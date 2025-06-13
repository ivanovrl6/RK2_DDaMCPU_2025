#include "dma.h"


void dma1_init(){
	char myString[] = "Hello World";
	uint8_t len = strlen(myString);
	uint8_t count = 0;

	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	USART2->CR3 |= USART_CR3_DMAT;

	DMA1_Channel7->CNDTR = len;
	DMA1_Channel7->CCR |= DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_CIRC;

	DMA1_Channel7->CPAR = (uint32_t)&USART2->TDR;
	DMA1_Channel7->CMAR = (uint32_t)myString;

	usart2_init();
}
/*
 * dma.c
 *
 *  Created on: 10 θών. 2025 γ.
 *      Author: User
 */


