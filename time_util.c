#include <stdint.h>
#include <stdio.h>
#include "time_util.h"

//날짜                    x, 1월, 2월 ..... 11월, 12월
uint8_t month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//타임 스탬프를 기준으로 요일 얻기
uint8_t timestamp_to_weekday(timestamp_t timestamp_sec)
{
	uint8_t result = (timestamp_sec / ONE_DAY + UTC_TIME_WEEKDAY_OFFSET) % 7;
	if (result == 0) {
		result = 7;
	}
	return result;
}

//intercalation month
int is_leap_year(uint16_t year)
{
	if (year % 4 == 0 && (((year % 100) != 0) || ((year % 400) == 0))) {
		return true;
	}
	else
		return false;
}

//convert utc time stampe to date
void utc_timestamp_to_date(timestamp_t timestamp, datetime_t* datetime)
{
	uint8_t  month;
	uint32_t days;
	uint16_t days_in_year;
	uint16_t year;
	timestamp_t second_in_day;

    // calculation day/hour/min
	second_in_day = timestamp % ONE_DAY;

	//second
	datetime->second = second_in_day % 60;

	//minute
	second_in_day /= 60;
	datetime->minute = second_in_day % 60;

	//hour
	second_in_day /= 60;
	datetime->hour = second_in_day % 24;
	

	//total days from 1970-1-1 0:0:0 to now 
	days = timestamp / ONE_DAY;
	
	//find year
	for (year = 1970; year <= 2200; year++) {
		if (is_leap_year(year))
			days_in_year = 366;
		else
			days_in_year = 365;

		if (days >= days_in_year)
			days -= days_in_year;
		else
			break;
	}
	
	//year
	datetime->year = year;

	//weekday
	datetime->weekday = timestamp_to_weekday(timestamp);

	//number of week in this year
	datetime->week = (days + 11 - datetime->weekday) / 7;

	//month
	if (is_leap_year(datetime->year)) //윤달의 경우 2월이 29일이다.
		month_days[2] = 29; 
	else
		month_days[2] = 28;

	//find month
	for (month = 1; month <= 12; month++) {
		if (days >= month_days[month])
			days -= month_days[month];
		else
			break;
	}
	datetime->month = month;
	datetime->day = days + 1;
}


datetime_t time_unix2kst(uint32_t time)
{
	// timestamp_t unix_timestamp = 1615546840;
    timestamp_t unix_timestamp = time;
	datetime_t datetime;
    
	utc_timestamp_to_date(unix_timestamp , &datetime);
    datetime.hour += 9; // time gap between seoul and UTC
	//LOG_INF("unix time : %d\n",unix_timestamp );
	//LOG_INF("datetime : %d-%d-%d(%d, %d)_%d:%d:%d\n",datetime.year, datetime.month, datetime.day, datetime.week, datetime.weekday, datetime.hour, datetime.minute, datetime.second);	
    return datetime;
}

void kst_time(char *time_str, uint32_t time)
{   
	datetime_t d;
    
	utc_timestamp_to_date((timestamp_t)time , &d);
    d.hour += 9; // time gap between seoul and UTC

	sprintf(time_str, "%d-%d-%d(%d, %d) %d:%d:%d",
	       d.year, d.month, d.day, d.week, d.weekday, d.hour, d.minute, d.second);	
}

uint32_t swap32(uint32_t data) {
	return ((data >> 16) | (data << 16));
}
