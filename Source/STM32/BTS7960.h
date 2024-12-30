
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
#ifndef BTS7960_DRIVER_H_
#define BTS7960_DRIVER_H_

/**************************************************************************************************
 *  INCLUDES
 *************************************************************************************************/
#include "stm32f411xe.h"
 /**************************************************************************************************
 *  MACROS
 **************************************************************************************************/
#define BTS7960_MAX_PWM 65535
#define BTS7960_MIN_PWM 0
/**************************************************************************************************
 *  Config PWM
 *************************************************************************************************/
typedef struct {
    TIM_TypeDef* timer;          /**< Timer: Points to the timer (e.g., TIM1, TIM2). */
    GPIO_TypeDef* gpioPort;      /**< GPIO Port: Points to the GPIO port (e.g., GPIOA, GPIOB). */
    uint32_t gpioPin;            /**< GPIO Pin: Specifies the GPIO pin (e.g., 0, 1, 2...). */
    uint8_t timerChannel;        /**< Timer Channel: The timer channel number (e.g., 1, 2, 3, 4). */
    uint8_t Psc_t;               /**< Prescaler value for the timer  */
    uint32_t Arr_t;              /**< Auto-reload value: Determines the PWM period or frequency. */
} BTS7960_Channel_t;

typedef struct {
    BTS7960_Channel_t motor1;
    BTS7960_Channel_t motor2;
} MotorSystem;
/**************************************************************************************************
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
void BTS7960_PWMInit(BTS7960_Channel_t* motor1, BTS7960_Channel_t* motor2);

/**
 * \brief Move forward.
 */
static inline void BTS7960_MoveForward(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Move backward.
 */
static inline void BTS7960_MoveBackward(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Turn left.
 */
static inline void BTS7960_TurnLeft(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Turn right.
 */
static inline void BTS7960_TurnRight(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Stop the motor.
 */
static inline void BTS7960_Stop(uint32_t pwmLeft, uint32_t pwmRight);

/**
 * \brief Set motor mode and control movement.
 */
void BTS7960_SetMode(BTS7960_Mode mode, uint32_t pwmLeft, uint32_t pwmRight);

#endif /* BTS7960_DRIVER_H_ */
