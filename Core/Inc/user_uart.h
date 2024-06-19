#ifndef __USER_UART_H
#define __USER_UART_H

#include "main.h"

#define USER_UART1_BUADRATE    115200
#define USER_UART1_PARITY      UART_PARITY_NONE

#if (USER_UART1_PARITY == UART_PARITY_NONE)
#define USER_UART1_WORDLENGTH UART_WORDLENGTH_8B
#elif ((USER_UART1_PARITY == UART_PARITY_ODD) || (USER_UART1_PARITY == UART_PARITY_EVEN))
#define USER_UART1_WORDLENGTH UART_WORDLENGTH_9B
#endif

void MX_UART1_Init(void);
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);
size_t __write(int handle, const unsigned char * buffer, size_t size);

#endif
