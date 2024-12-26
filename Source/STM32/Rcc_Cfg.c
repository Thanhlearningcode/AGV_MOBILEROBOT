/**************************************************************************************************
 *  Rcc.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for changing clock to 72mhz
 *  \endverbatim
 *************************************************************************************************/
#include "Rcc_Cfg.h"

void Rcc_Clock_Init	(void) {

    // Step 1: Enable HSE (High Speed External)
    RCC->CR |= RCC_CR_HSEON; // Turn on HSE
  while (!(RCC->CR & RCC_CR_HSERDY)); // Wait until HSE is ready

    // Step 2: Configure PLL
    RCC->PLLCFGR = 0; // Reset PLL Configuration Register
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; // Select HSE as PLL source
    RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLM_Pos); // Set PLLM to 8 (HSE / 8)
    RCC->PLLCFGR |= (144 << RCC_PLLCFGR_PLLN_Pos); // Set PLLN to 144 (HSE / 8 * 144 / 1 = 72 MHz)
    RCC->PLLCFGR |= (RCC_PLLCFGR_PLLP_0); // Set PLLP to 2 (PLLCLK = PLLN / PLLP = 72 MHz)

    // Step 3: Enable PLL
    RCC->CR |= RCC_CR_PLLON; // Turn on PLL
  while (!(RCC->CR & RCC_CR_PLLRDY)); // Wait until PLL is ready

    // Step 4: Select PLL as system clock source
    RCC->CFGR |= RCC_CFGR_SW_PLL; // Set PLL as system clock source
   while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait until PLL is used as system clock source

    // Step 5: Configure AHB and APB Prescalers
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // Set AHB = SYSCLK / 1 = 72 MHz
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; // Set APB1 = 72 MHz / 4 = 18 MHz
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; // Set APB2 = 72 MHz / 2 = 36 MHz
}
/******************************************Watchdog Functions*****************************************************/
void IWDG_Init(void) {
    /* Enable write access to IWDG_PR and IWDG_RLR registers  */
    IWDG->KR = 0x5555;

    
    IWDG->PR = 0x03; // Set prescaler (divide by 64)
 
    
    IWDG->RLR = 625; // Set reload value for 2s

    
    IWDG->KR = 0xAAAA; // Reload the counter

    
    IWDG->KR = 0xCCCC; // Start the watchdog
}

void IWDG_Refresh(void) {
    // Refresh the watchdog counter
    IWDG->KR = 0xAAAA;
}
