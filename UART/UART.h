#ifndef UART_H_
#define UART_H_


#include "stm32f0xx.h"



void UART2_Init(void);
void USART2_Send (char chr);
void USART2_Send_Str (char* str);

void UART1_Init(void);
void USART1_Send (char chr);

#endif /* UART_H_ */
