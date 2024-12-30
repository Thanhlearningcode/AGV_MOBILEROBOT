/**************************************************************************************************
 *  DC BTS7960.c
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh 
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for controlling driver BTS7960 motor
 *  \endverbatim
 *************************************************************************************************/

#include "BTS7960.h"
#include <assert.h>
#include "stddef.h"
#ifndef assert_param
    #define assert_param(expression)  assert(expression)  
#endif
/**************************************************************************************************
 *  GLOBAL FUNCTION DEFINITIONS
 *************************************************************************************************/
/**
 * \brief Initialize TIM2 for multi-channel PWM generation.
 * \details This function configures TIM2 and GPIOA for generating PWM signals on multiple channels
 *          (PA0, PA1, PA2, PA3).
 */
 static void check_assert_param(BTS7960_Channel_t* a, BTS7960_Channel_t* b){
 
 	/* Check the Parameters */
 assert_param(a != NULL);  // Ensure motor1 pointer is valid
 assert_param(b != NULL);  // Ensure motor2 pointer is valid
    
 }
void BTS7960_PWMInit(BTS7960_Channel_t* motor1, BTS7960_Channel_t* motor2) {
check_assert_param(&motor1,&motor2);
      /* Case when motor1 and motor2 use the same timers*/
    if (motor1->timer == motor2->timer) {
        // Enable the clock for the timer used by both motors
        if (motor1->timer == TIM1) {
            RCC->APB2ENR |= (1U << 0);  // Enable clock for TIM1
        } else if (motor1->timer == TIM2) {
            RCC->APB1ENR |= (1U << 0);  // Enable clock for TIM2
        }

        // Enable the GPIO clock for the motor pins
        if (motor1->gpioPort == GPIOA || motor2->gpioPort == GPIOA) {
            RCC->AHB1ENR |= (1U << 0);  // Enable GPIOA clock
        } else if (motor1->gpioPort == GPIOB || motor2->gpioPort == GPIOB) {
            RCC->AHB1ENR |= (1U << 1);  // Enable GPIOB clock
        }

        // Configure GPIO for motor1
        motor1->gpioPort->MODER &= ~(0x3 << (2 * motor1->gpioPin));  // Clear bits for motor1 pin
        motor1->gpioPort->MODER |= (0x2 << (2 * motor1->gpioPin));    // Set to AF mode for motor1 pin
        motor1->gpioPort->AFR[motor1->gpioPin / 8] |= (1U << ((motor1->gpioPin % 8) * 4));

        // Configure GPIO for motor2
        motor2->gpioPort->MODER &= ~(0x3 << (2 * motor2->gpioPin));  // Clear bits for motor2 pin
        motor2->gpioPort->MODER |= (0x2 << (2 * motor2->gpioPin));    // Set to AF mode for motor2 pin
        motor2->gpioPort->AFR[motor2->gpioPin / 8] |= (1U << ((motor2->gpioPin % 8) * 4));

        // Configure the timer for both motors (same timer)
        motor1->timer->CNT = 0;            // Reset counter
        motor1->timer->ARR = motor1->Arr_t;  // Auto-reload value (max counter)
        motor1->timer->PSC = motor1->Psc_t;  // No prescaler
        motor1->timer->CCR1 = 0;           // Set initial duty cycle for motor1
        motor1->timer->CCR2 = 0;           // Set initial duty cycle for motor2
        motor1->timer->CR1 |= (1U << 7);   // Enable auto-reload preload
        motor1->timer->CR1 &= ~(1U << 4);  // Set counter as upcounter

        // Configure PWM mode for motor1
        if (motor1->timerChannel == 1) {
            motor1->timer->CCMR1 &= ~(3U << 0);  // CC1 channel is output
            motor1->timer->CCMR1 |= (6U << 4);   // PWM mode 1 for CC1
					  motor1->timer->CCER |= (1U << 0);    // Enable output for Channel 1 of motor1
        }

        // Configure PWM mode for motor2
        if (motor2->timerChannel == 2) {
            motor2->timer->CCMR1 &= ~(3U << 8);  // CC2 channel is output
            motor2->timer->CCMR1 |= (6U << 12);  // PWM mode 1 for CC2
						motor2->timer->CCER |= (1U << 4);    // Enable output for Channel 2 of motor2
        }
        // Enable the timer for both motors
        motor1->timer->CR1 |= (1U << 0);  // Enable Timer counter for both motors
    } 
/* Case when motor1 and motor2 use different timers*/
    else {
        // Enable clock for motor1's timer
        if (motor1->timer == TIM1) {
            RCC->APB2ENR |= (1U << 0);  // Enable clock for TIM1
        } else if (motor1->timer == TIM2) {
            RCC->APB1ENR |= (1U << 0);  // Enable clock for TIM2
        }

        // Enable clock for motor2's timer
        if (motor2->timer == TIM1) {
            RCC->APB2ENR |= (1U << 0);  // Enable clock for TIM1
        } else if (motor2->timer == TIM2) {
            RCC->APB1ENR |= (1U << 0);  // Enable clock for TIM2
        }

        // Enable the GPIO clock for the motor pins
        if (motor1->gpioPort == GPIOA || motor2->gpioPort == GPIOA) {
            RCC->AHB1ENR |= (1U << 0);  // Enable GPIOA clock
        } else if (motor1->gpioPort == GPIOB || motor2->gpioPort == GPIOB) {
            RCC->AHB1ENR |= (1U << 1);  // Enable GPIOB clock
        }

        // Configure GPIO for motor1
        motor1->gpioPort->MODER &= ~(0x3 << (2 * motor1->gpioPin));  // Clear bits for motor1 pin
        motor1->gpioPort->MODER |= (0x2 << (2 * motor1->gpioPin));    // Set to AF mode for motor1 pin
        motor1->gpioPort->AFR[motor1->gpioPin / 8] |= (1U << ((motor1->gpioPin % 8) * 4));

        // Configure GPIO for motor2
        motor2->gpioPort->MODER &= ~(0x3 << (2 * motor2->gpioPin));  // Clear bits for motor2 pin
        motor2->gpioPort->MODER |= (0x2 << (2 * motor2->gpioPin));    // Set to AF mode for motor2 pin
        motor2->gpioPort->AFR[motor2->gpioPin / 8] |= (1U << ((motor2->gpioPin % 8) * 4));

        // Configure Timer for motor1
        motor1->timer->CNT = 0;            // Reset counter for motor1
        motor1->timer->ARR = motor1->Arr_t;  // Auto-reload value (max counter)
        motor1->timer->PSC = motor1->Psc_t;  // No prescaler
        motor1->timer->CCR1 = 0;           // Set initial duty cycle for motor1
        motor1->timer->CCR2 = 0;           // Set initial duty cycle for motor2
        motor1->timer->CR1 |= (1U << 7);   // Enable auto-reload preload
        motor1->timer->CR1 &= ~(1U << 4);  // Set counter as upcounter

        // Configure PWM mode for motor1
        if (motor1->timerChannel == 1) {
            motor1->timer->CCMR1 &= ~(3U << 0);  // CC1 channel is output
            motor1->timer->CCMR1 |= (6U << 4);   // PWM mode 1 for CC1
						motor1->timer->CCER |= (1U << 0);    // Enable output for Channel 1 of motor1
        }

        // Configure Timer for motor2
        motor2->timer->CNT = 0;            // Reset counter for motor2
        motor2->timer->ARR = motor1->Arr_t;  // Auto-reload value (max counter)
        motor2->timer->PSC = motor1->Psc_t;  // No prescaler
        motor2->timer->CCR1 = 0;           // Set initial duty cycle for motor1
        motor2->timer->CCR2 = 0;           // Set initial duty cycle for motor2
        motor2->timer->CR1 |= (1U << 7);   // Enable auto-reload preload
        motor2->timer->CR1 &= ~(1U << 4);  // Set counter as upcounter

        // Configure PWM mode for motor2
        if (motor2->timerChannel == 2) {
            motor2->timer->CCMR1 &= ~(3U << 8);  // CC2 channel is output
            motor2->timer->CCMR1 |=  (6U << 12);  // PWM mode 1 for CC2
            motor2->timer->CCER |= (1U << 4);    // Enable output for Channel 2 of motor2
        }

        // Enable Timer for motor1 and motor2
        motor1->timer->CR1 |= (1U << 0);  // Enable Timer counter for motor1
        motor2->timer->CR1 |= (1U << 0);  // Enable Timer counter for motor2
    }
}
/**************************************************************************************************
 *  STATIC INLINE FUNCTIONS
 **************************************************************************************************/
static inline uint32_t BTS7960_ClampPWM(uint32_t pwm) {
				assert( (pwm <= 66535) && (pwm >= 0));
	return (pwm > BTS7960_MAX_PWM) ? BTS7960_MAX_PWM :
			(  (pwm < BTS7960_MIN_PWM) ? BTS7960_MIN_PWM : pwm );
}
/**
 * \brief Move the robot forward.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 */
static inline void BTS7960_MoveForward ( uint32_t pwm1, uint32_t pwm2 ) { // Mode 1
		pwm1 = BTS7960_ClampPWM(pwm1);
    pwm2 = BTS7960_ClampPWM(pwm2);
    TIM2->CCR1 = pwm1;  // Set PWM for left motor
    TIM2->CCR2 = 0;     // Disable left motor reverse
    TIM2->CCR3 = pwm2;  // Set PWM for right motor
    TIM2->CCR4 = 0;     // Disable right motor reverse
}

/**
 * \brief Move the robot backward.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 */
static inline void BTS7960_MoveBackward ( uint32_t pwm1 , uint32_t pwm2 ) { // Mode 2
		pwm1 = BTS7960_ClampPWM(pwm1);
    pwm2 = BTS7960_ClampPWM(pwm2);
    TIM2->CCR1 = 0;     // Disable left motor forward
    TIM2->CCR2 = pwm1;  // Set PWM for left motor reverse
    TIM2->CCR3 = 0;     // Disable right motor forward
    TIM2->CCR4 = pwm2;  // Set PWM for right motor reverse
}

/**
 * \brief Turn the robot to the left.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 */
static inline void BTS7960_TurnLeft ( uint32_t pwm1, uint32_t pwm2 ) { // Mode 3
		pwm1 = BTS7960_ClampPWM (pwm1);
    pwm2 = BTS7960_ClampPWM (pwm2);	
    TIM2->CCR1 = pwm1;  // Set PWM for left motor forward
    TIM2->CCR2 = 0;     // Disable left motor reverse
    TIM2->CCR3 = 0;     // Disable right motor forward
    TIM2->CCR4 = pwm2;  // Set PWM for right motor reverse
}

/**
 * \brief Turn the robot to the right.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 */
static inline void BTS7960_TurnRight ( uint32_t pwm1, uint32_t pwm2 ) { // Mode 4
		pwm1 = BTS7960_ClampPWM (pwm1);
    pwm2 = BTS7960_ClampPWM (pwm2);
    TIM2->CCR1 = 0;     // Disable left motor forward
    TIM2->CCR2 = pwm1;  // Set PWM for left motor reverse
    TIM2->CCR3 = pwm2;  // Set PWM for right motor forward
    TIM2->CCR4 = 0;     // Disable right motor reverse
}

/**
 * \brief Stop the robot's movement.
 * \details This function stops the robot by setting motor PWM values to zero.
 */
static inline void BTS7960_Stop ( uint32_t pwm1, uint32_t pwm2 ) { // Mode 0
    TIM2->CCR1 = 0;  // Stop left motor
    TIM2->CCR2 = 0;  // Stop left motor reverse
    TIM2->CCR3 = 0;  // Stop right motor
    TIM2->CCR4 = 0;  // Stop right motor reverse
}



/**************************************************************************************************
 *  GLOBAL VARIABLE DEFINITIONS
 *************************************************************************************************/

/* Array of function pointers to control different movement modes of the robot. */
void (*BTS7960_ControlFunctions[])(uint32_t, uint32_t) = {
    BTS7960_Stop,
    BTS7960_MoveForward,
    BTS7960_MoveBackward,
    BTS7960_TurnRight,
    BTS7960_TurnLeft,
};
/**
 * \brief Control robot mode.
 * \param[in] controlCar Function pointer to the movement mode function.
 * \param[in] pwm1 PWM value for the left motor.
 * \param[in] pwm2 PWM value for the right motor.
 */
void BTS7960_SetMode(BTS7960_Mode mode, uint32_t pwm1, uint32_t pwm2) {
    if (mode >= 0 && mode < sizeof(BTS7960_ControlFunctions) / sizeof(BTS7960_ControlFunctions[0])) {
        BTS7960_ControlFunctions[mode](pwm1, pwm2);
  } else {
        BTS7960_Stop (BTS7960_MIN_PWM, BTS7960_MIN_PWM);
    }
}
