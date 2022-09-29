#include "clock.h"
//#include "config.h"
#include <stm32l4xx_ll_bus.h>
#include <stm32l4xx_ll_rcc.h>
#include <stm32l4xx_ll_system.h>
#include <stm32l4xx_ll_utils.h>
#include <stm32l4xx_ll_gpio.h>
#include <stm32l4xx_ll_pwr.h>
#include <stm32l4xx_ll_cortex.h>

//==================================================================================
//      systick_init - ������������ SysTick ��� ��������� ���������� � �������� 1 ��
//  Comment: ������������ ��� LL_mDelay().
//==================================================================================
static void systick_init( uint32_t freq )
{
	LL_Init1msTick(freq);
	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	LL_SetSystemCoreClock(freq);

    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    NVIC_EnableIRQ(SysTick_IRQn);
}

//#define MSI48_to_HSE48
void hse_init()
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
	if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
		for (;;);

#ifndef MSI48_to_HSE48
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
#endif
	LL_RCC_HSE_Enable();

    LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_4);                 // �������� ������� �� ����� �������� ������������ ������� HSE

	/* Wait till HSE is ready */
	while (LL_RCC_HSE_IsReady() != 1);

	LL_RCC_HSE_EnableCSS();
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSE);

#ifndef MSI48_to_HSE48
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

    systick_init( 48000000 );
#endif
}

void clock_init()
{
    //clock_4msi_to_48msi();
	hse_init();



	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ALL);

	/* Enable Power Clock */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	/* Ensure that MSI is wake-up system clock */
	LL_RCC_SetClkAfterWakeFromStop(LL_RCC_STOP_WAKEUPCLOCK_MSI);
    LL_RCC_MSI_EnableRangeSelection();
}
