/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-June-2014
  * @brief   This example describes how to configure and use GPIOs through 
  *          the STM32F3xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "usart.h"
#include "stdint.h"
#include "dma.h"

volatile uint8_t dma_w = 0;
int pause = 600000;

void gpioe_init(){
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODER13_0;
	GPIOE->MODER |= GPIO_MODER_MODER13_0;
}


void fl2ch(float number, char* buff){
	int num = (int)(number * 100);
	for(int i=4;i>-1;i--){
		if(i==2){
			buff[i] = '.';
		}
		else{
			int a = num % 10;
			buff[i] ='0' + a;
			num = num/10;
		}
	}
	buff[5] = ' ';
	buff[6] = '\0';
}

void int2ch(int number, char* buff){
	int num = number;
	for(int i = 3; i > -1; i--){
		int a = num % 10;
		buff[i] ='0' + a;
		num = num/10;
	}
	buff[4] = ' ';
}
void gpioa_init(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER0;
}
int main(void)
{
	gpioa_init();
	usart2_init();
	adc_init();
	dma1_init_for_adc1();
	dma1_init_for_usart2();
	dma1_ch7_en();
	dma1_ch1_en();

}
void ADC1_2_IRQHandler(){
	if(ADC1->ISR & ADC_ISR_EOS){

	}
}
void USART2_IRQHandler() {
	if (USART2->ISR & USART_ISR_RXNE) {
	        if(USART2->RDR == 0xEE){

	        }
	 }
}

void DMA1_Channel7_IRQHandler(){
	if(DMA1->ISR & DMA_ISR_TCIF7){
		DMA1->IFCR |= DMA_IFCR_CTCIF7;
		delay(pause);
		dma1_ch7_en();

	}
}

void DMA1_Channel1_IRQHandler(){
	if(DMA1->ISR & DMA_ISR_TCIF1){
		DMA1->IFCR |= DMA_IFCR_CTCIF1;
		convert_data2str();
		dma1_ch1_en();

	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
