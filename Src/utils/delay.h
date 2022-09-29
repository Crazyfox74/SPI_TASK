#ifndef DELAY_H_
#define DELAY_H_

	/**
	! good enough up to 1ms @ 80MHz
	*/
#if defined(__ICCARM__)
	#pragma optimize=none
#elif defined(__GNUC__)
	#pragma GCC push_options
	#pragma GCC optimize ("O0")
#else
    #error "Unsupported compiler"
#endif

static inline void delay_us(uint32_t us) {
	for (volatile uint32_t i = 0; i < us * 5; i++) {
		asm volatile ("mov r0, r0");
		asm volatile ("mov r0, r0");
	}
}

	/**
	! +1us error @ 30MHz HSE
	*/
#if defined(__ICCARM__)
	#pragma optimize=none
#elif defined(__GNUC__)
	#pragma GCC optimize ("O0")
#else
    #error "Unsupported compiler"
#endif
static inline void delay_us_40M(uint32_t us) {
	for (volatile uint32_t i = 0; i < us * 2; i++) {
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
	}
}

#if defined(__GNUC__)
	#pragma GCC pop_options
#endif

#endif /* DELAY_H_ */
