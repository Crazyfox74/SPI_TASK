#include "spi.h"
#include <stm32l4xx_ll_dma.h>

#include "spi_conf.h"

// SPI драйвер
// SPI драйвер занимается только процессом приемопередачи байтов в/из SPI

static LL_SPI_InitTypeDef SPI_InitStruct = { 0 };

static volatile uint8_t SpiActive;					// флаг активной передачи

#ifndef SPI_DMA
static uint8_t *pBufTx, *pBufRx;
static uint16_t usBufPosRx, usBufPosTx;
static uint16_t usBufCnt;
#endif

#ifdef SPI_DMA
uint8_t spi_txEmptyBuf[256] = {SPI_EMPTY_BYTE} ;
uint8_t spi_rxDummyBuf[256] = {0} ;
#endif

#ifdef SPI_DMA
void DMA1_Channel2_IRQHandler(void)
{
	if (LL_DMA_IsActiveFlag_TC2(DMA1) == 1) {
		LL_DMA_ClearFlag_TC2(DMA1);

        SpiActive = 0;
		SPI_ON_READY_ISR_CB(0);
    }
}

//void DMA1_Channel3_IRQHandler(void)
//{
//	if (LL_DMA_IsActiveFlag_TC3(DMA1) == 1) {
//		LL_DMA_ClearFlag_TC3(DMA1);
//    }
//}

static void spi_rx_dma_init()
{
	/* enable DMA interrupts */
	NVIC_SetPriority(DMA1_Channel2_IRQn, 1);    // DMA IRQ lower priority than ADC IRQ
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);

	/* enable DMA clock */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	/* Configure the DMA transfer */
	LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_2,
		LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
		LL_DMA_MODE_NORMAL |
		LL_DMA_PERIPH_NOINCREMENT |
		LL_DMA_MEMORY_INCREMENT |
		LL_DMA_PDATAALIGN_BYTE |
		LL_DMA_MDATAALIGN_BYTE |
		LL_DMA_PRIORITY_MEDIUM);

	/* select SPI1 RX as DMA transfer request */
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMA_REQUEST_1);

	/* enable Transfer Complete interrupt */
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
}

static void spi_rx_dma_start(uint8_t *dst, uint16_t qntt)
{
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, qntt);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2,
		        (uint32_t)&SPI1->DR, (uint32_t) dst, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
}

static void spi_tx_dma_init()
{
	/* enable DMA interrupts */
	NVIC_SetPriority(DMA1_Channel3_IRQn, 1);    // DMA IRQ lower priority than ADC IRQ
	//NVIC_EnableIRQ(DMA1_Channel3_IRQn);

	/* enable DMA clock */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	/* Configure the DMA transfer */
	LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_3,
		LL_DMA_DIRECTION_MEMORY_TO_PERIPH |
		LL_DMA_MODE_NORMAL |
		LL_DMA_PERIPH_NOINCREMENT |
		LL_DMA_MEMORY_INCREMENT |
		LL_DMA_PDATAALIGN_BYTE |
		LL_DMA_MDATAALIGN_BYTE |
		LL_DMA_PRIORITY_MEDIUM);

	/* select SPI1 TX as DMA transfer request */
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_3, LL_DMA_REQUEST_1);

	/* enable Transfer Complete interrupt */
	//LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_3);
}

static void spi_tx_dma_start(uint8_t *src, uint16_t qntt)
{
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, qntt);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_3,
		        (uint32_t) src, (uint32_t)&SPI1->DR, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    DMA1_Channel2->CCR |= DMA_CCR_MINC;

	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
}

static void spi_tx_null_dma_start(uint8_t *src, uint16_t qntt)
{
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, qntt);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_3,
		        (uint32_t) src, (uint32_t)&SPI1->DR, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    DMA1_Channel2->CCR &= ~DMA_CCR_MINC;

	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
}
#endif

static void spi_gpio_init()
{
	/* SPI SCK */
	LL_GPIO_SetPinMode(SPI_SCK_GPIO, 1 << SPI_SCK_PIN, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(SPI_SCK_GPIO, 1 << SPI_SCK_PIN, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinPull(SPI_SCK_GPIO, 1 << SPI_SCK_PIN, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(SPI_SCK_GPIO, 1 << SPI_SCK_PIN, SPI_SCK_AF_0_7);
	LL_GPIO_SetPinOutputType(SPI_SCK_GPIO, 1 << SPI_SCK_PIN, LL_GPIO_OUTPUT_PUSHPULL);

	/* SPI MISO */
	LL_GPIO_SetPinMode(SPI_MISO_GPIO, 1 << SPI_MISO_PIN, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(SPI_MISO_GPIO, 1 << SPI_MISO_PIN, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinPull(SPI_MISO_GPIO, 1 << SPI_MISO_PIN, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(SPI_MISO_GPIO, 1 << SPI_MISO_PIN, SPI_MISO_AF_0_7);
	LL_GPIO_SetPinOutputType(SPI_MISO_GPIO, 1 << SPI_MISO_PIN, LL_GPIO_OUTPUT_PUSHPULL);

	/* SPI MOSI */
	LL_GPIO_SetPinMode(SPI_MOSI_GPIO, 1 << SPI_MOSI_PIN, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(SPI_MOSI_GPIO, 1 << SPI_MOSI_PIN, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinPull(SPI_MOSI_GPIO, 1 << SPI_MOSI_PIN, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(SPI_MOSI_GPIO, 1 << SPI_MOSI_PIN, SPI_MOSI_AF_0_7);
	LL_GPIO_SetPinOutputType(SPI_MOSI_GPIO, 1 << SPI_MOSI_PIN, LL_GPIO_OUTPUT_PUSHPULL);
}

void SpiInit()
{
	SpiActive = 0;

    spi_gpio_init();

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;//reset RCC_SPI(запись единицы)
	RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST);//don't reset RCC_SPI(запись нуля)

	/* SPI1 parameter configuration*/
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
	SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
	SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV32;
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
	SPI_InitStruct.CRCPoly = 7;
	LL_SPI_Init(_SPI, &SPI_InitStruct);

	_SPI->CR2 |= SPI_CR2_FRXTH;

#ifdef SPI_DMA
    _SPI->CR2 |= SPI_CR2_TXDMAEN;
    _SPI->CR2 |= SPI_CR2_RXDMAEN;
#endif

	LL_SPI_Enable(_SPI);
    LL_SPI_EnableIT_RXNE(_SPI);

#ifndef SPI_DMA
    NVIC_EnableIRQ(SPI1_IRQn);
#endif

#ifdef SPI_DMA
    spi_rx_dma_init();
    spi_tx_dma_init();
#endif
}

void SpiDeinit()
{
    LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1);          /* Force reset of SPI clock */
    LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1);        /* Release reset of SPI clock */

#ifdef SPI_DMA
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
#endif

    HIZ_PIN( SPI_SCK_GPIO, SPI_SCK_PIN );
    HIZ_PIN( SPI_MISO_GPIO, SPI_MISO_PIN );
    HIZ_PIN( SPI_MOSI_GPIO, SPI_MOSI_PIN );

	SpiActive = 0;
}

void SpiSendRecv(uint8_t *buf_tx, uint8_t *buf_rx, uint16_t len)
{
	SpiActive = 1;

#ifndef SPI_DMA
	pBufTx = buf_tx;
	pBufRx = buf_rx;
	usBufPosRx = 0;
	usBufPosTx = 1;
	usBufCnt = len;

	while (!(_SPI->SR & SPI_SR_TXE)); //ожидание установки 1 в TXE(окончание передачи)
	if (pBufTx)
		*(uint8_t*)&_SPI->DR = *pBufTx;
	else
		*(uint8_t*)&_SPI->DR = SPI_EMPTY_BYTE;
#endif

#ifdef SPI_DMA
    if ( buf_rx )
        spi_rx_dma_start(buf_rx, len);
    else
        spi_rx_dma_start(spi_rxDummyBuf, len);

    if ( buf_tx )
        spi_tx_dma_start(buf_tx, len);
    else
        spi_tx_null_dma_start(spi_txEmptyBuf, len);
#endif
}

void SpiBreak()
{
    LL_SPI_Disable(_SPI);

    LL_APB1_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1);          /* Force reset of SPI clock */
    LL_APB1_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1);        /* Release reset of SPI clock */

#ifdef SPI_DMA
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
#endif

    LL_SPI_Init(_SPI, &SPI_InitStruct);

	_SPI->CR2 |= SPI_CR2_FRXTH;

	LL_SPI_Enable(_SPI);

	SpiActive = 0;
}

void SpiSetPrescaler(uint32_t value)
{
    LL_SPI_SetBaudRatePrescaler( _SPI, value );
}

RAMFUNC uint8_t SpiIsReady()
{
	return !SpiActive;
}

#ifndef SPI_DMA
void SPI1_IRQHandler(void)
{
	{
		volatile uint8_t ucByte = *(uint8_t*)&_SPI->DR;

		if (pBufRx)
			pBufRx[usBufPosRx] = ucByte;
	}

	{
		if (usBufPosTx < usBufCnt)
		{
			if (pBufTx)
				*(uint8_t*)&_SPI->DR = pBufTx[usBufPosTx];
			else
				*(uint8_t*)&_SPI->DR = SPI_EMPTY_BYTE;

			usBufPosTx++;
		}
	}

	if (++usBufPosRx >= usBufCnt)
	{
		SpiActive = 0;
		//SPI_ON_READY_ISR_CB(0);
	}
}
#endif
