#include "HSCR04.h"

#define TRIG_PIN      ( 1U << 0 )   // Define for TRIG pin (GPIOD Pin 0)
#define ECHO_PIN      ( 1U << 2 )   // Define for ECHO pin (GPIOD Pin 2)
#define TIMEOUT_VALUE 1000000U    // Timeout for sensor read

float dist1;

/* Basic delay function */
void Delay3( uint32 nCount )
{
    while ( nCount-- )
    {
        /* Wait loop */
    }
}

/* Read distance from HCSR04 ultrasonic sensor */
float HCSR04_Read(void)
{
    uint32 time, timeout;

    /* Trigger the sensor by setting TRIG_PIN low -> high -> low */
    GPIOD->ODR &= ~TRIG_PIN;  // Trig low
    Delay3(2);
    GPIOD->ODR |= TRIG_PIN;   // Trig high
    Delay3(10);
    GPIOD->ODR &= ~TRIG_PIN;  // Trig low

    /* Wait for ECHO_PIN to go high */
    timeout = TIMEOUT_VALUE;
    while ( !( GPIOD->IDR & ECHO_PIN ) ) 
    {
        if ( timeout-- == 0U )
        {
            return -1.0F;  // Timeout occurred
        }
    }

    /* Measure the time while ECHO_PIN is high */
    time = 0U;
    while ( GPIOD->IDR & ECHO_PIN )
    {
        time++;
        Delay3(1);
    }

    /* Calculate distance in cm based on time and speed of sound */
    dist1 = (float)time * 0.0171821F;
    return dist1;
}

/* Initialize the HCSR04 sensor */
uint8 TM_HCSR04_Init(void)
{
    /* Enable clock for GPIOD */
    RCC->AHB1ENR |= ( 1U << 3 );

    /* Configure TRIG_PIN (GPIOD Pin 0) as output */
    GPIOD->MODER &= ~( 3U << 0 );  // Clear mode bits
    GPIOD->MODER |= ( 1U << 0) ;   // Set as output
    GPIOD->OTYPER &= ~TRIG_PIN;  // Push-pull
    GPIOD->OSPEEDR |= ( 1U << 0 ); // Medium speed
    GPIOD->ODR &= ~TRIG_PIN;     // Set TRIG_PIN low initially

    /* Configure ECHO_PIN (GPIOD Pin 2) as input with pull-down */
    GPIOD->MODER &= ~( 3U << 4 );  // Clear mode bits for Pin 2
    GPIOD->PUPDR |= (  2U << 4 );   // Pull-down

    /* Test the sensor by reading a distance */
    if ( HCSR04_Read() >= 0.0F )
    {
        return 1U;  // Sensor initialization successful
    }
    return 0U;  // Sensor initialization failed
}

/* Initialize EXTI0 interrupt for GPIOA Pin 0 */
void EXTI0_Init(void)
{
    /* Enable clock for SYSCFG and GPIOA */
    RCC->APB2ENR |= ( 1U << 14 );
    RCC->AHB1ENR |= ( 1U << 0 );

    /* Configure GPIOA Pin 0 as input */
    GPIOA->MODER &= ~( 3U << 0 );

    /* Connect EXTI0 line to GPIOA Pin 0 */
    SYSCFG->EXTICR[0] &= ~( 0xFU << 0 );

    /* Configure EXTI line for falling edge trigger */
    EXTI->FTSR |= ( 1U << 0 );  // Falling edge
    EXTI->RTSR &= ~ ( 1U << 0 ); // Disable rising edge

    /* Enable interrupt for EXTI0 */
    EXTI->IMR |= ( 1U << 0 );  // Unmask EXTI0 interrupt
    EXTI->PR |=  ( 1U << 0 );   // Clear pending flag

    /* Enable EXTI0 in NVIC */
    NVIC_EnableIRQ ( EXTI0_IRQn );
}
