#include "SpiManager.h"

#include "SpiManager_conf.h"
#include <string.h>

// SpiManager. Организует доступ к SPI согласно заданному профилю.
//		Конфигурация должна быть описана в профиле SPI_MAN_PROFILES_ARRAY
//
//		Менеджер инициализируется через вызов SpiManagerInit()
//
//		Для осуществления передачи по SPI необходимо:
//			1) получить доступ к SPI через SpiManagerGet(id) или SpiManagerGetCb(id, OnGet_cb())
//				Вызов обеих функций возможен из-под прерывания
//			2) для обмена вызвать SpiManagerSendRecv(*buf_tx, *buf_rx, len, (*OnComplete_cb))
//				иди SpiManagerSendRecvX(**a_buf_tx, **a_buf_rx, *a_buf_len, cnt, (*OnComplete_cb)())
//				Если задан callback OnComplete_cb, то он будет вызван по окончанию
//					цикла обмена из-под прерывания (!)
//			3) освободить SPI через SpiManagerFree(id)
//
//		SpiManagerSendRecv, SpiManagerSendRecvX активирует CS из профиля -
//			.cs_set(1). По окончанию передачи деактивирует его - .cs_set(0)
//
//		SpiManagerBreak прерывает текущий обмен по SPI. Вызов только из основного
//			потока (!)
//
//		SpiManager_10msInt - вызывается каждые 10 мс извне для обсуживания
//			внутренних таймеров
//
//		SpiManagerDeinit - осуществляет деинициализация менеджера
//

#define DEV_ID_INVALID									0xff

#ifndef NULL
	#define NULL	0
#endif

typedef struct
{
	uint8_t	L1;
	uint8_t L2;
} LOCK;

static SPI_MAN_PROFILE spi_profiles[SPI_DEVS_COUNT] = SPI_MAN_PROFILES_ARRAY;

static struct
{
	uint8_t ucCurrId;															// ID устройства, которое сейчас заняло SPI
	volatile uint8_t nOnGetReq;
	uint8_t bCheckOnGet;
	volatile uint8_t bSpiBusy;													// флаг активной передачи по SPI
	void (*aOnGet_cb[SPI_DEVS_COUNT])();										//
	void (*OnRxTxComplete_cb)();												// указатель на callback, который нужно вызвать по окончании передачи
	uint8_t **paTxBuf, **paRxBuf;												// указатели на цепочки буферов (передаваемая, принимаемая)
	uint16_t *aBufLen;															// указатель на массив с длинами звеньев цепочки буферов
	uint8_t ucBufChainLen;														// длина цепочки буферов (кол-во буферов)
	uint8_t ucBufChainPos;														// текущий передаваемый буфер из цепочки

	volatile uint8_t ucIrqTimeout;												// таймаут для операции ввода/вывода с прерыванием
	uint8_t ucTimerId;															// сторожевой таймер
	uint8_t ucPowerOnMsk;														// маска включения

	volatile uint16_t usOpenTimeout;											//

	volatile LOCK LockGet, LockCb;												// примитивы синхронизации
} SpiManager;

static void SpiManager_100msTo(void *param);										// cb сторожевого таймера
static void SpiManager_OnTimeout();

static void LockInit(volatile LOCK *lock)
{
	lock->L1 = 0;
	lock->L2 = 0;
}

static uint8_t Lock(volatile LOCK *lock)
{
	if (lock->L1)
		return 0;
	lock->L1 = 1;

	if (lock->L2)
		return 0;
	lock->L2 = 1;

	return 1;
}

static void Unlock(volatile LOCK *lock)
{
	lock->L2 = 0;
	lock->L1 = 0;
}

static uint8_t GetLock(volatile LOCK *pLock)
{
	return pLock->L1;
}


void SpiManagerInit()
{
	memset(&SpiManager, 0x00, sizeof(SpiManager));
	SpiManager.ucCurrId = DEV_ID_INVALID;

	LockInit(&SpiManager.LockGet);
	LockInit(&SpiManager.LockCb);

	// деактивируем чипы на линии SPI
	for (uint8_t i = 0; i < SPI_DEVS_COUNT; i++)
		spi_profiles[i].cs_set(0);

	TIMER_STOP_ALL();
}

void SpiManagerDeinit()
{
	TIMER_STOP_ALL();

	SPI_IRQ_DISABLE();

	SPI_DEINIT();
}

void SpiManagerPowerOn(uint8_t id)
{
	if (SpiManager.ucPowerOnMsk == 0)
	{
		SPI_INIT();

		TIMER_STOP_ALL();
		SpiManager.ucTimerId = TIMER_START(100, 0, SpiManager_100msTo, NULL);

		SPI_IRQ_ENABLE();	// активируем прерывание SPI
	}
	SpiManager.ucPowerOnMsk |= (1 << id);
}

void SpiManagerPowerDown(uint8_t id)
{
	SpiManager.ucPowerOnMsk &= ~(1 << id);
	if (SpiManager.ucPowerOnMsk == 0)
	{
		SPI_IRQ_DISABLE();

		SPI_BREAK();
		SPI_IRQ_CLEAR();

		SpiManager.ucTimerId = TIMER_STOP(SpiManager.ucTimerId);
		TIMER_STOP_ALL();

		SPI_DEINIT();
	}
}

SPI_MAN SpiManagerGet(uint8_t id)
{
	SPI_MAN res = SPI_MAN_BUSY;

	if (Lock(&SpiManager.LockGet))
	{
		if ( !SpiManager.bSpiBusy && (SpiManager.ucCurrId == DEV_ID_INVALID) )
		{
			SpiManager.ucCurrId = id;
			SpiManager.usOpenTimeout = SPI_OPEN_TIME_MAX;

			// настраиваем SPI
			SPI_SET_PRESCALER(spi_profiles[SpiManager.ucCurrId].prescaler);

			res = SPI_MAN_OK;
		}
		Unlock(&SpiManager.LockGet);
	}

	return res;
}

SPI_MAN SpiManagerGetCb(uint8_t id, void (*OnGet_cb)())
{
	if (Lock(&SpiManager.LockGet))
	{
		if (SpiManager.ucCurrId == DEV_ID_INVALID) // SPI свободен?
		{
			SpiManager.ucCurrId = id;
			SpiManager.usOpenTimeout = SPI_OPEN_TIME_MAX;

			SPI_SET_PRESCALER(spi_profiles[SpiManager.ucCurrId].prescaler);
			Unlock(&SpiManager.LockGet);	//
			OnGet_cb();	// сразу же вызываем
		}
		else	// случай, когда SPI уже занят
		{
			if (!GetLock(&SpiManager.LockCb))
				SpiManager.bCheckOnGet = 1;
			SpiManager.nOnGetReq++;
			SpiManager.aOnGet_cb[id] = OnGet_cb;	// сохраняем callback для дальнейшего вызова
			Unlock(&SpiManager.LockGet);
		}
	}
	else	// случай, когда кто-то уже открывает или закрывает SPI
	{
		if (!GetLock(&SpiManager.LockCb))
			SpiManager.bCheckOnGet = 1;
		SpiManager.nOnGetReq++;
		SpiManager.aOnGet_cb[id] = OnGet_cb;	// сохраняем callback для дальнейшего вызова
	}

	return SPI_MAN_OK;
}

SPI_MAN SpiManagerFree(uint8_t id)
{
	void (*func)() = NULL;

	if (SpiManager.ucCurrId == id)		// проверка, чтобы не закрыть чужое устройство
	{
		SpiManager.OnRxTxComplete_cb = NULL;
		spi_profiles[SpiManager.ucCurrId].cs_set(0); // deactivate CS

		SpiManager.ucCurrId = DEV_ID_INVALID;
	}

	// если устройство свободно, проверяем, возможно кому-то был нужен SPI
	if (Lock(&SpiManager.LockCb))
	{
		if ( (SpiManager.ucCurrId == DEV_ID_INVALID) && SpiManager.nOnGetReq)
		{
			for (uint8_t i = 0; i < SPI_DEVS_COUNT; i++)
				if (SpiManager.aOnGet_cb[i] != NULL)
				{
					SpiManager.ucCurrId = i;			// теперь устройство стало открыто

					SPI_SET_PRESCALER(spi_profiles[SpiManager.ucCurrId].prescaler);

					func = SpiManager.aOnGet_cb[i];
					SpiManager.aOnGet_cb[i] = NULL;
					SpiManager.nOnGetReq--;
					break;
				}
		}
		Unlock(&SpiManager.LockCb);
	}

	// вызываем функцию, когда уже покинули защищённую область
	if (func != NULL)
		func();

	return SPI_MAN_OK;
}

SPI_MAN SpiManagerSendRecv(uint8_t *buf_tx, uint8_t *buf_rx, uint16_t len, void (*OnComplete_cb)())
{
	if (SpiManager.bSpiBusy)
		return SPI_MAN_BUSY;
	if (SpiManager.ucCurrId == DEV_ID_INVALID)
		return SPI_MAN_ERROR;

	spi_profiles[SpiManager.ucCurrId].cs_set(1); // activate CS
	SpiManager.bSpiBusy = 1;
	SpiManager.ucIrqTimeout = (uint8_t)(SPI_IO_TIMEOUT/100)? (uint8_t)(SPI_IO_TIMEOUT/100) : 1;

	if (OnComplete_cb == NULL)
	{
		SpiSendRecv(buf_tx, buf_rx, len);

		uint32_t ulTimeout = GET_TICK_COUNT() + SPI_IO_TIMEOUT;
		while (SpiManager.bSpiBusy && (GET_TICK_COUNT() <= ulTimeout));
		if (SpiManager.bSpiBusy)
		{
			SpiManager_OnTimeout();
			return SPI_MAN_ERROR;
		}

		if (SpiManager.ucCurrId != DEV_ID_INVALID)	// проверяем, т.к. ucCurrId может быть сброшен в случае ошибки SPI
			spi_profiles[SpiManager.ucCurrId].cs_set(0); // deactivate CS
	}
	else
	{
		// имитируем вырожденную цепочку буферов с длинной в 0 (чтобы вызвался callback по завершении)
		SpiManager.ucBufChainPos	= 0;
		SpiManager.ucBufChainLen	= 0;
		SpiManager.OnRxTxComplete_cb = OnComplete_cb;

		SpiSendRecv(buf_tx, buf_rx, len);
	}

	return SPI_MAN_OK;
}

static int cSpiErrAccess = 0;
SPI_MAN SpiManagerSendRecvX(uint8_t **a_buf_tx, uint8_t **a_buf_rx, uint16_t *a_buf_len, uint8_t cnt, void (*OnComplete_cb)())
{
	if (SpiManager.bSpiBusy)
	{
		cSpiErrAccess++;
		return SPI_MAN_BUSY;
	}
	if (SpiManager.ucCurrId == DEV_ID_INVALID)
		return SPI_MAN_ERROR;

	spi_profiles[SpiManager.ucCurrId].cs_set(1); // activate CS

	SpiManager.ucIrqTimeout = (uint8_t)(SPI_IO_TIMEOUT/100)? (uint8_t)(SPI_IO_TIMEOUT/100) : 1;
	if (OnComplete_cb == NULL) // нет callback'а - значит должны сидеть тут
	{
		for (uint8_t i = 0; i < cnt; i++)
		{
			SpiManager.bSpiBusy = 1;
			SpiSendRecv(a_buf_tx[i], a_buf_rx[i], a_buf_len[i]);
			uint32_t ulTimeout = GET_TICK_COUNT() + SPI_IO_TIMEOUT;
			while (SpiManager.bSpiBusy && (GET_TICK_COUNT() <= ulTimeout));
			if (SpiManager.bSpiBusy)
			{
				SpiManager_OnTimeout();
				return SPI_MAN_ERROR;
			}
		}

		if (SpiManager.ucCurrId != DEV_ID_INVALID)	// проверяем, т.к. ucCurrId может быть сброшен в случае ошибки SPI
			spi_profiles[SpiManager.ucCurrId].cs_set(0); // deactivate CS
	}
	else
	{
		SpiManager.paTxBuf = a_buf_tx;
		SpiManager.paRxBuf = a_buf_rx;
		SpiManager.aBufLen = a_buf_len;
		SpiManager.ucBufChainPos	= 0;
		SpiManager.ucBufChainLen	= cnt;
		SpiManager.OnRxTxComplete_cb = OnComplete_cb;
		SpiManager.bSpiBusy = 1;

		SpiSendRecv(a_buf_tx[0], a_buf_rx[0], a_buf_len[0]);
	}

	return SPI_MAN_OK;
}

SPI_MAN SpiManagerBreak(uint8_t id)
{
	/// TODO: вероятно, тут следует вызвать прерывание с bError=1, если id != ucCurrId. Или просто вызвать прерывание? Или не вызывать, пусть сам верхний модуль разбирается?..
	/// TODO: что делать, если после Lock прилетит SpiManagerGetCb() ?!
	SPI_MAN res = SPI_MAN_BUSY;

	if (Lock(&SpiManager.LockGet))	// этот Lock для того, чтобы не было конфликта с SpiManagerGetCb
	{
		uint8_t fIrqEnabled = SPI_IRQ_IS_ENABLED();
		SPI_IRQ_DISABLE();				// запрещаем прерывания, чтобы не изменилось OnRxTxComplete_cb

		if (SpiManager.ucCurrId == id)
		{
			SpiManager.OnRxTxComplete_cb = NULL;
//			if (ucCurrId != DEV_ID_INVALID)	// проверяем, т.к. ucCurrId может быть сброшен в случае ошибки SPI
			{
				spi_profiles[SpiManager.ucCurrId].cs_set(0); // deactivate CS
				SpiManager.ucCurrId = DEV_ID_INVALID;
				SpiManager.bSpiBusy = 0;
//				SPI_BREAK();														// актуально для активной длинной посылки
			}

			SPI_IRQ_CLEAR();
		}
		else
		{
			SpiManager.aOnGet_cb[id] = NULL;
		}
		if (fIrqEnabled)
			SPI_IRQ_ENABLE();

		Unlock(&SpiManager.LockGet);

		res = SPI_MAN_OK;
	}

	return res;
}


void SpiManager_OnSpiCompleteISR(uint8_t bError)
{
	SpiManager.bSpiBusy = 0;
	if (SpiManager.OnRxTxComplete_cb)	// передача была в асинхронном режиме?
	{
		if ( (++SpiManager.ucBufChainPos >= SpiManager.ucBufChainLen) || bError) // передали всю цепочку или ошибка?
		{
			spi_profiles[SpiManager.ucCurrId].cs_set(0); // deactivate CS

			// do callback
			void (*cb)() = SpiManager.OnRxTxComplete_cb;	// т.к. в самом callback может быть задан новый callback, очищаем его ДО вызова callback
			SpiManager.OnRxTxComplete_cb = NULL;
			cb();
		}
		else // иначе толкаем следующий буфер
		{
			SpiSendRecv(SpiManager.paTxBuf[SpiManager.ucBufChainPos], SpiManager.paRxBuf[SpiManager.ucBufChainPos], SpiManager.aBufLen[SpiManager.ucBufChainPos]);
		}
	}
}

//volatile uint32_t ulIsrCb = 0;
void SpiManager_100msTo(void *param)
{
	if (SpiManager.ucIrqTimeout)
	{
		SpiManager.ucIrqTimeout--;
		if ((SpiManager.ucIrqTimeout == 0) && (SpiManager.bSpiBusy))	// прерывание так и не было вызвано?
			SpiManager_OnTimeout();
	}

	if ( SpiManager.usOpenTimeout )
	{
		if (--SpiManager.usOpenTimeout == 0)												// таймаут вышел?
		{
			if (SpiManager.ucCurrId != DEV_ID_INVALID)
			{
				SpiManagerFree(SpiManager.ucCurrId);										// закрываем
#ifdef SPI_MANAGER_OPEN_LONG_CB
				SPI_MANAGER_OPEN_LONG_CB();
#endif
			}
		}
	}

	// в случае, если порт закрывался, а нам подкинули SpiManagerGetCb, то вызовем мы его только тут
	if ( SpiManager.bCheckOnGet && (SpiManager.ucCurrId == DEV_ID_INVALID) )
	{
		void (*func)() = NULL;

		if (SpiManager.nOnGetReq)
		{
			if (Lock(&SpiManager.LockCb))
			{
				for (uint8_t i = 0; i < SPI_DEVS_COUNT; i++)
					if (SpiManager.aOnGet_cb[i] != NULL)
					{
						SpiManager.ucCurrId = i;			// теперь устройство стало открыто
						SpiManager.usOpenTimeout = SPI_OPEN_TIME_MAX;

						SPI_SET_PRESCALER(spi_profiles[SpiManager.ucCurrId].prescaler);

						func = SpiManager.aOnGet_cb[i];
						SpiManager.aOnGet_cb[i] = NULL;
						SpiManager.nOnGetReq--;
						break;
					}

				Unlock(&SpiManager.LockCb);
			}
		}
		SpiManager.bCheckOnGet = 0;	// сбрасываем флаг, чтобы не возвращаться сюда без дела

		if (func)
		{
//			ulIsrCb++;
			func();
		}
	}
}

void SpiManager_OnTimeout()
{
	SPI_IRQ_DISABLE();

	SPI_BREAK();

	SpiManager_OnSpiCompleteISR(1);		// вызываем callback с признаком ошибки

	SpiManagerInit();					// переинициализируем себя

#ifdef SPI_MANAGER_TIMEOUT_CB
	SPI_MANAGER_TIMEOUT_CB(1);
#endif
}
