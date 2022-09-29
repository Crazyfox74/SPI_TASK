#ifndef UART_PROT_H_
#define UART_PROT_H_

#include <stdint.h>

typedef struct __attribute__((packed)) CalibPacket
{
	uint8_t start;
	uint32_t VolL;
	uint32_t CPTM;
	int32_t L;
	uint16_t T;
	uint32_t N;
	uint8_t crc;

}calib_packet_t ;

typedef enum
{
	PRODUV_NONE = 0,
	PRODUV_SEND_CALIB_PACKET,
	PRODUV_CONNECT,
	PRODUV_BLOCK,
}produv_state_e;

void uart_prot_proc();
produv_state_e uart_prot_proc_timer();
uint32_t uart_prot_getTimersConnect();
void uart_prot_switch();
void uart_prot_reset_timer_connnect();
uint8_t uart_prot_send_NBFI();

#endif /* UART_PROT_H_ */
