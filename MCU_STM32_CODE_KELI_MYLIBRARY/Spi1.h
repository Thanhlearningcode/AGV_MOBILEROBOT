#ifndef _Spi1_H_
#define _Spi1_H_

#include "stm32f411xe.h"

void Spi1_Init(void);

void Spi1_Transmitrer ( uint8_t *data, uint8_t size );
void Spi1_ReceiveData ( uint8_t *data, uint8_t size );


#endif // _Spi1_H_