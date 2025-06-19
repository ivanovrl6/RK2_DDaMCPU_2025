

/*
 * dma.h
 *
 *  Created on: 10 θών. 2025 γ.
 *      Author: User
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32f3xx.h"
#include "string.h"
#include "usart.h"

void dma1_init_for_usart2();
void dma1_init_for_adc1();
void dma1_ch7_en();
void dma1_ch1_en();
void convert_data2str();
void int2chr(uint16_t number, char* buff);


#endif /* DMA_H_ */
