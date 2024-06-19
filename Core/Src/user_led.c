#include "user_led.h"

extern TIM_HandleTypeDef htim5;

void LED_Green_Set_Brightness(uint8_t brightness){
  HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Stop(&htim5, TIM_CHANNEL_1);
  TIM5->CCR1 = brightness * 100;
  HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim5, TIM_CHANNEL_1);
}

void LED_Blue_Set_Brightness(uint8_t brightness){
  HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Stop(&htim5, TIM_CHANNEL_2);
  TIM5->CCR2 = brightness * 100;
  HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim5, TIM_CHANNEL_2);
}
