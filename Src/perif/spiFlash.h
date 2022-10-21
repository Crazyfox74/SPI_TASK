#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_

//#include "rtc.h"

/********************************************************************
	DEFINES
*********************************************************************/

#define FLASH_RES_OK				0
#define FLASH_RES_ERROR_BUSY		1
#define FLASH_RES_ERROR_WRITE_ENABLE	2
#define FLASH_RES_ERROR_AGAIN		10

#define FLASH_WE_ATTEMPTS			3
//#define P_SPI_CS        			D, 0     // �� ����������� ������� �����������. �� ����� ���� ��� CS flash-������
//#define P_MEM_CS					P_SPI_CS

#define FLASH_PAGE_SIZE				(256)
#define FLASH_PAGE_MASK				(FLASH_PAGE_SIZE-1)

#define REG_STATUS_BUSY_MASK	    0x01
#define REG_STATUS_WEL_MASK			0x02

#include "SpiManager.h"
#define SPI_MANAGER_ID_MEM				1
//#define SPI_FLASH_OPEN()				(SpiManagerGet(SPI_MANAGER_ID_MEM) == SPI_MAN_OK)		// �������� �����
//#define SPI_FLASH_CLOSE()				SpiManagerFree(SPI_MANAGER_ID_MEM)						// ������������ �����
#define SPI_RW(tx, rx, len, cb)			SpiManagerSendRecv(tx, rx, len, cb)						// ������/������ ������ �/�� SPI
#define SPI_RWx(a_tx, a_rx, a_len, cnt, cb)	SpiManagerSendRecvX(a_tx, a_rx, a_len, cnt, cb)		// ������/������ ������� ������� �/�� SPI
#define SPI_RWF(tx, rx, len)			SpiManagerSendRecvFlash(tx, rx, len);
#define SPI_RWFX(a_tx, a_rx, a_len, cnt)	SpiManagerSendRecvFlashX(a_tx, a_rx, a_len, cnt);
//#define SPI_BREAK()						SpiManagerBreak(SPI_MANAGER_ID_MEM)						// �������� ������� �������� �� SPI

//================================================================================================

void spiFlash_init( void );
void spiFlash_deinit( void );
void spiFlash_powerOn();
void spiFlash_powerDown();
void spiFlash_setCS(uint8_t bEnable);
uint16_t spiFlash_readStatus( uint8_t cmd );
void spiFlash_read( uint32_t dwAddrRead, uint16_t bCnt, uint8_t* pBuf );
uint8_t spiFlash_write( uint32_t dwAddrWrite, uint16_t bCnt, uint8_t* pBuf );
uint8_t spiFlash_eraseSector( uint32_t dwSectAddr );
uint8_t spiFlash_wrtEnbl();

uint32_t spiFlash_readJEDECDesc( void );

#endif
