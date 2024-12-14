/***************************************************************************
 * @file    Encoder.h
 * @brief   Khai báo các hàm va cau truc lien quan toi Encoder
 * @details This file use to read encoder from DC BTS7960 
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 ***************************************************************************/
#ifndef _Encoder_H_
#define _Encoder_H_

#include "stm32f411xe.h"
#include "Exti.h" 
#include "Dio.h"
void setupVectorTable(void);
/* This functions use to read encoder from left motor */
void Encoder_Turnleft(void);

/* This functions use to read encoder from right motor */
void Encoder_Turnright(void);

#endif // _Encoder_H_