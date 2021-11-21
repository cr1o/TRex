#include "UART.h"


//------------------------------------------------------------------------
//---------------------------   UART init   -------------------------------
//------------------------------------------------------------------------
void UART2_Init(void){
	;
}

void UART1_Init(void){
		RCC->AHBENR|= RCC_AHBENR_GPIOAEN; 		//Clock Enable Port B
		RCC->APB2ENR|= RCC_APB2ENR_USART1EN; 	//USART1 clock enable

		// INIT TX (PA9) Alternative PUSH PULL
		GPIOA ->MODER |= GPIO_MODER_MODER9_1; 	// Alternative
		GPIOA ->OTYPER &= ~GPIO_OTYPER_OT_9;  	// PUSH PULL

		//GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_Msk;
		//GPIOA->AFR[0] |= (0x01<< 2*4);

		// INIT RX (PA10) Alternative OPEN DRAIN INPUT
		GPIOA ->MODER |= GPIO_MODER_MODER10_1; //Alternative
		GPIOA ->OTYPER |= GPIO_OTYPER_OT_10; // "RX" - OPEN DRAIN

		//UART_BRR = (Fck + baudrate/2)/baudrate;  Fck - clock AHBENR
		//(8 000 000 + 4800)/9600 = 833 (0x341)
		USART1->BRR = 0x6D4; //Baud rate 9600.

		USART1->CR1 |= USART_CR1_RE; //Receiver Enable
		USART1->CR1 |= USART_CR1_TE; //Transmitter Enable
		USART1->CR1 |= USART_CR1_UE; //USART Enable

}

//------------------------------------------------------------------------
void USART2_Send (char chr)
{
	while(!( USART2->ISR & USART_ISR_TC)); //Wait, until transmit not complete
	USART2->TDR = chr;
}
//------------------------------------------------------------------------
void USART1_Send (char chr)
{
	while(!( USART1->ISR & USART_ISR_TC)); //Wait, until transmit not complete
	USART1->TDR = chr;
}
//------------------------------------------------------------------------
void USART2_Send_Str (char* str)
{
	uint8_t i = 0;

	while(str[i])
	USART2_Send (str[i++]);
}



