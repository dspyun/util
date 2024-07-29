#pragma once



typedef uint32_t timestamp_t; //seconds

// datetime struct
typedef struct {
	uint16_t    year;
	uint8_t     month; 
	uint8_t     day;   
	uint8_t     hour;  
	uint8_t     minute;
	uint8_t     second;
	uint8_t     week; 
	uint8_t     weekday;
} datetime_t;

// 1day to seconds
#define ONE_DAY                  (1*60*60*24) 
// UTC start time
#define UTC_TIME_WEEKDAY_OFFSET (4) /* 1970,1,1 is thursday */

#define true 1
#define false 0

datetime_t time_unix2kst(uint32_t time);
void kst_time(char *time_str, uint32_t time);
