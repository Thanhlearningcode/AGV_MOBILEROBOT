/**************************************************************************************************
 *  ADXL345.c
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for IMU ADXL345
 *  \endverbatim
 *************************************************************************************************/

#include "ADXL345.h"

char data;
 uint8_t data_rec[6];

void ADXL_ReadAdress (uint8_t reg)
{
	 I2C1_byteRead( DEVICE_ADDR, reg, &data);

}

void ADXL_Write (uint8_t reg, char value)
{
	char data[1];
	data[0] = value;

	I2C1_burstWrite( DEVICE_ADDR, reg,1, data) ;
}

void ADXL_ReadValues (uint8_t reg)
{
	I2C1_burstRead(DEVICE_ADDR, reg, 6,(char *)data_rec);

}


void ADXL_Init (void)
{
	/*Enable I2C*/
	I2C1_Init();

	/*Read the DEVID, this should return 0xE5*/
	ADXL_ReadAdress(DEVID_R);

	/*Set data format range to +-4g*/
	ADXL_Write (DATA_FORMAT_R, FOUR_G);

	/*Reset all bits*/
	ADXL_Write (POWER_CTL_R, RESET);

	/*Configure power control measure bit*/
	ADXL_Write (POWER_CTL_R, SET_MEASURE_B);
}

/* 

	HOW TO USE 

int16_t x,y,z;
double xg, yg, zg;

extern uint8_t data_rec[6];

int main(void)
{


	adxl_init();


	while(1)
	{
		ADXL_ReadValues (DATA_START_ADDR);

		 x = ((data_rec[1]<<8)|data_rec[0]);
		 y = ((data_rec[3]<<8)|data_rec[2]);
		 z = ((data_rec[5]<<8)|data_rec[4]);

		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);

	}

}

*/