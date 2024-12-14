/*
 * Systick.h
 *
 *  Created on: Nov 25, 2024
 *      Author: Van Thanh
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_

#include "stm32f411xe.h"

void Tick_Increment(void);
void Systick_Init(void);
void Systick_Hander(void);
uint32_t get_tick(void);


#endif /* INC_SYSTICK_H_ */
