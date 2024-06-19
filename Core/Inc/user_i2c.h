#ifndef __USER_I2C_H
#define __USER_I2C_H

#include "main.h"

#define HAL_I2C_TIMEOUT_DEFAULT_VALUE   5000

extern I2C_HandleTypeDef hi2c1;

void MX_I2C1_Init(void);

#endif
