#include "dma.h"
#define SYNC 0xEE


 uint16_t len = 5;
 uint16_t adc1_for_dma[1024];
 char myString[1024*7];

void int2chr(uint16_t number, char* buff){
	uint16_t num = number;
	for(int i = 3; i > -1; i--){
		int a = num % 10;
		buff[i] = a + '0';
		num = num/10;
	}
	buff[4] = ' ';
}

void convert_data2str(){
	for(uint32_t i = 0, j = 0; j < len; j++, i = i + 7){
		myString[i] = SYNC;
		myString[i+1] = 0x00;
		int2chr(adc1_for_dma[j], &myString[i+2]);
	}
}

void dma1_init_for_adc1(){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel1->CCR |= DMA_CCR_MINC | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_TCIE;

	NVIC_SetPriority(DMA1_Channel1_IRQn, 0x01);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	ADC1->CFGR |= ADC_CFGR_DMACFG;
	ADC1->CFGR |= ADC_CFGR_DMAEN;
}

void dma1_init_for_usart2(){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel7->CCR |= DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE;

	NVIC_SetPriority(DMA1_Channel7_IRQn, 0x02);
	NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

void dma1_ch1_en(){
	DMA1_Channel1->CCR &= ~DMA_CCR_EN;
	DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
	DMA1_Channel1->CMAR = (uint32_t)&adc1_for_dma;
	DMA1_Channel1->CNDTR = len;
	DMA1_Channel1->CCR |= DMA_CCR_EN;

}

void dma1_ch7_en(){
	DMA1_Channel7->CCR &= ~DMA_CCR_EN;
	DMA1_Channel7->CNDTR = len*7;
	DMA1_Channel7->CPAR = (uint32_t)&USART2->TDR;
	DMA1_Channel7->CMAR = (uint32_t)myString;
	DMA1_Channel7->CCR |= DMA_CCR_EN;
}
/*
 * dma.c
 *
 *  Created on: 10 θών. 2025 γ.
 *      Author: User
 */


