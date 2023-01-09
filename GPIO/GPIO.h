#ifndef GPIO_H_
#define GPIO_H_

#define SENSOR1 ((GPIOB->IDR & GPIO_IDR_9) == 0 )

#define SENSOR2 ((GPIOC->IDR & GPIO_IDR_14) == 0 )
#define SENSOR3 ((GPIOC->IDR & GPIO_IDR_13) == 0 )
#define SENSOR4 ((GPIOB->IDR & GPIO_IDR_7) == 0 )
#define SENSOR5 ((GPIOB->IDR & GPIO_IDR_6) == 0 )

#include "stm32f0xx.h"
#include "main.h"

void PWM_Init(void);
void RCC_Init(void);
void GPIO_Init(void);
void Motor_Init(void);
void LEDtst(void);

#endif /* GPIO_H_ */
