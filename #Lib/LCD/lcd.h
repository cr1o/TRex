#ifndef LCD_H_
#define LCD_H_

#include "stm32f0xx.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define D0_set() GPIOB-> ODR |= GPIO_ODR_8;
#define D1_set() GPIOB-> ODR |= GPIO_ODR_9;
#define D2_set() GPIOB-> ODR |= GPIO_ODR_10;
#define D3_set() GPIOB-> ODR |= GPIO_ODR_11;
#define D4_set() GPIOB-> ODR |= GPIO_ODR_12;
#define D5_set() GPIOB-> ODR |= GPIO_ODR_13;
#define D6_set() GPIOB-> ODR |= GPIO_ODR_14;
#define D7_set() GPIOB-> ODR |= GPIO_ODR_15;


#define D0_reset() GPIOB->ODR &= ~GPIO_ODR_8;
#define D1_reset() GPIOB->ODR &= ~GPIO_ODR_9;
#define D2_reset() GPIOB->ODR &= ~GPIO_ODR_10;
#define D3_reset() GPIOB->ODR &= ~GPIO_ODR_11;
#define D4_reset() GPIOB->ODR &= ~GPIO_ODR_12;
#define D5_reset() GPIOB->ODR &= ~GPIO_ODR_13;
#define D6_reset() GPIOB->ODR &= ~GPIO_ODR_14;
#define D7_reset() GPIOB->ODR &= ~GPIO_ODR_15;

#define E_set() GPIOA-> ODR |= GPIO_ODR_11;
#define E_reset() GPIOA->ODR &= ~GPIO_ODR_11;

#define RS_set() GPIOA-> ODR |= GPIO_ODR_9;
#define RS_reset() GPIOA->ODR &= ~GPIO_ODR_9;

#define Light_set() GPIOA-> ODR |= GPIO_ODR_8;
#define Light_reset() GPIOA->ODR &= ~GPIO_ODR_8;


void LCD_Init(void);
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_Print(char* str);
void LCD_SetPos(uint8_t x, uint8_t y);
void LCD_SetTCur(uint8_t t );
void LCD_SetLight(uint8_t lt);
void LCD_PrintASCII(uint8_t* str);
void LCD_Print80(uint8_t* str);

#endif /* LCD_H_ */
