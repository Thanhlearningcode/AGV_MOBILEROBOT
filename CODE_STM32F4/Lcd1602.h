/*
 * lcd1602.h
 *
 *  Created on: 10/14/2024
 *      Author: Nguyen Van Thanh
 */

#ifndef _LCD1602_H_
#define _LCD1602_H_


void Lcd_Init(void);   // initialize lcd

void Lcd_Send_Cmd(char cmd);  // send command to the lcd

void Lcd_Send_Data(char data);  // send data to the lcd

void Lcd_Send_String(char *str);  // send string to the lcd

void Lcd_Put_Cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);

void Lcd_Clear (void);

#endif /* LCD1602_H_ */
