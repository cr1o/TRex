#ifndef MAIN_H_
#define MAIN_H_

//--------------------------   Lib   -------------------------------------
#include "stm32f0xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "UART.h"
#include "GPIO.h"
#include "DFPlayer.h"

//------------------------   Defines   -----------------------------------
#define NUMBER_OF_MOTOR		8
#define TIME_STEP 			10

typedef struct {
	uint8_t EN;
	uint8_t Start;
	uint16_t tAcceleration;		// оличество шагов разгона. Ўаг 10мс
	uint16_t perStartPWM;		//%от максимального количества оборотов с которого начинаетс€ разгон
	uint16_t perMaxPWM;			//«аданна€ скорость. (% от максимальных оборотов)
	uint16_t StepSize;			//–ассчетный размер шага

	uint16_t StepSizeF;			//–ассчетный размер шага

	uint16_t curStep;			//“екущий шаг разгона/торможени€
	uint16_t M_EN;
	uint16_t M_PWM;
} motor;

//--------------------------  Variable   ----------------------------------
volatile motor m[NUMBER_OF_MOTOR];
//--------------------------  Functions   ----------------------------------
void delay(uint32_t ms);

#endif /* MAIN_H_ */
