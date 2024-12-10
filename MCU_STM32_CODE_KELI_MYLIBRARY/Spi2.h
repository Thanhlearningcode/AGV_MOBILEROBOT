#ifndef _Spi2_H_
#define _Spi2_H_

#include "stm32f411xe.h"


void Spi2_Init(void);
void Spi2_Trans ( uint8_t	 *data , uint8_t size );
void Spi2_Receive ( uint8_t *data, uint8_t size );
#endif //_Spi2_H_