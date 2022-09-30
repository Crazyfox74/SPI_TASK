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
#include "FreeRTOS/portmacro.h"


	#ifdef BOOTLOADER
#include "bl_AppUser.h"
#include "archive_user.h"
	#endif

#include "spi.h"




#include "app_flags.h"

//#include "ax5043.h"


//freertos define

#define TASK_PRIO_START 1
#define TASK_START_STK_SIZE (1*256)


TaskHandle_t start_handler;




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
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    configASSERT( NULL );
}
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  static StaticTask_t Idle_TCB;
  static StackType_t  Idle_Stack[configMINIMAL_STACK_SIZE];

  *ppxIdleTaskTCBBuffer = &Idle_TCB;
  *ppxIdleTaskStackBuffer = Idle_Stack;
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory (StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
  static StaticTask_t Timer_TCB;
  static StackType_t  Timer_Stack[configTIMER_TASK_STACK_DEPTH];

  *ppxTimerTaskTCBBuffer   = &Timer_TCB;
  *ppxTimerTaskStackBuffer = Timer_Stack;
  *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
}


/***************************************************************************************/
BaseType_t xTaskCreate(
	TaskFunction_t pvTaskCode,	/*функция задачи*/
	const char * const pcName,	/*имя задачи*/
	unsigned short usStackDepth,	/*размер стека задачи*/
	void *pvParameters,	/*параметры задачи*/
	UBaseType_t uxPriority,	/*приоритет задачи*/
	TaskHandle_t * pvCreatedTask	/*дескриптор задачи*/
);


/***************************************************************************************/
//BaseType_t xQueueCreate(
//		unsigned portBASE_TYPE uxQueueLength,
//		unsigned portBASE_TYPE uxItemSize
//);
//************************
//BaseType_t xQueueSend(
//                  QueueHandle_t xQueue,	//дескриптор очереди сообщений
//                  const void * pvItemToQueue,	//передать адрес данных
//                  TickType_t xTicksToWait	//максимальное время ожидания для очереди
//);


BaseType_t xQueueReceive(
                  QueueHandle_t xQueue,	//дескриптор очереди сообщений
                  void * pvBuffer,	//адрес буфера для получени данных очереди
                  TickType_t xTicksToWait	//максимальное время ожидания для ожидания данных в очереди сообщений
);


void vTest(void *arg){ //тестовая задача

	char testDATA[60];
	QUEUE_DATA SPI_COM;
	while(1)
	{

		vTaskDelay(600);

	}

}

QueueHandle_t xQueue;

volatile uint32_t delay_shuntsNoSleep = 0;
int main(void)
{


	clock_init();

//	xQueue = xQueueCreate(5,sizeof(long))		//создание очереди в пять ячеек с типом  long

	xTaskCreate(vTest, "test_task", TASK_START_STK_SIZE, NULL, TASK_PRIO_START, &start_handler);	//создание задачи

	vTaskStartScheduler();	//запуск шедулера

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


