#ifndef UART_PROT_NEW_H_
#define UART_PROT_NEW_H_

#include <stdint.h>

typedef enum { // классы команд
  	UART_CMD_TYPE_NONE = 0,
  	UART_CMD_TYPE_METROLOGY,
  	UART_CMD_TYPE_SERVICE_DATA,
	UART_CMD_TYPE_LOG,
	UART_CMD_TYPE_BOOT,

} eTypeCmd;

typedef enum { // перечисление команд типа METROLOGY
	UART_CMD_WRITE_COEF_L = 0,
	UART_CMD_READ_COEF_L,
	UART_CMD_WRITE_COEF_A,
	UART_CMD_READ_COEF_A,
	UART_CMD_SAVE_COEF,
	UART_CMD_READ_VOLUME,
	UART_CMD_READ_ZERO,
	UART_CMD_SEARCH_ZERO,

} eMetrologyCmd;

typedef enum { // перечисление команд типа SERVICE_DATA
	UART_CMD_READ_VOLTAGE = 0,
	UART_CMD_READ_TEMPERATURE,
	UART_CMD_READ_ANGLE,
	UART_CMD_READ_TIME_WORK,
	UART_CMD_READ_MAC,
    UART_CMD_READ_TOUCH_STATUS,
    UART_CMD_CHECK_FLASH,
    UART_CMD_CHECK_FLASH_VCC,
    UART_CMD_SET_LCD_MODE,          // выводит заданные комбинации символов на ЖКИ
    UART_CMD_SET_SLEEP_MODE,        // переводит счетчик на заданное время (1..30 секунд) в режим SLEEP
    UART_CMD_TEST_48MHz,            // вкл/выккл вывода на пин Block деленной частоты 48 MHz
    UART_CMD_GET_SIGNAL_PARAMS,     // команда для получения параметров сигналов с УЗ датчиков
    UART_CMD_TEST_26MHz,            // вкл/выккл TCXO для измерения его частоты 26 MHz (трансивер в режим приема SDC)
    UART_CMD_TEST_TX,               // вкл/выкл трансивера в режим передачи (NBFI/SigFox)

} eServiceDataCmd;

typedef enum { // перечисление команд типа LOG
	UART_CMD_READ_LOG = 0,

} eLogCmd;

typedef enum { // статус приема пакета
	UART_RX_WAIT_START = 0,				// ждем стартовый байт пакета
	UART_RX_IN_PROGRESS,				// процесс приема пакета
	UART_RX_UNSTUFF,					// unstuff в процессе приема пакета
	UART_RX_COMPLETED					// прием пакета завершен
} eRcvState;


#pragma pack(push, 1)
typedef struct { // описывает состояние приема данных
	eRcvState rcvState;			// состояние приема пакета
	uint8_t rcvByteCount;				// счетчик принятых байт пакета
} tINTERFACE_RCV_STATE;
#pragma pack(pop)

#define UART_DATA_ANSWR_MAX_SIZE		64
#pragma pack(push, 1)
typedef struct { // описывает состояние приема и обработки принятых команд
	uint16_t id;						// значение идентификатора выполняемой команды
	uint16_t timer;
	uint8_t timeEvent;					// > 0 - сработал таймер для команды (передать статус выполения команды)
	uint8_t stateData;					// процент выполнения команды или результат
	uint8_t prevStateData	:7;			// процент выполнения команды 0..100%
	uint8_t repeatCmd		:1;			// признак повтора команды
//	enum_espCmdState state;				// фаза выполнения команды
	uint8_t timeOut;					// макс. время выполнения команды, если 0xFF - не определено

	uint8_t dataUnitSize;				// размер одного элемента данных
	uint8_t dataQntt;					// к-во данных (в байтах) в буфере для ответа на команду
	uint8_t dataOffset;					// смещение на начало данных в буфере

	uint8_t nCurProc;					// номер текущего процесса (для комманд, которые выполняются не мгновенно)

	uint8_t data[UART_DATA_ANSWR_MAX_SIZE];					// циклический буфер с данными для ответа на команду
} tINTERFACE_CMD_STATE;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct { // структура заголовка команды/события
  	uint8_t	typeCmd     :7;			// класс команды/события
	uint8_t ack         :1;       	// признак ответа на команду
  	uint8_t	cmd;					// команда/событие
	uint8_t qnttArgmnts;			// количесвто аргументов в команде
} tHEAD_CMD_PCKT;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct { // структура заголовка команды/события
    tHEAD_CMD_PCKT head;

    union {
        struct {
            uint8_t	state;              // класс команды/события
            int16_t measure;
        } touch;

        int32_t signalParams;

        int16_t temperature;
        uint16_t vBat_mv;
        int32_t angle;
        uint32_t time_work;
        uint32_t mac;
        int16_t result;                 // 0 -> Ok, -1 -> error
    };
} tANSWER_PCKT;
#pragma pack(pop)

void uart_prot_proc_new ( void );
void uart_send_(uint8_t* data, uint8_t data_cnt);

#endif /* UART_PROT_NEW_H_ */