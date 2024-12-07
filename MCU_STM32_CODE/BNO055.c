/**************************************************************************************************
 *  BNO055.c
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for IMU BNO055
 *  \endverbatim
 *************************************************************************************************/

#include "BNO055.h"

char data;
uint8_t data_rec[6];

/**
 * \brief Read a register value from BNO055.
 * \param[in] reg Register address to read from.
 */
void Bno055_read_address(uint8_t reg)
{
    I2C1_byteRead(Device_Address , reg, &data);
}

/**
 * \brief Write a value to a register of BNO055.
 * \param[in] reg Register address to write to.
 * \param[in] value Value to be written.
 */
void Bno055_write(uint8_t reg, char value)
{
    char data[1] = { value };
    I2C1_burstWrite(Device_Address , reg, 1, data);
}

/**
 * \brief Read multiple bytes from BNO055 starting from a specific register.
 * \param[in] reg Start address of the register to read from.
 */
void Bno055_read_values(uint8_t reg)
{
    I2C1_burstRead(Device_Address , reg, 6, (char *)data_rec);
}

/**
 * \brief Initialize for IMU BNO055 sensor.
 */
void Bno055_init(void)
{
    /* Initialize I2C interface */
    I2C1_Init();

    /* Read the device ID, should return specific BNO055 ID */
    Bno055_read_address(Device_ID);

    /* Set data format range to +-4g */
    Bno055_write(Data_Format, FOUR_G);

    /* Reset all bits in the power control register */
    Bno055_write(POWER_CTL_R, RESET);

    /* Set the measure bit in power control register to start measurement */
    Bno055_write(POWER_CTL_R, SET_MEASURE_B);
}

/*
    HOW TO USE THIS DRIVER:

    int16_t x, y, z;
    double xg, yg, zg;

    extern uint8_t data_rec[6];

    int main(void)
    {
        Bno055_init();

        while(1)
        {
            Bno055_read_values(Data_Start);

            x = ((data_rec[1] << 8) | data_rec[0]);
            y = ((data_rec[3] << 8) | data_rec[2]);
            z = ((data_rec[5] << 8) | data_rec[4]);

            xg = x * 0.0078;
            yg = y * 0.0078;
            zg = z * 0.0078;
        }
    }
*/
