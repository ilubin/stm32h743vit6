#include "user_rtc.h"

RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef     User_RTC_Time;
RTC_DateTypeDef     User_RTC_Date;
User_RTC_TypeDef    User_RTC;

void MX_RTC_Init(void)
{

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  sTime.Hours = 0x12;
  sTime.Minutes = 0x50;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_SATURDAY;
  sDate.Month = RTC_MONTH_JUNE;
  sDate.Date = 0x8;
  sDate.Year = 0x24;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(rtcHandle->Instance==RTC)
  {
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_RTC_ENABLE();
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
    __HAL_RCC_RTC_DISABLE();
  }
}

static void User_RTC_Time_Get(User_RTC_TypeDef *rtc){
  HAL_RTC_GetTime(&hrtc,&User_RTC_Time,RTC_FORMAT_BCD);
  HAL_RTC_GetDate(&hrtc,&User_RTC_Date,RTC_FORMAT_BCD);
  rtc->seconds = (User_RTC_Time.Seconds / 16) * 10 + (User_RTC_Time.Seconds % 16);
  rtc->minutes = (User_RTC_Time.Minutes / 16) * 10 + (User_RTC_Time.Minutes % 16);
  rtc->hours = (User_RTC_Time.Hours / 16) * 10 + (User_RTC_Time.Hours % 16);
  rtc->weekday = (User_RTC_Date.WeekDay / 16) * 10 + (User_RTC_Date.WeekDay % 16);
  rtc->date = (User_RTC_Date.Date / 16) * 10 + (User_RTC_Date.Date % 16);
  rtc->month = (User_RTC_Date.Month / 16) * 10 + (User_RTC_Date.Month % 16);
  rtc->year = 20 * 100 + (User_RTC_Date.Year / 16) * 10 + (User_RTC_Date.Year % 16);
}

//static uint8_t rtc_bcd_value(uint16_t value){
//	uint8_t temp[2] = {0};
//	temp[0] = (value % 100) / 10;
//	temp[1] = ((value % 100) % 10);
//	return temp[0]*16 + temp[1];
//}

//static void rtc_set_bcd_value(RTC_TimeTypeDef *rtc_time, RTC_DateTypeDef *rtc_date){
//	rtc_date->Year = rtc_bcd_value(rtc_date->Year);
//	rtc_date->Month = rtc_bcd_value(rtc_date->Month);
//	rtc_date->Date = rtc_bcd_value(rtc_date->Date);
//	rtc_date->WeekDay = rtc_bcd_value(rtc_date->WeekDay);
//	rtc_time->Hours = rtc_bcd_value(rtc_time->Hours);
//	rtc_time->Minutes = rtc_bcd_value(rtc_time->Minutes);
//	rtc_time->Seconds = rtc_bcd_value(rtc_time->Seconds);
//}

void User_UART_Send_RTC(void){
  User_RTC_Time_Get(&User_RTC);
  printf("[ %d:%d:%d:%d:%d:%d ]",User_RTC.year,User_RTC.month,User_RTC.date,User_RTC.hours,User_RTC.minutes,User_RTC.seconds);
}
