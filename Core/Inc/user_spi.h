#ifndef __USER_SPI_H
#define __USER_SPI_H

#include "main.h"

#define HAL_SPI_TIMEOUT_DEFAULT_VALUE   5000

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi4;

void MX_SPI1_Init(void);
void MX_SPI2_Init(void);
void MX_SPI4_Init(void);

#endif
