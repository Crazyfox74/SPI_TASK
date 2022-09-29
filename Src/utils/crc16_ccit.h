#ifndef __CRC16_CCIT_H__
#define __CRC16_CCIT_H__

#include <stdint.h>

	/**
	! CRC16_CCIT (0x1021)
	- buf source buffer
	- len buffer length
	- crc initial value (common values are 0 and 0xffff)
	+ CRC value
	*/
uint16_t crc16_ccit(const uint8_t *buf, uint16_t len, uint16_t crc);

uint16_t ml_CRC16(uint8_t *buf, uint32_t len, uint16_t seed, uint16_t poly);

#endif /* __CRC16_CCIT_H__ */
