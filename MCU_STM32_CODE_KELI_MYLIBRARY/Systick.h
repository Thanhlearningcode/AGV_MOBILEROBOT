#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "stm32f411xe.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

void Tick_Increment(void);          // Ð?m b?o r?ng hàm này du?c khai báo
void Systick_Init(void);            // Khai báo Systick_Init dúng
void Systick_Handler(void);         // Ð?m b?o khai báo cho hàm handler
uint32_t get_tick(void);            // Khai báo hàm get_tick

#ifdef __cplusplus
}
#endif

#endif /* INC_SYSTICK_H_ */
