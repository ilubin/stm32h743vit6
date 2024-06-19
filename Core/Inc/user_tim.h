#ifndef __USER_TIM_H
#define __USER_TIM_H

#include "main.h"

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;

void MX_TIM5_Init(void);
void MX_TIM6_Init(void);
void MX_TIM7_Init(void);

void MX_TIM6_Init_Backup(void);

void delay_us(uint16_t us);
void delay_ms(uint16_t ms);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

#endif
