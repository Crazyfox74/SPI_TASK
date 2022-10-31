#include "board.h"
#include <stm32l4xx_ll_cortex.h>
#include <stm32l4xx_ll_rtc.h>
#include <stdio.h>
#include <string.h>

#include "clock.h"
#include "iwdg.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "delay.h"

	#ifdef BOOTLOADER
#include "bl_AppUser.h"
#include "archive_user.h"
	#endif


#include "spi.h"
#include "spiFlash.h"
#include "spi_conf.h"
//#include "SpiManager.h"
#include "SpiManager_conf.h"

#define TASK_PRIO_START 1
#define TASK_START_STK_SIZE (1*256)

TaskHandle_t myTaskEraseHandle = NULL;	//хэндл 1 задачи
TaskHandle_t myTaskReadHandle = NULL;	//хэндл 2 задачи
TaskHandle_t myTaskWriteHandle = NULL;	//хэндл 3 задачи
TaskHandle_t mySpiManagerHandle = NULL;
TaskHandle_t mySpiSendRecieveHandle = NULL;

QueueHandle_t myQueue;	//хэндл очереди
QueueHandle_t flashQueue;

SemaphoreHandle_t SemaphoreFlash;

extern BaseType_t err;

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

uint32_t flash_addr;
uint8_t cnt_flashb = 4;
uint8_t rx_flashb[64];
uint8_t tx_flashb[64];

uint16_t stat_reg1;
uint16_t stat_reg2;
extern volatile uint8_t SpiActive;
uint32_t jedec_id;
uint8_t wr_en;

uint8_t res = FLASH_RES_ERROR_AGAIN;

uint8_t k = 0;

uint8_t res_erase;

volatile uint32_t debug_cnsmtn = 0;

static void main_loop();

typedef struct {
	uint32_t flash_addr;
	uint8_t cnt_flashb;
	uint8_t *flash_buf;
	uint8_t cmd_flash;
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

void TaskErase (void *p){

	QUEUE_DATA flashData;

	flashData.flash_addr = 0;
	flashData.cmd_flash = CMD_ERASE_4KB;

	while(1){
		xQueueSend(flashQueue, &flashData, 50);

		vTaskDelay(1500);
	}
}

void TaskRead(void *p){

	QUEUE_DATA flashData;

	flashData.flash_addr = 0;
	flashData.cnt_flashb = 4;
	flashData.flash_buf = rx_flashb;
	flashData.cmd_flash = CMD_READ_DATA;

	while(1){
		xQueueSend(flashQueue, &flashData, 50);

		vTaskDelay(500);
	}

}

void TaskWrite (void *p){

	QUEUE_DATA flashData;

	flashData.flash_addr = 0;
	flashData.cnt_flashb = 4;
	flashData.flash_buf = tx_flashb;
	flashData.cmd_flash = CMD_PAGE_PROGRAMM;
	tx_flashb[0] = 10;
	tx_flashb[1] = 20;
	tx_flashb[2] = 30;
	tx_flashb[3] = 40;

	while(1){
		xQueueSend(flashQueue, &flashData, 50);

		vTaskDelay(1000);
	}

}

void TaskSpiManager (void *p){

	QUEUE_DATA flashData;
	uint8_t sizeRx = sizeof(rx_flashb);

	while(1){
		xQueueReceive(flashQueue, &flashData, portMAX_DELAY);

		switch(flashData.cmd_flash){
		case CMD_ERASE_4KB:
			wr_en = spiFlash_wrtEnbl();

			stat_reg1 = spiFlash_readStatus(CMD_READ_STATUS_REG1);
			stat_reg2 = spiFlash_readStatus(CMD_READ_STATUS_REG2);

			res_erase = spiFlash_eraseSector(flashData.flash_addr, flashData.cmd_flash);
			do {
				stat_reg1 = spiFlash_readStatus(CMD_READ_STATUS_REG1);
			} while (stat_reg1 & 0x01 );
			break;
		case CMD_READ_DATA:
			memset(flashData.flash_buf, 0x00, sizeRx);

			spiFlash_read( flashData.flash_addr, flashData.cnt_flashb, flashData.flash_buf, flashData.cmd_flash );

			break;
		case CMD_PAGE_PROGRAMM:

			wr_en = spiFlash_wrtEnbl();
			stat_reg1 = spiFlash_readStatus(CMD_READ_STATUS_REG1);
			stat_reg2 = spiFlash_readStatus(CMD_READ_STATUS_REG2);
			spiFlash_write(flashData.flash_addr, flashData.cnt_flashb, flashData.flash_buf, flashData.cmd_flash);
			do {
				stat_reg1 = spiFlash_readStatus(CMD_READ_STATUS_REG1);
			} while (stat_reg1 & 0x01 );

			spiFlash_read( flashData.flash_addr, flashData.cnt_flashb, rx_flashb, CMD_READ_DATA );

			break;

		}

		xSemaphoreTake(SemaphoreFlash,portMAX_DELAY);

	}

}


volatile uint32_t delay_shuntsNoSleep = 0;

int main(void)
{
	clock_init();

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	board_gpio_init();				/* Initialize board IO */

	SpiInit();
	spiFlash_init();
	spiFlash_powerOn();


	xTaskCreate(TaskErase, "ERASE_task", 200, (void*) 0, tskIDLE_PRIORITY+1, &myTaskEraseHandle);	//создание задачи 1
	xTaskCreate(TaskRead, "READ_task", 200, (void*) 0, tskIDLE_PRIORITY+1, &myTaskReadHandle);	//создание задачи 2
	xTaskCreate(TaskWrite, "WRITE_task", 200, (void*) 0, tskIDLE_PRIORITY+1, &myTaskWriteHandle);	//создание задачи 3
	xTaskCreate(TaskSpiManager, "SPIMANAGER_task", 200, (void*) 0, tskIDLE_PRIORITY+1, &mySpiManagerHandle); //создание задачи 4
	//xTaskCreate(TaskSpiRW, "task5", 200,(void*) 0, tskIDLE_PRIORITY+2, &mySpiSendRecieveHandle); //создание задачи 5

	flashQueue= xQueueCreate(10, sizeof(QUEUE_DATA));

	SemaphoreFlash=xSemaphoreCreateBinary();

	vTaskStartScheduler();	//запуск диспетчера задач





     __set_FAULTMASK(0);    // ��������� ����������, ��� ��� ��������� ��������� ��.

    iwdg_set_2s_reload();



	/* Initialize data storage */


#if RADIO_TYPE == RT_SIGFOX

#endif

    board_led_clear();

	main_loop();

}

void main_loop()
{

	while (1) {

          } while(0);
        }


