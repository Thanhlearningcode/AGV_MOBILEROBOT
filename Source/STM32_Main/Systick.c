/*
 * systick.c
 *
 *  Created on: Nov 25, 2024
 *      Author: Van Thanh
 */

#include "Systick.h"
volatile uint32_t ticks = 0;
#define MAX_DELAY 0xFFFFFFFF
__IO uint32_t g_curr_tick;
__IO uint32_t g_curr_tick_p;
__IO uint32_t tick_freq =1;

void Tick_Increment(void){
	g_curr_tick += tick_freq;
}

void Systick_Init(void){
    __asm__ volatile(
        "LDR R0, =0xE000E014 \n\t"  // Address of STK_LOAD
        "LDR R1, =71999999   \n\t"  // Load the value 71999999 into R1 (corresponding to 72 MHz * 1s - 1)
        "STR R1, [R0]        \n\t"  // Write the value to STK_LOAD

        "LDR R0, =0xE000E018 \n\t"  // Address of STK_VAL
        "LDR R1, =0          \n\t"  // Set the value of STK_VAL to 0
        "STR R1, [R0]        \n\t"  // Write the value to STK_VAL

        "LDR R0, =0xE000E010 \n\t"  // Address of STK_CTRL
        "LDR R1, =7          \n\t"  // Configure SysTick: Enable SysTick (ENABLE = 1), Enable interrupt (TICKINT = 1), Use system clock source (CLKSOURCE = 1)
        "STR R1, [R0]        \n\t"  // Write the value to STK_CTRL
    );
}

void SysTick_Handler(){
	Tick_Increment();
}

uint32_t get_tick(void){
	__disable_irq();
	g_curr_tick_p = g_curr_tick;
	__enable_irq();
	return g_curr_tick_p;
}
void delay( uint32_t delay ){
	uint32_t tick_start = get_tick();
	uint32_t wait = delay*1000;
	if( wait < MAX_DELAY ){
		wait += (uint32_t)( tick_freq );
	}

	while( ( get_tick() - tick_start ) < wait ){}
}

