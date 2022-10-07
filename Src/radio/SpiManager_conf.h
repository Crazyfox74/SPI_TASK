#ifndef __SPI_MANAGER_CONF_H
#define __SPI_MANAGER_CONF_H

#include "spi.h"
//#include "rtc.h"
//#include "axtrx.h"
#include "spiFlash.h"

#define SPI_IO_TIMEOUT			250												// ������� ��� IO ��������	(1..255)
#define	SPI_OPEN_TIME_MAX		10												// ����� ����. �������� SPI, ����� ���� �� ����� ������������� ������ (1..65535)

#define SPI_DEVS_COUNT			2

    #ifndef SPI_DMA
#define SPI_IRQn							SPI1_IRQn
    #endif
    #ifdef SPI_DMA
#define SPI_IRQn							DMA1_Channel2_IRQn
    #endif
//#define SPI_DMA_TX_IRQn							DMA3_IRQn
//#define SPI_DMA_RX_PRIORITY						3
//#define SPI_DMA_TX_PRIORITY						2

#define SPI_INIT()				SpiInit()
#define SPI_DEINIT()			SpiDeinit()

// clock prescaler - F_PCLK/N
#define BR_SCALER_2         		(0x00000000U)
#define BR_SCALER_4         		(SPI_CR1_BR_0)
#define BR_SCALER_8         		(SPI_CR1_BR_1)
#define BR_SCALER_16        		(SPI_CR1_BR_1 | SPI_CR1_BR_0)
#define BR_SCALER_32        		(SPI_CR1_BR_2)
#define BR_SCALER_64        		(SPI_CR1_BR_2 | SPI_CR1_BR_0)
#define BR_SCALER_128       		(SPI_CR1_BR_2 | SPI_CR1_BR_1)
#define BR_SCALER_256       		(SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)

//#define SPI_MAN_PROFILES_ARRAY	{												\
									{	/* 0 - rf */							\
										.prescaler = BR_SCALER_8,				\
										.cs_set = axtrx_CS_set,					\
									},											\
									{	/* 1 - spi flash */						\
										.prescaler = BR_SCALER_32,				\
										.cs_set = spiFlash_setCS,				\
									},											\
								}

#define SPI_SET_PRESCALER(p)		do { SpiSetPrescaler(p); } while (0)

#define SPI_IRQ_ENABLE()			do { NVIC_SetPriority(SPI_IRQn, 3); NVIC_EnableIRQ(SPI_IRQn);  /*nvicEnableVector(SPI_DMA_RX_IRQn, SPI_DMA_RX_PRIORITY); nvicEnableVector(SPI_DMA_TX_IRQn, SPI_DMA_TX_PRIORITY);*/ } while (0)
#define SPI_IRQ_DISABLE()			do { NVIC_DisableIRQ(SPI_IRQn); /*nvicDisableVector(SPI_DMA_RX_IRQn); nvicDisableVector(SPI_DMA_TX_IRQn);*/ } while (0)
#define SPI_IRQ_IS_ENABLED()		NVIC_GetEnableIRQ(SPI_IRQn)
#define SPI_IRQ_CLEAR()				do { NVIC_ClearPendingIRQ(SPI_IRQn); } while (0)

#define SPI_BREAK()					do { SpiBreak(); } while (0)

//#define GET_TICK_COUNT()			rtc_get_ticks()

//#include "TimerManager.h"
#include "board.h"
//#define TIMER_START(interval_ms, once, cb, param)								TimerManagerTimerStart(TIMER_GROUP_ID_SPI_MAN, interval_ms, once, cb, param)
//#define TIMER_STOP(id)															TimerManagerTimerStop(TIMER_GROUP_ID_SPI_MAN, id)
//#define TIMER_STOP_ALL()														TimerManagerTimerGroupStop(TIMER_GROUP_ID_SPI_MAN)

#ifdef COLLECT_DBG_INFO
	#include "dbg_storage.h"
	#define SPI_MANAGER_TIMEOUT_CB(bIsIrq)	do {	if (!bIsIrq)							\
														dbg_storage.ulSpiManagerTO++;		\
													else									\
														dbg_storage.ulSpiManagerIrqTO++;	\
													DbgStorValidate();						\
												} while (0)
	#define SPI_MANAGER_OPEN_LONG_CB()		do {	dbg_storage.ulSpiOpenLongCnt++;	DbgStorValidate();	} while (0)
#endif

#endif
