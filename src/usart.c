#include "usart.h"

void usart2_gpio_init(){
	RCC->AHBENR|= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR|= RCC_APB1ENR_USART2EN;
	GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
	GPIOA->AFR[0] &= ~(0xF << (4 * 2));
	GPIOA->AFR[0] &= ~(0xF << (4 *3));
	GPIOA->AFR[0] |=  (7 << (4 * 2));
	GPIOA->AFR[0] |=  (7 << (4 * 3));
}

void usart2_init(){

	usart2_gpio_init();

	USART2->CR1 &= ~USART_CR1_M;

	USART2->BRR = SystemCoreClock / 115200;

	USART2->CR2 &= ~USART_CR2_STOP;

	USART2->CR1 |= USART_CR1_UE|USART_CR1_TE|USART_CR1_RE;

}
/*
 * usart.c
 *
 *  Created on: 9 θών. 2025 γ.
 *      Author: User
 */


