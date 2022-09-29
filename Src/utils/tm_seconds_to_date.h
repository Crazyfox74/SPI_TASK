#ifndef UTILS_TM_SECONDS_TO_DATE_H_
#define UTILS_TM_SECONDS_TO_DATE_H_

#include <stdint.h>

typedef struct {     // struct. members are date
    uint16_t year;   // time infos.
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} DateTime;

int ts_to_datetime(unsigned long secs, DateTime *datetime);

#endif /* UTILS_TM_SECONDS_TO_DATE_H_ */
