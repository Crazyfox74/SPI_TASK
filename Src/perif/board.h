#ifndef BOARD_H_
#define BOARD_H_

#include <stm32l4xx_ll_gpio.h>
#include <stm32l4xx_ll_spi.h>
#include <stm32l4xx_ll_adc.h>
#include <stm32l4xx_ll_rcc.h>
#include <stm32l4xx_ll_utils.h>
#include <stm32l4xx_ll_bus.h>
#include <stm32l4xx_ll_exti.h>
#include <stm32l4xx_ll_system.h>
//#include "config.h"

#if (defined(__ICCARM__))
#define RAMFUNC                     //__ramfunc
#define NOINIT                      __no_init
#elif (defined(__GNUC__))
#define RAMFUNC                     __attribute__ ((long_call, section (".ramfunctions")))
#define NOINIT                      __attribute__ ((section (".noinit")))
#endif

#ifdef PRINTF_ENABLE
#include <stdio.h>
#define DEBUG_OUT(...)      do { printf(__VA_ARGS__); } while (0)
#else
#define DEBUG_OUT(...)      do {  } while (0)
#endif

#define RST_SRC_PON			0x0001			// power-on reset
#define RST_SRC_WDT			0x0002			// watchdog reset
#define RST_SRC_LVD			0x0004			// low-voltage detect reset
#define RST_SRC_SW			0x0008			// software reset
#define RST_SRC_CSS			0x0010			// some clock troubles
#define RST_SRC_EXT			0x0020			// external pin reset
#define RST_SRC_LOCKUP		0x0040			// arm lockup
#define RST_SRC_HARDFAULT	0x0080			// hard fault occured

/* DBG1 */
    #ifndef PCB_V3
#define BOARD_DEBUG1_GPIO		GPIOA
#define BOARD_DEBUG1_PIN		LL_GPIO_PIN_8
    #endif
    #ifdef PCB_V3
#define BOARD_DEBUG1_GPIO		GPIOB
#define BOARD_DEBUG1_PIN		LL_GPIO_PIN_8
    #endif

/* ENABLE  COUNT - PIN BLOCK*/
#define BOARD_ENCOUNT_GPIO		GPIOB
#define BOARD_ENCOUNT_PIN		LL_GPIO_PIN_3

/* Green LED */
    #ifndef PCB_V3
#define BOARD_LED_GPIO			GPIOB
#define BOARD_LED_PIN			LL_GPIO_PIN_8
    #endif
    #ifdef PCB_V3
#define BOARD_LED_GPIO			GPIOA
#define BOARD_LED_PIN			LL_GPIO_PIN_15
    #endif

/* SELECT - MUX*/
#define BOARD_SELECT_GPIO		GPIOA
#define BOARD_SELECT_PIN		LL_GPIO_PIN_10

/* Direct sensor excitation - TpmN & TpmP */
#define BOARD_S0L_GPIO			GPIOB
#define BOARD_S0L_PIN			LL_GPIO_PIN_13
#define BOARD_S0H_GPIO			GPIOB
#define BOARD_S0H_PIN			LL_GPIO_PIN_14

/* Temperature sensor power */
#define BOARD_TEMP_PWR_GPIO		GPIOB
#define BOARD_TEMP_PWR_PIN		LL_GPIO_PIN_1

/* OPAMP1 power */
#define BOARD_AMP1_PWR_GPIO		GPIOA
    #ifndef PCB_V3
#define BOARD_AMP1_PWR_PIN		LL_GPIO_PIN_12
    #endif
    #ifdef PCB_V3
#define BOARD_AMP1_PWR_PIN		LL_GPIO_PIN_11
    #endif

/* SENSOR TX ENABLE*/
#define BOARD_SENS_TX_EN_GPIO 	GPIOB
#define BOARD_SENS_TX_EN_PIN 	LL_GPIO_PIN_12

/* SENSOR SHUNT ENABLE*/
#define BOARD_SENS_SH_EN_GPIO 	GPIOA
#define BOARD_SENS_SH_2_EN_GPIO GPIOA
    #ifndef PCB_V3
#define BOARD_SENS_SH_EN_PIN 	LL_GPIO_PIN_9
#define BOARD_SENS_SH_2_EN_PIN 	LL_GPIO_PIN_11
    #endif
    #ifdef PCB_V3
#define BOARD_SENS_SH_EN_PIN 	LL_GPIO_PIN_12
#define BOARD_SENS_SH_2_EN_PIN 	LL_GPIO_PIN_8
    #endif

/* Ultrasonic sensor amplifier ADC input */
#define BOARD_SENSOR_GPIO		GPIOA
#define BOARD_SENSOR_PIN		LL_GPIO_PIN_0
#define BOARD_SENSOR_ADC		ADC1
#define BOARD_SENSOR_ADC_CH		LL_ADC_CHANNEL_5 // IN5 is the fast channel!

/* Temperature sensor ADC input */
#define BOARD_TEMP_GPIO			GPIOA
#define BOARD_TEMP_PIN			LL_GPIO_PIN_2
#define BOARD_TEMP_ADC			ADC1
#define BOARD_TEMP_ADC_CH		LL_ADC_CHANNEL_7

// TX on/off
#define BOARD_RADIO_TX_GPIO	    GPIOH
#define BOARD_RADIO_TX_PIN		LL_GPIO_PIN_3

// RX on/off
    #ifndef PCB_V3
#define BOARD_RADIO_RX_GPIO	    GPIOC
#define BOARD_RADIO_RX_PIN		LL_GPIO_PIN_13
    #endif
    #ifdef PCB_V3
#define BOARD_RADIO_RX_GPIO	    GPIOB
#define BOARD_RADIO_RX_PIN		LL_GPIO_PIN_9
    #endif

// SPI FLASH on/off
    #ifndef PCB_V3
#define BOARD_SPI_FLASH_GPIO	GPIOB
#define BOARD_SPI_FLASH_PIN		LL_GPIO_PIN_9
    #endif
    #ifdef PCB_V3
#define BOARD_SPI_FLASH_GPIO	GPIOC
#define BOARD_SPI_FLASH_PIN		LL_GPIO_PIN_13
    #endif

// SPI FLASH CS
#define BOARD_SPI_FLASH_CS_GPIO	GPIOA
#define BOARD_SPI_FLASH_CS_PIN	LL_GPIO_PIN_4

// AX IRQ input
#define BOARD_RADIO_AX_IRQ_GPIO	    GPIOA
#define BOARD_RADIO_AX_IRQ_PIN		LL_GPIO_PIN_3

// UART1_TX
#define BOARD_UART1_TX_GPIO	    GPIOB
#define BOARD_UART1_TX_PIN		LL_GPIO_PIN_6

    #ifdef PCB_V3
// SAVE_WHEN_POWER_OFF -  ����������� ����������� ��� ����������� ���������� ���������
#define BOARD_SAVE_WHEN_PWR_OFF_GPIO    GPIOB
#define BOARD_SAVE_WHEN_PWR_OFF_PIN     LL_GPIO_PIN_8

// BAT2_CONNECT -  ����������� 2-�� ��������� ��� ���������� (���� �������� �� 2-�� ��������)
#define BOARD_BAT2_CONNECT_GPIO         GPIOA
#define BOARD_BAT2_CONNECT_PIN          LL_GPIO_PIN_9
    #endif

static inline void board_gpio_set_output(GPIO_TypeDef *GPIOx, uint32_t Pin,
		uint32_t Pull, uint32_t Speed)
{
	LL_GPIO_SetPinMode(GPIOx, Pin, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOx, Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOx, Pin, Pull);
	LL_GPIO_SetPinSpeed(GPIOx, Pin, Speed);
}

static inline void board_gpio_init()
{
	/* DBG1 */
	board_gpio_set_output(BOARD_DEBUG1_GPIO, BOARD_DEBUG1_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_VERY_HIGH);

	/* SPI FLASH Vdd on/off */
	board_gpio_set_output(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetOutputPin(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN);    // off flash pwr

	/* SPI FLASH CS */
	board_gpio_set_output(BOARD_SPI_FLASH_CS_GPIO, BOARD_SPI_FLASH_CS_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_ResetOutputPin(BOARD_SPI_FLASH_CS_GPIO, BOARD_SPI_FLASH_CS_PIN);    // CS = 0, while flash power is off

    //AXSEM Tx supply
	board_gpio_set_output(BOARD_RADIO_TX_GPIO, BOARD_RADIO_TX_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_ResetOutputPin(BOARD_RADIO_TX_GPIO, BOARD_RADIO_TX_PIN);    // off Tx power

	// AXSEM Rx supply
	board_gpio_set_output(BOARD_RADIO_RX_GPIO, BOARD_RADIO_RX_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetOutputPin(BOARD_RADIO_RX_GPIO, BOARD_RADIO_RX_PIN);      // off Rx power

	/* AMP1 */
	board_gpio_set_output(BOARD_AMP1_PWR_GPIO, BOARD_AMP1_PWR_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);

	/* TMP PWR */
	board_gpio_set_output(BOARD_TEMP_PWR_GPIO, BOARD_TEMP_PWR_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);

	/* LED */
	board_gpio_set_output(BOARD_LED_GPIO, BOARD_LED_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);

	/* SELECT */
	board_gpio_set_output(BOARD_SELECT_GPIO, BOARD_SELECT_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);

	/* TX SENS ENABLE*/
	board_gpio_set_output(BOARD_SENS_TX_EN_GPIO, BOARD_SENS_TX_EN_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);

	/* SHUNT SENS ENABLE*/
	board_gpio_set_output(BOARD_SENS_SH_EN_GPIO, BOARD_SENS_SH_EN_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);

    board_gpio_set_output(BOARD_SENS_SH_2_EN_GPIO, BOARD_SENS_SH_2_EN_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);

	/* S0L */
	//LL_GPIO_SetPinMode(BOARD_S0L_GPIO, BOARD_S0L_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinMode(BOARD_S0L_GPIO, BOARD_S0L_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(BOARD_S0L_GPIO, BOARD_S0L_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	//LL_GPIO_SetAFPin_8_15(BOARD_S0L_GPIO, BOARD_S0L_PIN, LL_GPIO_AF_14);
	LL_GPIO_SetPinPull(BOARD_S0L_GPIO, BOARD_S0L_PIN, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(BOARD_S0L_GPIO, BOARD_S0L_PIN, LL_GPIO_SPEED_FREQ_LOW);

	/* S0H */
	//LL_GPIO_SetPinMode(BOARD_S0H_GPIO, BOARD_S0H_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinMode(BOARD_S0H_GPIO, BOARD_S0H_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(BOARD_S0H_GPIO, BOARD_S0H_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	//LL_GPIO_SetAFPin_8_15(BOARD_S0H_GPIO, BOARD_S0H_PIN, LL_GPIO_AF_14);
	LL_GPIO_SetPinPull(BOARD_S0H_GPIO, BOARD_S0H_PIN, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(BOARD_S0H_GPIO, BOARD_S0H_PIN, LL_GPIO_SPEED_FREQ_LOW);

    LL_GPIO_SetPinMode(BOARD_ENCOUNT_GPIO, BOARD_ENCOUNT_PIN, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(BOARD_ENCOUNT_GPIO, BOARD_ENCOUNT_PIN, LL_GPIO_PULL_NO);

    LL_GPIO_SetPinMode(BOARD_UART1_TX_GPIO, BOARD_UART1_TX_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinPull(BOARD_UART1_TX_GPIO, BOARD_UART1_TX_PIN, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(BOARD_UART1_TX_GPIO, BOARD_UART1_TX_PIN, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_ResetOutputPin(BOARD_UART1_TX_GPIO, BOARD_UART1_TX_PIN);

#ifdef PCB_V3
	/* BAT2_CONNECT */
	board_gpio_set_output(BOARD_BAT2_CONNECT_GPIO, BOARD_BAT2_CONNECT_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_ResetOutputPin(BOARD_BAT2_CONNECT_GPIO, BOARD_BAT2_CONNECT_PIN);    // 2nd battery disconnect

	/* SAVE_WHEN_PWR_OFF */
	board_gpio_set_output(BOARD_SAVE_WHEN_PWR_OFF_GPIO, BOARD_SAVE_WHEN_PWR_OFF_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_ResetOutputPin(BOARD_SAVE_WHEN_PWR_OFF_GPIO, BOARD_SAVE_WHEN_PWR_OFF_PIN);    // capacitor disconnect
#endif
}

extern volatile uint32_t radio_supplyTxOn;
extern volatile uint32_t radio_supplyRxOn;
extern volatile uint32_t flash_supplyOn;

static inline void board_dbg1_set();
static inline void board_dbg1_clear();

static inline void axsem_supplyTxOn()
{
    LL_GPIO_SetOutputPin(BOARD_RADIO_TX_GPIO, BOARD_RADIO_TX_PIN);
    LL_GPIO_ResetOutputPin(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN);

    radio_supplyTxOn = 1;
}

static inline void axsem_supplyTxOff()
{
    LL_GPIO_ResetOutputPin(BOARD_RADIO_TX_GPIO, BOARD_RADIO_TX_PIN);
    if ( !radio_supplyRxOn && !flash_supplyOn)
        LL_GPIO_SetOutputPin(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN);

    radio_supplyTxOn = 0;
}

static inline void axsem_supplyRxOn()
{
    LL_GPIO_ResetOutputPin(BOARD_RADIO_RX_GPIO, BOARD_RADIO_RX_PIN);
    LL_GPIO_ResetOutputPin(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN);

    radio_supplyRxOn = 1;
}

static inline void axsem_supplyRxOff()
{
    LL_GPIO_SetOutputPin(BOARD_RADIO_RX_GPIO, BOARD_RADIO_RX_PIN);
    if ( !flash_supplyOn)
        LL_GPIO_SetOutputPin(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN);

    radio_supplyRxOn = 0;
}

static inline void supply_flashOn()
{
    LL_GPIO_ResetOutputPin(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN);

    flash_supplyOn = 1;
}

static inline void supply_flashOff()
{
    LL_GPIO_SetOutputPin(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN);

    flash_supplyOn = 0;
}

static inline void SELECT_ON()	{ LL_GPIO_SetOutputPin(BOARD_SELECT_GPIO, BOARD_SELECT_PIN); }
static inline void SELECT_OFF()	{ LL_GPIO_ResetOutputPin(BOARD_SELECT_GPIO, BOARD_SELECT_PIN); }

static inline void AMP1_ON()	{ LL_GPIO_SetOutputPin(BOARD_AMP1_PWR_GPIO, BOARD_AMP1_PWR_PIN); }		// AMP_EN = 1, разрешаем работу ОУ
static inline void AMP1_OFF()	{ LL_GPIO_ResetOutputPin(BOARD_AMP1_PWR_GPIO, BOARD_AMP1_PWR_PIN); } 	// AMP_EN = 0, запрещаем работу ОУ

static inline void SENS_TX_ON()   {LL_GPIO_SetOutputPin(BOARD_SENS_TX_EN_GPIO, BOARD_SENS_TX_EN_PIN);}
static inline void SENS_TX_OFF()  {LL_GPIO_ResetOutputPin(BOARD_SENS_TX_EN_GPIO, BOARD_SENS_TX_EN_PIN);}

static inline void SENS_SHUNT_ON()  {LL_GPIO_SetOutputPin(BOARD_SENS_SH_EN_GPIO, BOARD_SENS_SH_EN_PIN);}
static inline void SENS_SHUNT_OFF()  {LL_GPIO_ResetOutputPin(BOARD_SENS_SH_EN_GPIO, BOARD_SENS_SH_EN_PIN);}

static inline void SENS_SHUNT_2_ON()  {LL_GPIO_SetOutputPin(BOARD_SENS_SH_2_EN_GPIO, BOARD_SENS_SH_2_EN_PIN);}
static inline void SENS_SHUNT_2_OFF()  {LL_GPIO_ResetOutputPin(BOARD_SENS_SH_2_EN_GPIO, BOARD_SENS_SH_2_EN_PIN);}

#define GUI_LED_INIT()          board_gpio_set_output(BOARD_LED_GPIO, BOARD_LED_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
#define GUI_LED_ON()            { LL_GPIO_ResetOutputPin(BOARD_LED_GPIO, BOARD_LED_PIN); }
#define GUI_LED_OFF()           { LL_GPIO_SetOutputPin(BOARD_LED_GPIO, BOARD_LED_PIN); }

#define PWR_TX_OFF()			axsem_supplyTxOff();
#define PWR_TX_ON()             axsem_supplyTxOn();
#define PWR_RX_OFF()            axsem_supplyRxOff();
#define PWR_RX_ON()				axsem_supplyRxOn();

#define SPI_FLASH_PWR_OUT()     board_gpio_set_output(BOARD_SPI_FLASH_GPIO, BOARD_SPI_FLASH_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
#define SPI_FLASH_PWR_OFF()     supply_flashOff();      // off flash pwr
#define SPI_FLASH_PWR_ON()      supply_flashOn();       // on flash pwr

#define SPI_FLASH_CS_OUT()      board_gpio_set_output(BOARD_SPI_FLASH_CS_GPIO, BOARD_SPI_FLASH_CS_PIN, LL_GPIO_PULL_NO, LL_GPIO_SPEED_FREQ_LOW);
#define SPI_FLASH_CS_HIGH()     LL_GPIO_SetOutputPin(BOARD_SPI_FLASH_CS_GPIO, BOARD_SPI_FLASH_CS_PIN);    // CS = 1
#define SPI_FLASH_CS_LOW()      LL_GPIO_ResetOutputPin(BOARD_SPI_FLASH_CS_GPIO, BOARD_SPI_FLASH_CS_PIN);    // CS = 0

static inline void S0H_DISABLE()	{ LL_GPIO_SetPinMode(BOARD_S0H_GPIO, BOARD_S0H_PIN, LL_GPIO_MODE_INPUT); }

static inline void board_dbg1_toggle() 	{ LL_GPIO_TogglePin(BOARD_DEBUG1_GPIO, BOARD_DEBUG1_PIN); }
static inline void board_dbg1_set()		{ LL_GPIO_SetOutputPin(BOARD_DEBUG1_GPIO, BOARD_DEBUG1_PIN); }
static inline void board_dbg1_clear() 	{ LL_GPIO_ResetOutputPin(BOARD_DEBUG1_GPIO, BOARD_DEBUG1_PIN); }

static inline void board_led_set() 		{ LL_GPIO_ResetOutputPin(BOARD_LED_GPIO, BOARD_LED_PIN); }
static inline void board_led_clear() 	{ LL_GPIO_SetOutputPin(BOARD_LED_GPIO, BOARD_LED_PIN); }
static inline void board_led_toggle() 	{ LL_GPIO_TogglePin(BOARD_LED_GPIO, BOARD_LED_PIN); }

static inline uint32_t pin_read_enable_count() { return LL_GPIO_IsInputPinSet(BOARD_ENCOUNT_GPIO, BOARD_ENCOUNT_PIN); }

#endif /* BOARD_H_ */
