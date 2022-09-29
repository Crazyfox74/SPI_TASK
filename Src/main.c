#include "board.h"
#include <stm32l4xx_ll_cortex.h>
#include <stm32l4xx_ll_rtc.h>
#include <stdio.h>


#include "clock.h"
#include "iwdg.h"


#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/portmacro.h"
#include "FreeRTOS/FreeRTOSConfig.h"
#include "FreeRTOS/croutine.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"



	#ifdef BOOTLOADER
#include "bl_AppUser.h"
#include "archive_user.h"
	#endif

#include "spi.h"




#include "app_flags.h"

//#include "ax5043.h"






//volatile uint8_t debug_buf[256] = {0};
volatile uint8_t debug_bufTest[8] = {'T','e','s','t','-','w','r','t'};

#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
static volatile uint8_t reset_flag;


volatile uint32_t radio_supplyTxOn = 0;
volatile uint32_t radio_supplyRxOn = 0;
volatile uint32_t flash_supplyOn = 0;
volatile uint32_t tstmp_axsemReset = 0;
extern volatile uint32_t radio_int;



volatile uint32_t debug_cnsmtn = 0;

volatile ApplicationEventFlags_t ApplicationEventFlags = {0};
volatile ApplicationScheduler_t ApplicationScheduler = {0};

static void main_loop();



//==================================================================================
//      saveErrorTime - c��������� �������� ������� � ��������� ������
//==================================================================================


/**
 * TODO:
 * [.] scan - improve ASR
 * [ ] add 500ns delay for LCD strobe
 * [ ] check parallel IO pins
 *
 *
 *
 */


void vFreeRTOSInitAll()
{

}
void vApplicationIdleHook(void)
{
}

void vApplicationMallocFailedHook(void)
{
    for(;;);
}
/***************************************************************************************/


/***************************************************************************************/
void vApplicationTickHook(void)
{
}

void vTest(void *pvParameters){

	while(1)
	{
		vTaskDelay(600);

	}

}

volatile uint32_t delay_shuntsNoSleep = 0;
int main(void)
{


	clock_init();



#ifdef BOOTLOADER
	if ( SCB->VTOR == 0 )   // ���� ������� �������� ���������� �� ���������� �� ���������� ������ ��������
	{
		BL_ResetMCU_tbl();  // ������������� ��
	}
#endif

     __set_FAULTMASK(0);    // ��������� ����������, ��� ��� ��������� ��������� ��.

    iwdg_set_2s_reload();


//	SystemCoreClockUpdate();		/* Read core clock setting */

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	board_gpio_init();				/* Initialize board IO */

#if defined(DEBUG_) || defined(NCP_TESTS)
    uart_init();
#endif

	/* Initialize data storage */


#if RADIO_TYPE == RT_SIGFOX

#endif





	/* Set radio refresh period and schedule reset packet transmission */
//	bool app_setTxScheduled();
    ApplicationEventFlags.ResetDetected = 1;
//  ApplicationEventFlags.WeekHasPassed = 1;    // ��� ����� �� �� ������ ����� � �� ?
//  ApplicationEventFlags.DayHasPassed = 1;

#ifdef BOOTLOADER
	BL_AppInit();
#endif





#ifdef NCP_TESTS
    ApplicationEventFlags.BlowIsActive = 1;
    ncp_uart_init();
#else


    ApplicationEventFlags.BlowCountEnable = 1;
#endif

    board_led_clear();

#ifdef CONSUMPTION_CHECK
    rtc_wutr_reset( RTC_WAKEUP_2_PER_SECOND );
#endif

	main_loop();

#ifdef BOOTLOADER
	BL_ResetMCU_tbl();
#endif
}




void main_loop()
{



	while (1) {






          } while(0);
        }


