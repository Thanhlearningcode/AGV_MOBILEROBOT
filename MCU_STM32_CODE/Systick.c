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
		        "LDR R0, =0xE000E014 \n\t"  // Ð?a ch? c?a STK_LOAD
		        "LDR R1, =71999999   \n\t"  // N?p giá tr? 71999999 vào R1 (tuong ?ng v?i 72 MHz * 1s - 1)
		        "STR R1, [R0]        \n\t"  // Ghi giá tr? vào STK_LOAD

		        "LDR R0, =0xE000E018 \n\t"  // Ð?a ch? c?a STK_VAL
		        "LDR R1, =0          \n\t"  // Ð?t giá tr? c?a STK_VAL v? 0
		        "STR R1, [R0]        \n\t"  // Ghi giá tr? vào STK_VAL

		        "LDR R0, =0xE000E010 \n\t"  // Ð?a ch? c?a STK_CTRL
		        "LDR R1, =7          \n\t"  // C?u hình SysTick: B?t SysTick (ENABLE = 1), T?o ng?t (TICKINT = 1), S? d?ng ngu?n xung h? th?ng (CLKSOURCE = 1)
		        "STR R1, [R0]        \n\t"  // Ghi giá tr? vào STK_CTRL
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
void delay(uint32_t delay){
	uint32_t tick_start = get_tick();
	uint32_t wait = delay*1000;
	if(wait <MAX_DELAY){
		wait += (uint32_t)(tick_freq);
	}

	while((get_tick()- tick_start) < wait){}
}

