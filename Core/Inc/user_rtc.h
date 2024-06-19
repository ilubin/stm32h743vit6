#ifndef __USER_RTC_H
#define __USER_RTC_H

#include "main.h"

typedef struct{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t weekday;
  uint8_t date;
  uint8_t month;
  uint16_t year;
}User_RTC_TypeDef;

extern RTC_HandleTypeDef hrtc;

void MX_RTC_Init(void);
static void User_RTC_Time_Get(User_RTC_TypeDef *rtc);
static uint8_t rtc_bcd_value(uint16_t value);
static void rtc_set_bcd_value(RTC_TimeTypeDef *rtc_time, RTC_DateTypeDef *rtc_date);
void User_UART_Send_RTC(void);

#endif
