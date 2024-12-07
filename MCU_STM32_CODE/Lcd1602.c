/*
 * lcd1602.c
 *
 *  Created on: 10/14/2024
 *      Author: Nguyen Van Thanh
 */


#include "Lcd1602.h"

#include "stm32f411xe.h"


/****************** define the timer handler below  **************/
static void delay(uint32_t nCount);

static void delay(uint32_t nCount){
	__IO uint32_t index = 0;


	for(index = (500 * nCount); index != 0; index--);

}

/****************************************************************************************************************************************************************/

void send_to_lcd (char data, int rs)
{
// rs = 1 for data, rs=0 for command
if ( rs ==1) GPIOB->ODR |=( 1 << 0 );	
else				 GPIOB->ODR&=~( 1 << 0 );
	/* write the data to the respective pin */
GPIOB->ODR |=( ((data>>3)&0x01) << 7 );
GPIOB->ODR |=( ((data>>3)&0x01) << 6 );
GPIOB->ODR |=( ((data>>3)&0x01) << 5 );
GPIOB->ODR |=( ((data>>3)&0x01) << 4 );	


	/* Toggle EN PIN to send the data
	 * if the HCLK > 100 MHz, use the  20 us delay
	 * if the LCD still doesn't work, increase the delay to 50, 80 or 100..
	 */
	GPIOB -> ODR   |=  ( 1<< 2 );
	delay (20);
		GPIOB -> ODR &=~ ( 1<< 2 );
	delay (20);
}

void Lcd_Send_Cmd(char cmd)
{
    char datatosend;

    /* send upper nibble first */
  datatosend = ((cmd>>4)&0x0f);
  send_to_lcd(datatosend,0);  // RS must be 0 while sending command

    /* send Lower Nibble */
    datatosend = ((cmd)&0x0f);
	send_to_lcd(datatosend, 0);
}

void Lcd_Send_Data(char data)
{
	char datatosend;

	/* send higher nibble */
	datatosend = ((data>>4)&0x0f);
	send_to_lcd(datatosend, 1);  // rs =1 for sending data

	/* send Lower nibble */
	datatosend = ((data)&0x0f);
	send_to_lcd(datatosend, 1);
}

void Lcd_Clear (void)
{
	Lcd_Send_Cmd(0x01);
	delay(2);
}

void Lcd_Put_Cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    Lcd_Send_Cmd(col);
}


void Lcd_Init(void)
{
	// 4 bit initialisation
	delay(50);  // wait for >40ms
	Lcd_Send_Cmd(0x30);
	delay(5);  // wait for >4.1ms
	Lcd_Send_Cmd(0x30);
	delay(1);  // wait for >100us
	Lcd_Send_Cmd(0x30);
	delay(10);
	Lcd_Send_Cmd(0x20);  // 4bit mode
	delay(10);

  // dislay initialisation
	Lcd_Send_Cmd(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	delay(1);;
	Lcd_Send_Cmd(0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	delay(1);
	Lcd_Send_Cmd(0x01);  // clear display
	delay(2);
	Lcd_Send_Cmd(0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	delay(1);
	Lcd_Send_Cmd(0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void Lcd_Send_String(char *str)
{
	while (*str) Lcd_Send_Data(*str++);
}
