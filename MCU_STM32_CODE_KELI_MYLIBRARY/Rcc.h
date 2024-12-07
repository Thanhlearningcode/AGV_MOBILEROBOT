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
#ifndef _Rcc_H_
#define _Rcc_H_

#include "stm32f411xe.h"

void RCC_init(void);
void IWDG_Init(void);
#endif // _Rcc_H_