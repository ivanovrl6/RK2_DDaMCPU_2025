#include "adc.h"

uint16_t adc1_channel_select = 0x00;

void delay(int time){
	for(int i=0; i < time; i++);
}

void adc_calibrate_single(){

	if (ADC1->CR & ADC_CR_ADEN) {
	        ADC1->CR |= ADC_CR_ADDIS;
	        while (ADC1->CR & ADC_CR_ADEN);
	 }

	ADC1->CR |= ADC_CR_ADCAL;
	delay(100);
}

void ADVREGEN_OFF(){
	ADC1->CR &= ~ADC_CR_ADVREGEN;
	delay(100);
	ADC1->CR |= ADC_CR_ADVREGEN_1;

}

void ADVREGEN_ON(){
	ADC1->CR &= ~ADC_CR_ADVREGEN;
	delay(100);
	ADC1->CR |= ADC_CR_ADVREGEN_0;
}

void adc_init(){

	RCC->AHBENR |= RCC_AHBENR_ADC12EN;
	ADC1_2_COMMON->CCR |= ADC12_CCR_CKMODE_1;
	//RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV16;


	ADVREGEN_ON();

	adc_calibrate_single();

	ADC1->CFGR |= ADC_CFGR_CONT;

	ADC1->SQR1  &= ~ADC_SQR1_L;
	ADC1->SQR1 |= ADC_SQR1_SQ1_0;

	ADC1->SMPR1 |= ADC_SMPR1_SMP1;

	ADC1->IER |= ADC_IER_EOS;
	//ADC1->SMPR2 |= ADC_SMPR2_SMP16;
	//ADC1_2_COMMON->CCR |= ADC12_CCR_TSEN;
	NVIC_SetPriority(ADC1_2_IRQn, 0x01);
	NVIC_EnableIRQ(ADC1_2_IRQn);

	ADC1->CFGR &= ~ADC_CFGR_RES;

	ADC1->CFGR |= ADC_CFGR_DMAEN;

	ADC1->CR |= ADC_CR_ADEN;
	delay(100);
	ADC1->CR |= ADC_CR_ADSTART;
}


void pll_init(){
	RCC->CR &= ~RCC_CR_PLLON;

	RCC->CIR |= RCC_CIR_PLLRDYIE;
	delay(100);
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_DIV2;

	RCC->CFGR |= RCC_CFGR_PLLMUL16;
}

/*
 * adc.c
 *
 *  Created on: 9 θών. 2025 γ.
 *      Author: User
 */


