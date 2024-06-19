#include "user_key.h"
#include "user_tim.h"

uint8_t touch_flag = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  delay_ms(10);
  if(HAL_GPIO_ReadPin(Touch_IN_GPIO_Port, Touch_IN_Pin) == GPIO_PIN_SET){
    touch_flag = 1;
  }
  else{
    
  }
}
