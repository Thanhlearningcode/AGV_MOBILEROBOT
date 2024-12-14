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
void Dio_Init(void){
	//	RCC->AHB1ENR|=(1U<<02); // System configuration GPIOC clock enable
			GPIOC->MODER &= ~ ( 3U << 12 ); // Input mode PC6
			GPIOC->MODER &= ~ ( 3U << 16 ); // Input mode PC8

			GPIOC->PUPDR &= ~ ( 3U << 12 ); // No pull-up and No pull-down
			GPIOC->PUPDR &= ~ ( 3U << 12 ); // No pull-up and No pull-down
}
/* This functions to rename Weak Interupt */
void setupVectorTable(void) {
	Dio_Init();
    // Set VTOR to the address of RAM
    uint32_t* VTOR = (uint32_t*)0xE000ED08; // VTOR address
    *VTOR = 0x20000000;  // Set to RAM address (base vector)

    // Assign the address of Encoder_Turnleft to the EXTI9 vector
    uint32_t* exti9_vector = (uint32_t*)(0x20000000 + 0x58); // Address for EXTI9 vector
    *exti9_vector = (uint32_t)Encoder_Turnleft; // Assign the interrupt handler address for EXTI9

    // Assign the address of Encoder_Turnright to the EXTI15 vector
    uint32_t* exti15_vector = (uint32_t*)(0x20000000 + 0x5C); // Address for EXTI15 vector
    *exti15_vector = (uint32_t)Encoder_Turnright; // Assign the interrupt handler address for EXTI15
}



int readEncoder1(void){
	int c = (( GPIOC->IDR>>8)&0x1) ;
	return c;

}
int readEncoder2(void){
int c1 =(( GPIOC->IDR>>6)&0x1);
	return c1;
}
