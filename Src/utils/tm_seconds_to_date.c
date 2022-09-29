#include "tm_seconds_to_date.h"

int ts_to_datetime(unsigned long secs, DateTime *datetime){
	int num_of_leap=0;
	datetime->second = secs % 60;
	datetime->minute = (secs /60)%60;
	datetime->hour = (secs % 86400)/3600;

	int temp_x;
	long sec_in_year=365*24*60*60;
	int day_of_year;

	datetime->year =1970 + secs / sec_in_year;

	int passed_years = datetime->year-1900;
	day_of_year = (secs % (31536000)) / 86400 -((passed_years-69)/4) + ((passed_years-1)/100) - ((passed_years+299)/400)+1;

	uint8_t val = (datetime->year % 4 == 0 && datetime->year % 100 != 0) || (datetime->year % 400 == 0);
	int mo[12] = {31, 28 + val, 31,30,31,30,31,31,30,31,30,31};
	int	 i=0;
	temp_x=0;
	int kk=1970;
	while(kk<datetime->year){
		num_of_leap +=  (kk % 4 == 0 && kk % 100 != 0) || (kk % 400 == 0);
		kk++;
	}

	while(i<12){
		temp_x += mo[i];
		if(day_of_year <temp_x)
			break;
		i++;
	}
	if( (temp_x+ num_of_leap)>366){
	}

			datetime->month = i+1;

int tt= day_of_year -temp_x + mo[i];
		if( tt < 0){
			tt += 31;
			datetime->month =12;
			datetime->year -=1;

		}
		datetime->day = tt;

		if(datetime->day ==0){

			datetime->day =mo[i-1];
			datetime->month =i;

			if ( datetime->month == 0){

				datetime->day =31;
				datetime->year -=1;
				datetime->month =12;
			}

		}

	return day_of_year;
}
