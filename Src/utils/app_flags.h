#ifndef __APP_FLAGS_H
#define __APP_FLGS_H

typedef struct {
	uint16_t SecondHasPassed : 1;
	uint16_t DayHasPassed : 1;
	uint16_t WeekHasPassed : 1;
    uint16_t MonthHasPassed : 1;
	uint16_t RadioTransmissionInProgress : 1;
    uint16_t BlowIsActive : 1;
    uint16_t BlowCountEnable : 1;
    uint16_t ResetDetected : 1;

    uint16_t reserved : 8;
} ApplicationEventFlags_t;

typedef struct {
	uint8_t SenseAdcTmprtrScheduled : 1;
	uint8_t RadioTransmissionScheduled : 1;
	uint8_t ModeChangeScheduled : 1;
    uint8_t VolumeStorageScheduled : 1;
    uint8_t ErrorsTimeStorageScheduled : 1;
    uint8_t reserved : 3;

    uint8_t SenseAdcTxVbatScheduled;
} ApplicationScheduler_t;

//bool gmm_countIsEnable();

#endif
