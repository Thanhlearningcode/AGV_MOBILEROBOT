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

/**************************************************************************************************
 *  GLOBAL FUNCTION DEFINITIONS
 *************************************************************************************************/
 /**************************************************************************************************
 *  MACROS
 **************************************************************************************************/
#define BTS7960_MAX_PWM 65535
#define BTS7960_MIN_PWM 0
/**
 * \brief Initialize TIM2 for multi-channel PWM generation.
 * \details This function configures TIM2 and GPIOA for generating PWM signals on multiple channels
 *          (PA0, PA1, PA2, PA3).
 */
void BTS7960_PWMInit(void) {
    /* Enable clock for TIM2 */
    RCC->APB1ENR |= ( 1U << 0 );  // Enable RCC clock for TIM2

    /* Configure GPIOA (PA0, PA1, PA2, PA3) for Alternate Function (AF) mode */
    GPIOA->MODER &= ~( 0xF << 0 );  // Clear bits for PA0 and PA1
    GPIOA->MODER |= ( 0xA << 0  );   // Set PA0 and PA1 to AF mode

    GPIOA->MODER &= ~( 0x3 << 4 );  // Clear bits for PA2
    GPIOA->MODER |=  ( 2U  << 4 );    // Set PA2 to AF mode

    GPIOA->MODER &= ~( 0x3 << 6 );  // Clear bits for PA3
    GPIOA->MODER |=  ( 2U  << 6 );    // Set PA3 to AF mode

    /* Set Alternate Function (AF01) for PA0, PA1, PA2, PA3 */
    GPIOA->AFR[0] |= ( 1U << 0 );   // AF01 mapping for PA0
    GPIOA->AFR[0] |= ( 1U << 4 ) ;   // AF01 mapping for PA1
    GPIOA->AFR[0] |= ( 1U << 8 );   // AF01 mapping for PA2
    GPIOA->AFR[0] |= ( 1U << 12 );  // AF01 mapping for PA3

    /* Configure TIM2 */
    TIM2->CNT  = 0;               // Reset counter
    TIM2->ARR  = 65535;      	  // Auto-reload value (maximum counter value)
    TIM2->PSC  = 0;        		  // Set prescaler (no division)
    TIM2->CCR1 = 0;         	  // Set initial duty cycle for PA0
    TIM2->CCR2 = 0;               // Set initial duty cycle for PA1
    TIM2->CCR3 = 0;               // Set initial duty cycle for PA2
    TIM2->CCR4 = 0;               // Set initial duty cycle for PA3

    TIM2->CR1 |= ( 1U << 7  ); 	  // Enable auto-reload preload
    TIM2->CR1 &= ~( 1U << 4 ); 	  // Set counter as upcounter

    /* Configure channels for PWM output */
    // Channel 1 (PA0)
    TIM2->CCMR1 &= ~( 3U << 0 );    // CC1 channel is output
    TIM2->CCMR1 |= ( 6U << 4 );     // PWM mode 1 for CC1

    // Channel 2 (PA1)
    TIM2->CCMR1 &= ~( 3U << 8 );    // CC2 channel is output
    TIM2->CCMR1 |=  ( 6U << 12 );    // PWM mode 1 for CC2

    // Channel 3 (PA2)
    TIM2->CCMR2 &= ~( 3U << 0 );    // CC3 channel is output
    TIM2->CCMR2 |=  ( 6U << 4 );     // PWM mode 1 for CC3

    // Channel 4 (PA3)
    TIM2->CCMR2 &= ~( 3U << 8 );    // CC4 channel is output
    TIM2->CCMR2 |= ( 6U << 12 );    // PWM mode 1 for CC4

    /* Enable output for all channels */
    TIM2->CCER |= ( 1U << 0 );      // Enable output for Channel 1
    TIM2->CCER |= ( 1U << 4 );      // Enable output for Channel 2
    TIM2->CCER |= ( 1U << 8 );      // Enable output for Channel 3
    TIM2->CCER |= ( 1U << 12 );     // Enable output for Channel 4

    /* Enable TIM2 */
    TIM2->CR1 |= ( 1U << 0 );       // Enable TIM2 counter
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
void BTS7960_MoveForward ( uint32_t pwm1, uint32_t pwm2 ) { // Mode 1
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
void BTS7960_MoveBackward ( uint32_t pwm1 , uint32_t pwm2 ) { // Mode 2
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
void BTS7960_TurnLeft ( uint32_t pwm1, uint32_t pwm2 ) { // Mode 3
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
void BTS7960_TurnRight ( uint32_t pwm1, uint32_t pwm2 ) { // Mode 4
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
void BTS7960_Stop ( uint32_t pwm1, uint32_t pwm2 ) { // Mode 0
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
