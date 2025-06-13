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

static float temp;

void gpioe_init(){
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODER13_0;
	GPIOE->MODER |= GPIO_MODER_MODER13_0;
}

void ADC_1_2_IRQHandler(void){
	if(ADC1->ISR & ADC_ISR_EOC){
		temp = (float)(25 - ADC1->DR) + 25;
	}
}

int main(void)
{
¸	char myString[] = "Hello World";
	uint8_t len = strlen(myString);
	uint8_t count = 0;
	usart2_init();
		while(count<len){
			if(USART2->ISR & USART_ISR_TXE){
				USART2->TDR = myString[count++];
			}
		}

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
