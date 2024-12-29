/**************************************************************************************************
 *  Encoder.c
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for educational purposes only.
 *  \endverbatim
 *************************************************************************************************/

#include "Encoder.h"



/* This functions to rename Weak Interupt */
void setupVectorTable(void) {
    // Set VTOR to the address of RAM
    uint32_t* VTOR = (uint32_t*)0xE000ED08; // VTOR address
    *VTOR = 0x20000000;  // Set to RAM address (base vector)

    // Assign the address of Encoder_Turnleft to the EXTI9 vector
    uint32_t* exti9_vector = (uint32_t*)(VTOR + 0x58); // Address for EXTI9 vector
    *exti9_vector = (uint32_t)Encoder_Turnleft; // Assign the interrupt handler address for EXTI9
	

    // Assign the address of Encoder_Turnright to the EXTI15 vector
    uint32_t* exti15_vector = (uint32_t*)(VTOR + 0x5C); // Address for EXTI15 vector
    *exti15_vector = (uint32_t)Encoder_Turnright; // Assign the interrupt handler address for EXTI15
	  NVIC_SetPriority( EXTI9_5_IRQn , 1 ); // Set priority level 2
		NVIC_SetPriority( EXTI15_10_IRQn , 2 ); // Set priority level 2
    NVIC_EnableIRQ  (  EXTI15_10_IRQn ); // Enable USART1 interrupt in NVIC(
		NVIC_EnableIRQ  (  EXTI9_5_IRQn );
}



