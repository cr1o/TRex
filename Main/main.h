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
	uint16_t tAcceleration;		//���������� ����� �������. ��� 10��
	uint16_t perStartPWM;		//%�� ������������� ���������� �������� � �������� ���������� ������
	uint16_t perMaxPWM;			//�������� ��������. (% �� ������������ ��������)
	uint16_t StepSize;			//���������� ������ ����

	uint16_t StepSizeF;			//���������� ������ ����

	uint16_t curStep;			//������� ��� �������/����������
	uint16_t M_EN;
	uint16_t M_PWM;
} motor;

//--------------------------  Variable   ----------------------------------
volatile motor m[NUMBER_OF_MOTOR];
//--------------------------  Functions   ----------------------------------
void delay(uint32_t ms);

#endif /* MAIN_H_ */
