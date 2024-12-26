#ifndef BTS7960_DRIVER_H_
#define BTS7960_DRIVER_H_

/**************************************************************************************************
 *  BTS7960_Driver.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Date: 2024-11-01
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  Description: Driver for controlling BTS7960 motor driver module.
 *  \endverbatim
 *************************************************************************************************/

/**************************************************************************************************
 *  INCLUDES
 *************************************************************************************************/
#include "stm32f411xe.h"
#include <assert.h>

/**************************************************************************************************
 *  GLOBAL ENUMS AND MACROS
 *************************************************************************************************/
typedef enum {
    BTS7960_STOP = 0U,    /**< Stop the motor. */
    BTS7960_FORWARD,      /**< Move forward. */
    BTS7960_BACKWARD,     /**< Move backward. */
    BTS7960_TURN_LEFT,    /**< Turn left. */
    BTS7960_TURN_RIGHT    /**< Turn right. */
} BTS7960_Mode;

/**************************************************************************************************
 *  FUNCTION PROTOTYPES
 *************************************************************************************************/
/**
 * \brief Initialize TIM2 for BTS7960 PWM generation.
 */
void BTS7960_PWMInit(void);

/**
 * \brief Move forward.
 */
void BTS7960_MoveForward(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Move backward.
 */
void BTS7960_MoveBackward(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Turn left.
 */
void BTS7960_TurnLeft(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Turn right.
 */
void BTS7960_TurnRight(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Stop the motor.
 */
void BTS7960_Stop(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Set motor mode and control movement.
 */
void BTS7960_SetMode(BTS7960_Mode mode, uint32_t pwmLeft, uint32_t pwmRight);

#endif /* BTS7960_DRIVER_H_ */
