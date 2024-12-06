#ifndef _Uart2_H_
#define _Uart2_H_

#include "stm32f411xe.h"
void Uart2_Init(uint16_t baudrate);
void Uart2_Transmiter(uint8_t *data, uint16_t size);
uint16_t Uart2_Receiver();

#endif // _Uart2_H_