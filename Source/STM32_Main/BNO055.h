/**************************************************************************************************
 *  BNO055.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for IMU BNO055
 *  \endverbatim
 *************************************************************************************************/
#ifndef _BNO055_H_
#define _BNO055_H_

#include "I2C1.h"
#include <stdint.h>

/*Define register addresses and configuration values*/
#define   Device_ID            (0x00)    // Device ID register
#define   Device_Address       (0x53)    // I2C address of the BNO055 sensor
#define   Data_Format          (0x31)    // Data format register
#define   POWER_CTL_R          (0x2D)    // Power control register
#define   Data_Start    			 (0x32)    // Start address for accelerometer data

#define   FOUR_G               (0x01)    // Set range to ±4g
#define   RESET                (0x00)    // Reset value for power control
#define   SET_MEASURE_B        (0x08)    // Enable measurement mode



void Bno055_init (void);
void Bno055_read_values ( uint8_t reg );

#endif /*_BNO055_H_ */
