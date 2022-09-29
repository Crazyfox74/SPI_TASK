#ifndef UART_PROT_NEW_H_
#define UART_PROT_NEW_H_

#include <stdint.h>

typedef enum { // ������ ������
  	UART_CMD_TYPE_NONE = 0,
  	UART_CMD_TYPE_METROLOGY,
  	UART_CMD_TYPE_SERVICE_DATA,
	UART_CMD_TYPE_LOG,
	UART_CMD_TYPE_BOOT,

} eTypeCmd;

typedef enum { // ������������ ������ ���� METROLOGY
	UART_CMD_WRITE_COEF_L = 0,
	UART_CMD_READ_COEF_L,
	UART_CMD_WRITE_COEF_A,
	UART_CMD_READ_COEF_A,
	UART_CMD_SAVE_COEF,
	UART_CMD_READ_VOLUME,
	UART_CMD_READ_ZERO,
	UART_CMD_SEARCH_ZERO,

} eMetrologyCmd;

typedef enum { // ������������ ������ ���� SERVICE_DATA
	UART_CMD_READ_VOLTAGE = 0,
	UART_CMD_READ_TEMPERATURE,
	UART_CMD_READ_ANGLE,
	UART_CMD_READ_TIME_WORK,
	UART_CMD_READ_MAC,
    UART_CMD_READ_TOUCH_STATUS,
    UART_CMD_CHECK_FLASH,
    UART_CMD_CHECK_FLASH_VCC,
    UART_CMD_SET_LCD_MODE,          // ������� �������� ���������� �������� �� ���
    UART_CMD_SET_SLEEP_MODE,        // ��������� ������� �� �������� ����� (1..30 ������) � ����� SLEEP
    UART_CMD_TEST_48MHz,            // ���/����� ������ �� ��� Block �������� ������� 48 MHz
    UART_CMD_GET_SIGNAL_PARAMS,     // ������� ��� ��������� ���������� �������� � �� ��������
    UART_CMD_TEST_26MHz,            // ���/����� TCXO ��� ��������� ��� ������� 26 MHz (��������� � ����� ������ SDC)
    UART_CMD_TEST_TX,               // ���/���� ���������� � ����� �������� (NBFI/SigFox)

} eServiceDataCmd;

typedef enum { // ������������ ������ ���� LOG
	UART_CMD_READ_LOG = 0,

} eLogCmd;

typedef enum { // ������ ������ ������
	UART_RX_WAIT_START = 0,				// ���� ��������� ���� ������
	UART_RX_IN_PROGRESS,				// ������� ������ ������
	UART_RX_UNSTUFF,					// unstuff � �������� ������ ������
	UART_RX_COMPLETED					// ����� ������ ��������
} eRcvState;


#pragma pack(push, 1)
typedef struct { // ��������� ��������� ������ ������
	eRcvState rcvState;			// ��������� ������ ������
	uint8_t rcvByteCount;				// ������� �������� ���� ������
} tINTERFACE_RCV_STATE;
#pragma pack(pop)

#define UART_DATA_ANSWR_MAX_SIZE		64
#pragma pack(push, 1)
typedef struct { // ��������� ��������� ������ � ��������� �������� ������
	uint16_t id;						// �������� �������������� ����������� �������
	uint16_t timer;
	uint8_t timeEvent;					// > 0 - �������� ������ ��� ������� (�������� ������ ��������� �������)
	uint8_t stateData;					// ������� ���������� ������� ��� ���������
	uint8_t prevStateData	:7;			// ������� ���������� ������� 0..100%
	uint8_t repeatCmd		:1;			// ������� ������� �������
//	enum_espCmdState state;				// ���� ���������� �������
	uint8_t timeOut;					// ����. ����� ���������� �������, ���� 0xFF - �� ����������

	uint8_t dataUnitSize;				// ������ ������ �������� ������
	uint8_t dataQntt;					// �-�� ������ (� ������) � ������ ��� ������ �� �������
	uint8_t dataOffset;					// �������� �� ������ ������ � ������

	uint8_t nCurProc;					// ����� �������� �������� (��� �������, ������� ����������� �� ���������)

	uint8_t data[UART_DATA_ANSWR_MAX_SIZE];					// ����������� ����� � ������� ��� ������ �� �������
} tINTERFACE_CMD_STATE;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct { // ��������� ��������� �������/�������
  	uint8_t	typeCmd     :7;			// ����� �������/�������
	uint8_t ack         :1;       	// ������� ������ �� �������
  	uint8_t	cmd;					// �������/�������
	uint8_t qnttArgmnts;			// ���������� ���������� � �������
} tHEAD_CMD_PCKT;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct { // ��������� ��������� �������/�������
    tHEAD_CMD_PCKT head;

    union {
        struct {
            uint8_t	state;              // ����� �������/�������
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