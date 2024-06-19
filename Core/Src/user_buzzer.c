#include "user_buzzer.h"
#include "user_tim.h"

extern TIM_HandleTypeDef htim5;

void BZ_Set_PWM_Loader(uint8_t loader){
  
  TIM_OC_InitTypeDef sConfigOC = {0};
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
//  HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_2);
//  HAL_TIMEx_PWMN_Stop(&htim5, TIM_CHANNEL_2);
  
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = loader * 100;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  
  GPIO_InitStruct.Pin = BZ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
  HAL_GPIO_Init(BZ_GPIO_Port, &GPIO_InitStruct);
  
//  TIM5->CCR1 = brightness * 100;
  HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim5, TIM_CHANNEL_2);
  delay_ms(30);
  HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Stop(&htim5, TIM_CHANNEL_2);
}
