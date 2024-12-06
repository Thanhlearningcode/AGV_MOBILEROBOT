/***************************************************************************
 * @file    Encoder.h
 * @brief   Khai báo các hàm và cấu trúc liên quan tới Encoder
 * @details This file is used to read encoder data from DC BTS7960 motors
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 ***************************************************************************/
#ifndef _Encoder_H_
#define _Encoder_H_

#include "stm32f411xe.h"

/* This function is used to read encoder from left motor */
void Encoder_Turnleft(void);

/* This function is used to read encoder from right motor */
void Encoder_Turnright(void);

/* Initialize GPIO for encoder reading */
void Dio_Init(void);

/* Read encoder data from left motor */
int readEncoder1(void);

/* Read encoder data from right motor */
int readEncoder2(void);

/*Rename Interupt of Encoder */
void setupVectorTable(void) ;

#endif /* _Encoder_H_ */
