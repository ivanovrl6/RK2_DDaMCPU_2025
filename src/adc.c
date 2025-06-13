#include "adc.h"

void delay(int time){
	for(int i=0; i < time; i++);
}

void adc_calibrate_single(){

	if (ADC1->CR & ADC_CR_ADEN) {
	        ADC1->CR |= ADC_CR_ADDIS;
	        while (ADC1->CR & ADC_CR_ADEN);
	 }

	ADC1->CR |= ADC_CR_ADCAL;
	while (ADC1->CR & ADC_CR_ADCAL);
}

void ADVREGEN_OFF(){
	ADC1->CR &= ~ADC_CR_ADVREGEN;
	delay(100);
	ADC1->CR |= ADC_CR_ADVREGEN_1;

}

void ADVREGEN_ON(){
	ADC1->CR &= ~ADC_CR_ADVREGEN;
	delay(10000);
	ADC1->CR |= ADC_CR_ADVREGEN_0;
}

void adc_init(){

	RCC->AHBENR |= RCC_AHBENR_ADC12EN;
	ADC1_2_COMMON->CCR |= ADC12_CCR_CKMODE_1;
	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV16;

	ADVREGEN_ON();

	adc_calibrate_single();

	ADC1->CFGR |= ADC_CFGR_CONT;
	ADC1->SQR1 |= ADC_SQR1_SQ1_4;
	ADC1->SMPR2 |= ADC_SMPR2_SMP16;
	ADC1->CFGR &= ~ADC_CFGR_RES;

	ADC1->IER |= ADC_IER_EOC;
	NVIC_EnableIRQ(ADC1_2_IRQn);

	ADC1_2_COMMON->CCR |= ADC12_CCR_TSEN;
	ADC1->CR |= ADC_CR_ADEN;
	while (!(ADC1->ISR & ADC_ISR_ADRD));

	ADC1->CR |= ADC_CR_ADSTART;
}


/*
 * adc.c
 *
 *  Created on: 9 θών. 2025 γ.
 *      Author: User
 */


