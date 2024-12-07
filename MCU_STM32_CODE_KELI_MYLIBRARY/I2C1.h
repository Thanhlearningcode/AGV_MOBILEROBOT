/**************************************************************************************************
 *  I2C.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for controlling driver BTS7960 motor
 *  \endverbatim
 *************************************************************************************************/

#ifndef _I2C1_H_
#define _I2C1_H_

#include "stm32f411xe.h"

void I2C1_Init(void);
void I2C1_byteRead(char saddr, char maddr , char *data);
void I2C1_burstRead( char saddr, char maddr, int n, char *data);
void I2C1_burstWrite(char saddr, char maddr , int n, char *data);

#endif /* _I2C1_H_ */