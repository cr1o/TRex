#include "stm32f0xx.h"
#include "ADC.h"

void ADC_Init (void) {
		
		//RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  //enable timing on ADC
		//RCC->APB2ENR |=RCC_APB2ENR_IOPAEN; //fds
		RCC->APB2ENR |= RCC_APB2ENR_ADCEN;   //enable timing on ADC
		RCC->AHBENR |=RCC_AHBENR_GPIOAEN;    //enable timing on GPIOA
		
		
		GPIOA->MODER &= ~GPIO_MODER_MODER0_Msk; //PA0 - Reset function
		GPIOA->MODER|= GPIO_MODER_MODER0_1; //PA0 - Alternative funtion		

		RCC->CFGR2 |= RCC_CFGR_ADCPRE_DIV4; //Prescaller SystemCoreClock /4   48Mhz/4 = 12Mhz	
		
		ADC1->CR |= ADC_CR_ADCAL; 								//Start calibration
		
		while ((ADC1->CR & ADC_CR_ADCAL) != 0) 		//Waiting calibration
		{
			/* For robust implementation, add here time-out management */
		}	
	
		ADC1->CHSELR |= ADC_CHSELR_CHSEL0;	//Input Channel-x is selected for conversion
						
		ADC1->CR |= ADC_CR_ADEN; 									//ADC enable
		while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) //waiting until ADC will be ready
		{
			/* For robust implementation, add here time-out management */
		}
	
		ADC1->CFGR1 &= ~ADC_CFGR1_CONT; 		//0-single conversation; 1-Continuous conv.
		ADC1->CFGR1 &= ~ADC_CFGR1_EXTEN; 		//EFGR1->EXTEN 00: Hardware trigger detection disabled (conversions can be started by software)
		ADC1->SMPR |= ADC_SMPR_SMP_Msk;     //239.5 ADC clock cycles
	
}
