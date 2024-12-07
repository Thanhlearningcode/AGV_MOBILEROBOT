#include "Exti.h"


void Exti_Init(void){
	RCC->APB2ENR|=(1U<<14); // System configuration controller clock enable
	RCC->AHB1ENR|=(1U<<02); // System configuration GPIOC clock enable
	RCC->AHB1ENR|=(1U<<03); // System configuration GPIOD clock enable
					/* Configure GPIOC Input */
	GPIOC->MODER &= ~(3U << 18); // Clear MODER bits for PC9 (input mode)
	GPIOD->MODER &= ~(3U << 30); // Clear MODER bits for PD15 (input mode)

			/* Configure no Pull-up & Pull-down resistors for GPIOD */
	
	GPIOC->PUPDR &= ~(3U << 18); // No pull-up, pull-down PC9
	
	GPIOD->PUPDR &= ~(3U << 30); // No pull-up, pull-down PD15

			/* Syscfg EXTI Configuration */
	SYSCFG->EXTICR[3] |= (3U << 12); // Connect PD15 to EXTI15
	SYSCFG->EXTICR[2] |= (2U << 4);  // Connect PC9 to EXTI9

	/* Configure Falling edge trigger for EXTI7 and EXTI9 */
	EXTI->RTSR |= (1U << 15); // Enable rising edge trigger for EXTI15
	EXTI->RTSR |= (1U << 9); // Enable rising edge trigger for EXTI9


/* Enable interrupt for EXTI15 and EXTI9 */
	EXTI->IMR |= (1U << 15); // Unmask EXTI line 15
	EXTI->IMR |= (1U << 9); // Unmask EXTI line 9

	EXTI->PR|=(1U<<15);
	EXTI->PR|=(1U<<9);
/*  Enable EXTI interrupt in NVIC */
 NVIC_SetPriority(EXTI15_10_IRQn, 2);
  NVIC_SetPriority(EXTI9_5_IRQn, 1);
NVIC_EnableIRQ(EXTI9_5_IRQn); // Enable IRQ handler for EXTI lines [9:5]
NVIC_EnableIRQ(EXTI15_10_IRQn);
}	
