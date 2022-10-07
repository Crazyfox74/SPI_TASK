#include "spi.h"

#include "spiFlash.h"
#include "SpiManager.h"
#include "SpiManager_conf.h"

#ifndef NULL
	#define NULL	0
#endif

#define CMD_WRITE_ENABLE					0x06
#define CMD_PAGE_PROGRAMM					0x02
#define CMD_RELEASE_POWER_DOWN				0xAB
#define CMD_READ_STATUS_REG					0x05
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
void spiFlash_read( uint32_t dwAddrRead, uint16_t bCnt, uint8_t* pBuf )
{
	//uint32_t ulTimeout = rtc_get_ticks();
//	while ( !systicks_isTimeout(ulTimeout, FL_IO_TO) )
//	{
	//	if (SPI_FLASH_OPEN())
	//	{
	/*
			buf_txrx[0] = CMD_READ_DATA;		// ������� ������ ������
			buf_txrx[1] = (uint8_t)(dwAddrRead >> 16); //третий байт адреса
			buf_txrx[2] = (uint8_t)(dwAddrRead >> 8);	//второй байт адреса
			buf_txrx[3] = (uint8_t)(dwAddrRead >> 0);
			a_buf_tx[0] = buf_txrx;
			a_buf_rx[0] = NULL;
			a_buf_len[0] = 4;

			a_buf_tx[1] = NULL;
			a_buf_rx[1] = pBuf;
			a_buf_len[1] = bCnt;

			SpiSendRecv(buf_txrx, a_buf_tx, 4);
			//SPI_RWx(a_buf_tx, a_buf_rx, a_buf_len, 2, NULL);

*/
	uint16_t i;
			spi_buf_tx[0]=CMD_READ_DATA;
			spi_buf_tx[1] = (uint8_t)(dwAddrRead >> 16); //третий байт адреса
			spi_buf_tx[2] = (uint8_t)(dwAddrRead >> 8);	//второй байт адреса
			spi_buf_tx[3] = (uint8_t)(dwAddrRead >> 0);



			for( i=4;i<4+bCnt;i++){
				spi_buf_tx[i]=0xff;
			}
			a_buf_rx[0] = pBuf;
			SpiSendRecv(spi_buf_tx, a_buf_rx[0], i);


		//	SPI_FLASH_CLOSE();

	//		break;
	//	}
	//}
}

/********************************************************************/
//        spiFlash_write - ������ ������ �� ���������� ������
/********************************************************************/
static volatile uint32_t ulAgain = 0;
uint8_t spiFlash_write( uint32_t dwAddrWrite, uint16_t bCnt, uint8_t* pBuf )
{
	uint8_t res = FLASH_RES_ERROR_AGAIN;

	// ��������� ������
	uint8_t i = FLASH_WE_ATTEMPTS;
	uint8_t j = 0;
	while (i && j < FLASH_WE_ATTEMPTS)	/// TODO: ������ ����� ��������� �� FLASH_RES_ERROR_AGAIN ? -> radio ����� �� ������� SPI
	{
		if (spiFlash_wrtEnbl() == FLASH_RES_ERROR_AGAIN)
		{
			j++;
			continue;
		}
		else
		{
			if (spiFlash_readStatus() & REG_STATUS_WEL_MASK)
				break;
		}
		i--;
	}
	if (i == 0) // ��� � �� ������� ��������� ������?
		res = (j == FLASH_WE_ATTEMPTS)? FLASH_RES_ERROR_AGAIN : FLASH_RES_ERROR_WRITE_ENABLE;	// FLASH_RES_ERROR_AGAIN � ������, ���� WE ��������� ������ FLASH_RES_ERROR_AGAIN
	else
	{
      //  uint32_t ulTimeout = rtc_get_ticks();
     //   while ( !systicks_isTimeout(ulTimeout, FL_IO_TO) )
		{
	//		if (SPI_FLASH_OPEN())
			{
				buf_txrx[0] = CMD_PAGE_PROGRAMM;		// ������� ������ ������
				buf_txrx[1] = (uint8_t)(dwAddrWrite >> 16);
				buf_txrx[2] = (uint8_t)(dwAddrWrite >> 8);
				buf_txrx[3] = (uint8_t)(dwAddrWrite >> 0);
				a_buf_tx[0] = buf_txrx;
				a_buf_rx[0] = NULL;
				a_buf_len[0] = 4;

				a_buf_tx[1] = pBuf;
				a_buf_rx[1] = NULL;
				a_buf_len[1] = bCnt;

				SPI_RWx(a_buf_tx, a_buf_rx, a_buf_len, 2, NULL);

			//	SPI_FLASH_CLOSE();

				res = FLASH_RES_OK;
			//	break;
			}
		}
	}

	if (res == FLASH_RES_ERROR_AGAIN)
		ulAgain++;

	return res;
}

/********************************************************************/
//        s25fl_readStatus - ������ �������� �������
/********************************************************************/
uint16_t spiFlash_readStatus1( void )
{
	uint16_t bRegStatus;

//	uint32_t ulTimeout = rtc_get_ticks();
//	while ( !systicks_isTimeout(ulTimeout, FL_IO_TO) )
	//{
	//	if (SPI_FLASH_OPEN())
		//{
	/*
			buf_txrx[0] = CMD_READ_STATUS_REG;		// ������� ������ �������� �������
			buf_txrx[1] = 0xFF;

			SpiSendRecv(buf_txrx, buf_txrx, 2);

		//	SPI_RW(buf_txrx, buf_txrx, 2, NULL);

		//	SPI_FLASH_CLOSE();

			bRegStatus = buf_txrx[1];

*/

			spi_buf_tx[0]=CMD_READ_STATUS_REG;
			spi_buf_tx[1]=0xff;
			spi_buf_tx[2]=0xff;

			SpiSendRecv(spi_buf_tx, spi_buf_rx, 3);

			bRegStatus=spi_buf_rx[0];
			bRegStatus=bRegStatus<<8;
			bRegStatus |=spi_buf_rx[1];


		//	break;
		//}
//	}

	return bRegStatus;
}

uint8_t spiFlash_wrtEnbl()
{
	uint8_t res = FLASH_RES_ERROR_AGAIN;

	// ��������� ������
	//uint32_t ulTimeout = rtc_get_ticks();
//	while ( !systicks_isTimeout(ulTimeout, FL_IO_TO) )
//	{
	//	if (SPI_FLASH_OPEN())
	//	{
			buf_txrx[0] = CMD_WRITE_ENABLE;

			SpiSendRecv(buf_txrx, NULL, 1);

		//	SPI_RW(buf_txrx, NULL, 1, NULL);

		//	SPI_FLASH_CLOSE();

			res = FLASH_RES_OK;
		//	break;
		//}
	//}

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

	uint32_t ulTimeout = rtc_get_ticks();
	while ( !systicks_isTimeout(ulTimeout, FL_IO_TO) )
	{
		if (SPI_FLASH_OPEN())
		{
			buf_txrx[0] = 0x9F;		// ������� ������ �������� JEDEC
			a_buf_tx[0] = buf_txrx;
			a_buf_rx[0] = NULL;
			a_buf_len[0] = 1;

			a_buf_tx[1] = NULL;
			a_buf_rx[1] = (uint8_t*)&result;
			a_buf_len[1] = 3;

			SPI_RWx(a_buf_tx, a_buf_rx, a_buf_len, 2, NULL);

			SPI_FLASH_CLOSE();

			break;
		}
	}

	return result;
}

/********************************************************************/
//        spiFlash_eraseSector - �������� ������� �� ���������� ������
/********************************************************************/
uint8_t spiFlash_eraseSector( uint32_t dwSectAddr )
{
	uint8_t res = FLASH_RES_ERROR_AGAIN;

	// ��������� ������
	uint8_t i = FLASH_WE_ATTEMPTS;
	uint8_t j = 0;
	while (i && j < FLASH_WE_ATTEMPTS)
	{
		if (spiFlash_wrtEnbl() == FLASH_RES_ERROR_AGAIN)
		{
			j++;
			continue;
		}
		else
		{
			if (spiFlash_readStatus() & REG_STATUS_WEL_MASK)
				break;
		}
		i--;
	}
	if (i == 0) // ��� � �� ������� ��������� ������?
		res = (j == FLASH_WE_ATTEMPTS)? FLASH_RES_ERROR_AGAIN : FLASH_RES_ERROR_WRITE_ENABLE;	// FLASH_RES_ERROR_AGAIN � ������, ���� WE ��������� ������ FLASH_RES_ERROR_AGAIN
	else
	{
		// �������� ������� 4 ������
	uint32_t ulTimeout = rtc_get_ticks();
	while ( !systicks_isTimeout(ulTimeout, FL_IO_TO) )
		{
			if (SPI_FLASH_OPEN())
			{
				buf_txrx[0] = CMD_ERASE_4KB;		// ������� �������� �������
				buf_txrx[1] = (uint8_t)(dwSectAddr >> 16);
				buf_txrx[2] = (uint8_t)(dwSectAddr >> 8);
				buf_txrx[3] = (uint8_t)(dwSectAddr >> 0);

				SPI_RW(buf_txrx, NULL, 4, NULL);

				SPI_FLASH_CLOSE();
				res = FLASH_RES_OK;

				break;
			}
		}
	}

	return res;
}

