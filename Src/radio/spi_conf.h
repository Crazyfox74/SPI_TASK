#ifndef __SPI_CONF_H
#define __SPI_CONF_H

//#include "SpiManager.h"
//#include "axsem_platdefs.h"


#define SPI_SCK_GPIO            GPIOA
#define SPI_SCK_PIN             5
#define SPI_SCK_AF_0_7          LL_GPIO_AF_5

#define SPI_MOSI_GPIO           GPIOA
#define SPI_MOSI_PIN            7
#define SPI_MOSI_AF_0_7		    LL_GPIO_AF_5

#define SPI_MISO_GPIO           GPIOA
#define SPI_MISO_PIN            6
#define SPI_MISO_AF_0_7		    LL_GPIO_AF_5

//#define SPI_DMA_RX_CHANNEL
//#define SPI_DMA_TX_CHANNEL

//#define SPI_USE_FIFO
//#define	_SPI_DMA_TX_CH	DMA->ch[3]
//#define	_SPI_DMA_RX_CH	DMA->ch[2]
//#define DMAMUX_CHCFG_SOURCE_SPI0_RX        16                          // 0x10 SPI0 RX

#define SPI_ON_READY_ISR_CB(bError)		SpiManager_OnSpiCompleteISR(bError)
#define SPI_EMPTY_BYTE					0xff									// ����, ������� ����� ������������ ��� buf_tx = NULL

#ifdef COLLECT_DBG_INFO
	#include "dbg_storage.h"

	#define SPI_ON_DMA_TX_ERROR_CB()		do { dbg_storage.ulSpiDmaTxErrCnt++; DbgStorValidate(); } while (0);
	#define SPI_ON_DMA_RX_ERROR_CB()		do { dbg_storage.ulSpiDmaRxErrCnt++; DbgStorValidate(); } while (0);
#endif

#endif
