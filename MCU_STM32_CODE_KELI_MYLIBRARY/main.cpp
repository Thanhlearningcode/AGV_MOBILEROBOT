/***************************************************************************
 * @file    main.cpp
 * @brief   Main program for the AGV (Autonomous Guided Vehicle) project
 * @details This file serves as the core of the AGV system, providing the primary
 *          interface and functionalities required for autonomous navigation and control.
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH && PHAN DANG DANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 *****************************************************************************************************/
#include "main.h"
#include "mainpp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Rcc_init(void);
int main(void)
{
	
	/* Configure RCC to 72MHZ */
	Rcc_init();

   setup();
  
  while (1)
  {
   
	  loop();
    
  }

}
void Rcc_init(void){

RCC->CR |= RCC_CR_HSEON; // Turn on HSE
	    while ( !( RCC->CR & RCC_CR_HSERDY ) ); // Wait until HSE is ready

	    // Step 2: Configure PLL
	    RCC->PLLCFGR = 0; // Reset PLL Configuration Register
	    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; // Select HSE as PLL source
	    RCC->PLLCFGR |= ( 8   << RCC_PLLCFGR_PLLM_Pos ); // Set PLLM to 8 (HSE / 8)
	    RCC->PLLCFGR |= ( 144 << RCC_PLLCFGR_PLLN_Pos ); // Set PLLN to 144 (HSE / 8 * 144 / 1 = 72 MHz)
	    RCC->PLLCFGR |= ( RCC_PLLCFGR_PLLP_0 ); // Set PLLP to 2 (PLLCLK = PLLN / PLLP = 72 MHz)

	    // Step 3: Enable PLL
	    RCC->CR |= RCC_CR_PLLON; // Turn on PLL
	    while ( !( RCC->CR & RCC_CR_PLLRDY ) ); // Wait until PLL is ready

	    // Step 4: Select PLL as system clock source
	    RCC->CFGR |= RCC_CFGR_SW_PLL; // Set PLL as system clock source
	    while ( ( RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL ); // Wait until PLL is used as system clock source

	    // Step 5: Configure AHB and APB Prescalers
	    RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // Set AHB = SYSCLK / 1 = 72 MHz
	    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; // Set APB1 = 72 MHz / 4 = 18 MHz
	    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; // Set APB2 = 72 MHz / 2 = 36 MHz
}