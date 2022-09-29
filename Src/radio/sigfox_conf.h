#ifndef __SIGFOX_CONF_H
#define __SIGFOX_CONF_H

#include <stm32l4xx.h>
#include <stm32l4xx_ll_rtc.h>

#include "config.h"

#define SIGFOX_RADIO_RDY_TO									3000				// radio ready timeout
#define SIGFOX_TX_TO										3000				// tx timeout in ms for 1 packet
#define SIGFOX_TX_PAUSE										1500                // pause between repeats
#define USE_MULTIPLE_PACKET									1					// 0 if use single packet transmition

#define GET_INT16(buff, offset) ((uint16_t)((uint8_t *)(buff))[(offset)] | ((uint16_t)((uint8_t *)(buff))[(offset) + 1] << 8))

#define SET_INT16R(buff, offset, val) {((uint8_t *)(buff))[(offset)] = (val >> 8) & 0xff; ((uint8_t *)(buff))[(offset)+1] = ((val)>>0) & 0xff;}
#define SET_INT32(buff, offset, val) {((uint8_t *)(buff))[(offset)] = (val) & 0xff; ((uint8_t *)(buff))[(offset)+1] = ((val)>>8) & 0xff; ((uint8_t *)(buff))[(offset)+2] = ((val)>>16) & 0xff; ((uint8_t *)(buff))[(offset)+3] = ((val)>>24) & 0xff;}

/*
 * System Register address and magic marker
 */
#define SYSTEM_REGISTER						(TAMP_BASE + 0x100)
#define SYSTEM_REGISTER_SIGFOX_OFFSET		0x0

static inline uint32_t sigfox_read_nvm()
{
	//return *(uint32_t*)(SYSTEM_REGISTER + SYSTEM_REGISTER_SIGFOX_OFFSET);
    return LL_RTC_BKP_GetRegister( TAMP, 0);
}

static inline void sigfox_write_nvm(uint32_t val)
{
	//*(uint32_t*)(SYSTEM_REGISTER + SYSTEM_REGISTER_SIGFOX_OFFSET) = val;
    LL_RTC_BKP_SetRegister( TAMP, 0, val);
}

#include "sigfox_storage.h"
#include "rtc.h"
#include "crc16_ccit.h"

#define GET_TICK_COUNT()									rtc_get_ticks()
#define CRC16(buf, len, seed, poly)							ml_CRC16(buf, len, seed, poly)

#if RADIO_TYPE == RT_SIGFOX
	#include "TimerManager.h"
	#define TIMER_START(interval_ms, once, cb, param)			TimerManagerTimerStart(TIMER_GPOUP_ID_SIGFOX, interval_ms, once, cb, param)
	#define TIMER_STOP(id)										TimerManagerTimerStop(TIMER_GPOUP_ID_SIGFOX, id)
	#define SIGFOX_NVM_READ_MC()   								sigfoxCounts_getMC()
    #define SIGFOX_NVM_READ_RoC()  								sigfoxCounts_getRoC()
	#define SIGFOX_NVM_WRITE(MC, RoC)							sigfoxCounts_write( MC, RoC)

	#include "radio.h"
	#define RADIO_SEND(buf, len, to)							ax5043_send_paddingSigFox(buf, len, to)
	#define RADIO_ON(ch)										ax5043_power_on(RM_SIGFOX, ch)
	#define RADIO_OFF()											ax5043_power_off()
#else
	#define TIMER_START(interval_ms, once, cb, param)			0
	#define TIMER_STOP(id)										0
	#define SIGFOX_NVM_READ_MC()                                0
    #define SIGFOX_NVM_READ_RoC()                               0
	#define SIGFOX_NVM_WRITE(MC, RoC)

	#define RADIO_SEND(buf, len, to)
	#define RADIO_OFF()
	#define RADIO_ON(ch)
#endif

#endif
