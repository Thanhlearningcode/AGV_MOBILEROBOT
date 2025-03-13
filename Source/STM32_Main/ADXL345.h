/**************************************************************************************************
 *  ADXL345.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for IMU ADXL345
 *  \endverbatim
 *************************************************************************************************/
#ifndef _ADXL345_H_
#define _ADXL345_H_

#include "I2C1.h"
#include <stdint.h>

#define   DEVID_R							(0x00)
#define   DEVICE_ADDR    			(0x53)
#define   DATA_FORMAT_R   		(0x31)
#define   POWER_CTL_R 				(0x2D)
#define   DATA_START_ADDR			(0x32)
#define   DATA_FORMAT_R   		(0x31)


#define		FOUR_G							(0x01)
#define		RESET								(0x00)
#define   SET_MEASURE_B		    (0x08)




void ADXL_Init (void);
void ADXL_ReadValues (uint8_t reg);

#endif /* _ADXL345_H_ */
