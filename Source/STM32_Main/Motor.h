#ifndef MOTOR_H_
#define MOTOR_H_

/**************************************************************************************************
 *  DC BTS7960.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Date: 2024-11-01
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for controlling driver BTS7960 motor
 *  \endverbatim
 *************************************************************************************************/

/**************************************************************************************************
 *  INCLUDES
 *************************************************************************************************/
#include "stm32f411xe.h"
#include <assert.h>
/**************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *************************************************************************************************/
/**
 * \brief Enumeration for controlling the car's movement.
 * \param[in] Stop value for stoping the car.
 * \param[in] Forward value for turn foward the car.
 * \param[in] Backward value for turn backward the car.
 * \param[in] right value for turn right the car.
  * \param[in] left value for turn left the car.
 * \details This function makes the robot move backward based on the PWM values.
 */
typedef enum {
    Stop = 0U ,   /**< Stop the car. */
    Forward,     /**< Move the car forward. */
    Backward,    /**< Move the car backward. */
    Left,        /**< Turn the car to the left. */
    Right        /**< Turn the car to the right. */
} CarControlMode;

/**
 * \brief Initialize TIM2 for multi-channel PWM generation.
 * \details This function configures TIM2 and GPIOA for generating PWM signals on multiple channels
 *          (PA0, PA1, PA2, PA3).
 */
void Motor_Init(void);
/**
 * \brief Move the robot forward.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 * \details This function makes the robot move forward based on the PWM values.
 */
void Robot_MoveForward (uint32_t pwm1, uint32_t pwm2);

/**
 * \brief Move the robot backward.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 * \details This function makes the robot move backward based on the PWM values.
 */
void Robot_MoveBackward (uint32_t pwm1, uint32_t pwm2);

/**
 * \brief Turn the robot to the left.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 * \details This function makes the robot turn left by adjusting motor PWM values.
 */
void Robot_TurnLeft (uint32_t pwm1, uint32_t pwm2);

/**
 * \brief Turn the robot to the right.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 * \details This function makes the robot turn right by adjusting motor PWM values.
 */
void Robot_TurnRight (uint32_t pwm1, uint32_t pwm2);

/**
 * \brief Stop the robot's movement.
 * \details This function stops the robot by setting motor PWM values to zero.
 */
void Robot_Stop (uint32_t pwm1, uint32_t pwm2);

/**
 * \brief Control robot mode.
 * \param[in] controlCar Pointer to the function controlling the robot's movement mode.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 * \details This function allows the selection of the robot's mode of operation by calling the specified control function.
 */
void Robot_SetMotor (void (*controlCar)(uint32_t, uint32_t), uint32_t pwm1, uint32_t pwm2);

#endif /* MOTOR_H_ */
