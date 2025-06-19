
/*
 * adc.h
 *
 *  Created on: 9 θών. 2025 γ.
 *      Author: User
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f3xx.h"

void delay(int time);
void adc_calibrate_single();
void ADVREGEN_OFF();
void ADVREGEN_ON();
void adc_init();

void pll_init();




#endif /* ADC_H_ */
