#ifndef __SPI_MANAGER_H_
#define __SPI_MANAGER_H_

#include <stdint.h>

//#include "axtrx.h"

typedef enum
{
	SPI_MAN_OK			= 0,
	SPI_MAN_BUSY		= 0x40,
	SPI_MAN_ERROR		= 0x80,
} SPI_MAN;

typedef struct
{
	uint8_t prescaler;
	void (*cs_set)(uint8_t bEnable);
} SPI_MAN_PROFILE;

void SpiManagerInit();															// ������������� ���������� SPI
void SpiManagerDeinit();														// ��������������� ���������� SPI
void SpiManagerPowerOn(uint8_t id);
void SpiManagerPowerDown(uint8_t id);

// �. ��������� �������
SPI_MAN SpiManagerGet(uint8_t id);												// ������ �� ����� �� SPI. ���������� SPI_MAN_OK, ���� SPI �������� � ����� � ������
SPI_MAN SpiManagerGetCb(uint8_t id, void (*OnGet_cb)());						// ������ SpiManagerGet, ������ �����������
SPI_MAN SpiManagerFree(uint8_t id);												// ��������, ��� SPI ������ �� �����. ����������� ���������� ����� SpiManagerGet

// �. ������
SPI_MAN SpiManagerSendRecv(uint8_t *buf_tx, uint8_t *buf_rx, uint16_t len, void (*OnComplete_cb)());		// ���������� ������ �� SPI. buf_rx ����� ���� NULL, ���� �������� ����� �� �����
SPI_MAN SpiManagerSendRecvX(uint8_t **a_buf_tx, uint8_t **a_buf_rx, uint16_t *a_buf_len, uint8_t cnt, void (*OnComplete_cb)());		// ���������� ������ �� SPI. **a_buf_rx ����� ���� NULL, ���� �������� ����� ������ �� �����. �������� a_buf_tx/a_buf_rx ����� ���� NULL, ���� �� ���������

SPI_MAN SpiManagerBreak(uint8_t id);											// ���������� �������� ������ �� SPI � ��������� �����

void SpiManager_OnSpiCompleteISR(uint8_t bError);								// ���������� �� ��������� �������� �� ����������

#endif
