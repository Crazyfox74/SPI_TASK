#include "board.h"
#include <stm32l4xx_ll_cortex.h>
#include <stm32l4xx_ll_rtc.h>
#include <stdio.h>


#include "clock.h"
#include "iwdg.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"



	#ifdef BOOTLOADER
#include "bl_AppUser.h"
#include "archive_user.h"
	#endif

#include "spi.h"
#include "spiFlash.h"
#include "spi_conf.h"
//#include "SpiManager.h"
#include "SpiManager_conf.h"





//#include "ax5043.h"




#define TASK_PRIO_START 1
#define TASK_START_STK_SIZE (1*256)


TaskHandle_t myTask1Handle = NULL;	//хэндл 1 задачи
TaskHandle_t myTask2Handle = NULL;	//хэндл 2 задач

QueueHandle_t myQueue;	//хэндл очереди




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



static void main_loop();


typedef struct {

} QUEUE_DATA;


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


void vApplicationIdleHook ( void ){
}

 void vApplicationMallocFailedHook( void )
 {
     for( ;; );
 }

extern void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  static StaticTask_t Idle_TCB;
  static StackType_t  Idle_Stack[configMINIMAL_STACK_SIZE];

  *ppxIdleTaskTCBBuffer = &Idle_TCB;
  *ppxIdleTaskStackBuffer = Idle_Stack;
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

extern void vApplicationGetTimerTaskMemory (StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
  static StaticTask_t Timer_TCB;
  static StackType_t  Timer_Stack[configTIMER_TASK_STACK_DEPTH];

  *ppxTimerTaskTCBBuffer   = &Timer_TCB;
  *ppxTimerTaskStackBuffer = Timer_Stack;
  *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    configASSERT( NULL );
}

void myTask1 (void *p){
	int count = 0;

	char TxBuf[30];

	myQueue = xQueueCreate(5,sizeof(TxBuf));

	sprintf(TxBuf, "message 1");
	xQueueSend(myQueue, (void*) TxBuf, (TickType_t) 5);

	sprintf(TxBuf, "message 2");
	xQueueSend(myQueue, (void*) TxBuf, (TickType_t) 5);

	sprintf(TxBuf, "message 3");
	xQueueSend(myQueue, (void*) TxBuf, (TickType_t) 5);

	while(1){
		//printf("Test: %d\r\n", count++);
		vTaskDelay(1000);
	}

}

void myTask2(void *p){

	char RxBuf[30];

	while(1){
			if(myQueue!=0){
				if(xQueueReceive(myQueue, (void *) RxBuf, (TickType_t) 5)){
					printf("data received: %s\r\n", RxBuf);
				}


			}else vTaskDelay(1000);
	}
}



volatile uint32_t delay_shuntsNoSleep = 0;

uint32_t flash_addr;
uint8_t cnt_flashb=4;
uint8_t rx_flashb[64];
uint16_t stat_reg1;
int main(void)
{


	clock_init();

	SpiInit();
	spiFlash_init();
	spiFlash_powerOn();

	stat_reg1=spiFlash_readStatus1();

	flash_addr=0;
	spiFlash_read( flash_addr, cnt_flashb, rx_flashb );

	xTaskCreate(myTask1, "task1", 200, (void*) 0, tskIDLE_PRIORITY, &myTask1Handle);	//создание задачи 1
	xTaskCreate(myTask2, "task2", 200, (void*) 0, tskIDLE_PRIORITY, &myTask2Handle);	//создание задачи 2

	vTaskStartScheduler();	//запуск диспетчера задач



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

//  ApplicationEventFlags.WeekHasPassed = 1;    // ��� ����� �� �� ������ ����� � �� ?
//  ApplicationEventFlags.DayHasPassed = 1;

#ifdef BOOTLOADER
	BL_AppInit();
#endif





#ifdef NCP_TESTS
    ApplicationEventFlags.BlowIsActive = 1;
    ncp_uart_init();
#else



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


