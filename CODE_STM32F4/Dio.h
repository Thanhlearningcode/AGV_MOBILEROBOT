#ifndef _Dio_H_
#define _Dio_H_

#include "stm32f411xe.h"
void Dio_Init(void);
int readEncoder1(void);
int readEncoder2(void);
#endif // _Dio_H_