#ifndef _HSCR04_H_
#define _HSCR04_H_

#include "stm32f411xe.h"
typedef unsigned char      uint8;   /* 8-bit unsigned integer */
typedef signed char        sint8;   /* 8-bit signed integer */
typedef unsigned short     uint16;  /* 16-bit unsigned integer */
typedef signed short       sint16;  /* 16-bit signed integer */
typedef unsigned long      uint32;  /* 32-bit unsigned integer */
typedef signed long        sint32;  /* 32-bit signed integer */
typedef unsigned long long uint64;  /* 64-bit unsigned integer */
typedef signed long long   sint64;  /* 64-bit signed integer */
typedef float              float32; /* 32-bit floating-point */
typedef double             float64; /* 64-bit floating-point */

extern float dist1;
void Delay3(__IO uint32 nCount);
float HCSR04_Read(void);
uint8_t TM_HCSR04_Init(void);
void EXIT1_Init(void);

#endif