#ifndef CLOCK_H_
#define CLOCK_H_

#include <stm32l4xx.h>

	/**
	! Initialize 48MHz HSE. System clock is 48MHz
	*/
void clock_init();

	/**
	! Enable clock output (LSE, DIV1)
	*/
void clock_out_enable();

void clock_48hse_to_24msi();
void clock_48hse_to_48msi();

void hse_init();
void clock_4msi_to_48msi();

#endif /* CLOCK_H_ */
