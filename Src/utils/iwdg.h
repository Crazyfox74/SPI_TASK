#ifndef IWDG_H_
#define IWDG_H_

#include <stm32l4xx.h>

	/**
	! Initialize IWDG with 2.048sec timeout.
	Note: IWDG _must_ be enabled in option bits for production.
	*/
static inline void iwdg_set_2s_reload()
{
	/* enable write access */
	IWDG->KR = 0xCCCC;
	IWDG->KR = 0x5555;

    IWDG->RLR = 0xFFF;

	/* prescaler = 16, timeout = 2.048sec */
	IWDG->PR = IWDG_PR_PR_1;

	/* wait for registers to be updated */
	while (IWDG->SR != 0) ;

	/* reload counter */
	IWDG->KR = 0xAAAA;
}

static inline void iwdg_set_32s_reload()
{
	/* enable write access */
	IWDG->KR = 0xCCCC;
	IWDG->KR = 0x5555;

    IWDG->RLR = 0xFFF;

	/* prescaler = 128, timeout = 16.384sec */
	IWDG->PR = IWDG_PR_PR_2 | IWDG_PR_PR_1;

	/* wait for registers to be updated */
	while (IWDG->SR != 0) ;

	/* reload counter */
	IWDG->KR = 0xAAAA;
}

	/**
	! Kick the dog
	*/
static inline void iwdg_reset()
{
	IWDG->KR = 0xAAAA;
}

#endif /* IWDG_H_ */
