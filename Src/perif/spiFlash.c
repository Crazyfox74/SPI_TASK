#include "spi.h"

#include "delay.h"

#include "spiFlash.h"
#include "SpiManager.h"
#include "SpiManager_conf.h"

#ifndef NULL
	#define NULL	0
#endif

#define CMD_WRITE_ENABLE					0x06
#define CMD_PAGE_PROGRAMM					0x02
#define CMD_RELEASE_POWER_DOWN				0xAB
#define CMD_READ_STATUS_REG1				0x05
#define CMD_READ_STATUS_REG2				0x35
#define CMD_READ_DATA						0x03
#define CMD_ERASE_4KB						0x20
#define CMD_ERASE_64KB						0xd8

//#define FL_WRITE_TO							(10/10+1)
//#define FL_ERASE_TO							(500/10)
//#define FL_ERASE_BLOCK_TO					(2000/10)
#define FL_IO_TO							10

/********************************************************************
	DEFINES
*********************************************************************/
#define MEM_BUF_CHAIN_LEN					2

/********************************************************************
	���������� ����������
*********************************************************************/
//static volatile uint16_t usTimeout;					// ������� ��� �������� �����/������
static uint8_t *a_buf_tx[MEM_BUF_CHAIN_LEN];		// ������ ������ �� ������ ��������
static uint8_t *a_buf_rx[MEM_BUF_CHAIN_LEN];		// ������ ������ �� ������ �����
static uint16_t a_buf_len[MEM_BUF_CHAIN_LEN];		// ����� �������
static uint8_t buf_txrx[6];							// ����� ��� ������� � ������

static uint8_t spi_buf_tx[32];		//буфер для передачи
static uint8_t spi_buf_rx[32];		//буфер для чтения

extern volatile uint8_t SpiActive;
/********************************************************************
	���������� ���������
*********************************************************************/
//void s25fl_GPIO_Sel( void );

/********************************************************************/
//        spiFlash_init - ������������� ����� ��� �������
/********************************************************************/
void spiFlash_init( void )
{
	SPI_FLASH_PWR_OUT();//настройка на выход ножки PB9
	SPI_FLASH_PWR_OFF();//запись 1 в PB9(выключение)

	SPI_FLASH_CS_OUT();
    SPI_FLASH_CS_LOW();
}

void spiFlash_deinit( void )
{
	SPI_FLASH_PWR_OFF();

	SPI_FLASH_CS_OUT();
    SPI_FLASH_CS_LOW();
}

void spiFlash_powerOn()
{
	SPI_FLASH_PWR_ON();//запись 0 в PB9(включение)

	SPI_FLASH_CS_OUT();
	SPI_FLASH_CS_HIGH();

	SPI_IRQ_ENABLE();
	//SpiManagerPowerOn(SPI_MANAGER_ID_MEM);
}

void spiFlash_powerDown()
{
	//SpiManagerPowerDown(SPI_MANAGER_ID_MEM);

	SPI_FLASH_PWR_OFF();

	SPI_FLASH_CS_LOW();
}

void spiFlash_setCS(uint8_t bEnable)
{
    if (bEnable) {
		SPI_FLASH_CS_LOW();
    }
	else {
		SPI_FLASH_CS_HIGH();
    }
}

/********************************************************************/
//        spiFlash_read - ������ ������ �� ���������� ������
/********************************************************************/
void spiFlash_read( uint32_t dwAddrRead, uint16_t bCnt, uint8_t* pBuf, uint8_t cmd )
{

	buf_txrx[0] = cmd;
	buf_txrx[1] = (uint8_t)(dwAddrRead >> 16);
	buf_txrx[2] = (uint8_t)(dwAddrRead >> 8);
	buf_txrx[3] = (uint8_t)(dwAddrRead >> 0);
	a_buf_tx[0] = buf_txrx;
	a_buf_rx[0] = NULL;
	a_buf_len[0] = 4;

	a_buf_tx[1] = NULL;
	a_buf_rx[1] = pBuf;
	a_buf_len[1] = bCnt;

	SPI_FLASH_CS_LOW();
	SPI_RWFX(a_buf_tx, a_buf_rx, a_buf_len, 2);

	SPI_FLASH_CS_HIGH();


}

/********************************************************************/
//        spiFlash_write - ������ ������ �� ���������� ������
/********************************************************************/
static volatile uint32_t ulAgain = 0;
uint8_t spiFlash_write( uint32_t dwAddrWrite, uint16_t bCnt, uint8_t* pBuf, uint8_t cmd )
{
	uint8_t res = FLASH_RES_ERROR_AGAIN;
	uint16_t i;

	buf_txrx[0] = cmd;
	buf_txrx[1] = (uint8_t)(dwAddrWrite >> 16);
	buf_txrx[2] = (uint8_t)(dwAddrWrite >> 8);
	buf_txrx[3] = (uint8_t)(dwAddrWrite >> 0);
	a_buf_tx[0] = buf_txrx;
	a_buf_rx[0] = NULL;
	a_buf_len[0] = 4;

	a_buf_tx[1] = pBuf;
	a_buf_rx[1] = NULL;
	a_buf_len[1] = bCnt;

	SPI_FLASH_CS_LOW();
	SPI_RWFX(a_buf_tx, a_buf_rx, a_buf_len, 2);

	SPI_FLASH_CS_HIGH();
	res = FLASH_RES_OK;

	return res;
}

/********************************************************************/
//        s25fl_readStatus - ������ �������� �������
/********************************************************************/
uint16_t spiFlash_readStatus( uint8_t cmd )
{
	uint16_t bRegStatus;

	spi_buf_tx[0] = cmd;
	spi_buf_tx[1] = 0xff;

	SPI_FLASH_CS_LOW();
	SpiSendRecv(spi_buf_tx, spi_buf_rx, 2);
	while(SpiActive);
	SPI_FLASH_CS_HIGH();
	bRegStatus = spi_buf_rx[1];

	return bRegStatus;
}

uint8_t spiFlash_wrtEnbl()
{
	uint8_t res = FLASH_RES_ERROR_AGAIN;

	buf_txrx[0] = CMD_WRITE_ENABLE;

	SPI_FLASH_CS_LOW();
	SpiSendRecv(buf_txrx, NULL, 1);
	while(SpiActive);
	SPI_FLASH_CS_HIGH();

	res = FLASH_RES_OK;

	return res;
}

/*uint8_t spiFlash_wakeUp()
{
	uint8_t res = 0;

	SPI_CS_LOW;

	xSpi(CMD_RELEASE_POWER_DOWN);
	xSpi(0xFF); // dummy
	xSpi(0xFF); // dummy
	xSpi(0xFF); // dummy
	res = xSpi(0xFF); // id7-0

    SPI_CS_HI;

	return res;
}*/

/********************************************************************/
//        spiFlash_readJEDECDesc - ������ �������� �������
/********************************************************************/
uint32_t spiFlash_readJEDECDesc( void )
{
	uint32_t result = 0;

	buf_txrx[0] = 0x9F;
	a_buf_tx[0] = buf_txrx;
	a_buf_tx[0] = NULL;
	a_buf_len[0] = 1;

	a_buf_tx[1] = NULL;
	a_buf_rx[1] = (uint8_t*)&result;

	SPI_FLASH_CS_LOW();
	SPI_RWFX(a_buf_tx, a_buf_rx, a_buf_len, 2);

	return result;
}

/********************************************************************/
//        spiFlash_eraseSector - �������� ������� �� ���������� ������
/********************************************************************/
uint8_t spiFlash_eraseSector( uint32_t dwSectAddr, uint8_t cmd )
{
	uint8_t res = FLASH_RES_ERROR_AGAIN;

	buf_txrx[0] = cmd;		// ������� �������� �������
	buf_txrx[1] = (uint8_t)(dwSectAddr >> 16);
	buf_txrx[2] = (uint8_t)(dwSectAddr >> 8);
	buf_txrx[3] = (uint8_t)(dwSectAddr >> 0);

	SPI_FLASH_CS_LOW();
	SpiSendRecv(buf_txrx, NULL, 4);
	while(SpiActive){};
	SPI_FLASH_CS_HIGH();

	res = FLASH_RES_OK;

	return res;
}
