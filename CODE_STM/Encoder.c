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

volatile long pos_left = 0;
volatile long pos_right = 0;
// direction of motor
int Direction_left = 1;
int Direction_right = 1;

const int encoder_minimum = -32768;
const int encoder_maximum = 32767;

/* This functions to rename Weak Interupt */
void setupVectorTable(void) {
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

void Encoder_Turnleft(void){
 int b1 = readEncoder1 ;
//    	int increment1 = 0;

    	if(b1 == 0){
    		Direction_left = 1;
    	}
    	else if (b1 > 0){
    		Direction_left = 0;
    	}

    	if(Direction_left == 1){
    		if (pos_left == encoder_maximum){
    			pos_left = encoder_minimum;
    		}
    		else{
    			pos_left++;
    		}
    	}
    	else {
    	    if (pos_left == encoder_minimum) {
    	    	pos_left = encoder_maximum;
    	    }
    	    else {
    	    	pos_left--;
    	    }
    	}
 }
void Encoder_Turnright(void){
 	int b2 =	readEncoder2;

    	if(b2 == 0){
    		Direction_right = 0;
    	}
    	else if (b2 > 0){
    		Direction_right = 1;
    	}

    	if(Direction_right == 1){
    		if (pos_right == encoder_maximum){
    			pos_right = encoder_minimum;
    		}
    		else{
    			pos_right++;
    		}
    	}
    	else {
    	    if (pos_right == encoder_minimum) {
    	    	pos_right = encoder_maximum;
    	    }
    	    else {
    	    	pos_right--;
    	    }
    	}

    }



