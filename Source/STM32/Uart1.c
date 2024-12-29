#include "Uart1.h"

void Uart1_Init ( uint16_t baudrate ){
    RCC->AHB2ENR |= ( 1U << 4 ); // Enable RCC for USART1
    RCC->AHB1ENR |= ( 1U << 0 ); // Enable RCC for GPIOA
    
    // Configure PA9 (TX) and PA10 (RX) in alternate function mode
    GPIOA->MODER &= ~( 0xF << 18 ); // Clear bits for PA9 and PA10
    GPIOA->MODER |=  ( 0xA << 18 );  // Set PA9, PA10 to AF mode
    GPIOA->AFR[1] |= ( 7U  << 4  );    // Set AF07 for PA9
    GPIOA->AFR[1] |= ( 7U  << 8  );    // Set AF07 for PA10
    
    // Configure USART1
    USART1->CR1 |= ( 0x3 << 2 ); // Enable RX and TX
    
    // Configure USART1 baud rate based on input parameter for 16 MHz clock
    switch (baudrate) {
        case 9600:
            USART1->BRR = ( 468 << 4 ) | 12; 

            break;
        case 115200:
            USART1->BRR = ( 39 << 4 ) | 1; 
            break;
        default:
            USART1->BRR = ( 104 << 4 ) | ( 3 << 0 ); // Default to 9600 if unsupported
            break;
    }

    // Enable USART1 interrupt
    USART1->CR1 |= ( 1U << 5 ); // Enable RXNE interrupt (Receive Not Empty)

    // Set the priority for USART1 interrupt
    NVIC_SetPriority( USART1_IRQn, 3 ); // Set priority level 3
    NVIC_EnableIRQ  ( USART1_IRQn ); // Enable USART1 interrupt in NVIC

    USART1->CR1 |=  ( 1U << 13 ); // Enable USART1
}

void Uart1_Transmiter ( uint8_t *data, uint16_t size ) {
    for (uint16_t i = 0; i < size; i++) {
     
        while ( !( ( USART2->SR >> 7) & 0x1));

        
        USART2->DR = data[i];

        
        while ( !( (USART2->SR >> 6 ) & 0x1 ) );
    }
}

uint32_t Uart1_Receiver(){
	// Wait until the data is ready to be received (RXNE bit set)
	while( !( ( USART1->SR>>5 )&0x1 ) );
	
	return (USART1->DR);

}