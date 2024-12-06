#include "Uart2.h"

void Uart2_Init(uint16_t baudrate) {
    // RCC Configure
    RCC->AHB1ENR |= (1U << 3);  // Enable RCC for GPIOD
    RCC->APB1ENR |= (1U << 17); // Enable RCC for USART2

    // Configure GPIOD PD6 RX & PD5 TX to AF mode
    GPIOD->MODER &= ~(0xF << 10); // Clear bits for PD5 and PD6
    GPIOD->MODER |= (0xA << 10);  // Set PD5 and PD6 to AF mode

    GPIOD->AFR[0] |= (0x7 << 20); // Set AF mapping for PD6 (RX)
    GPIOD->AFR[0] |= (0x7 << 24); // Set AF mapping for PD5 (TX)

    // UART Configure
    switch (baudrate) {
        case 9600:
            USART2->BRR = (468 << 4) | 12; 
            break; // Add break to prevent fall-through
        case 115200:
						USART2->BRR = (625 << 4) | 0; // Optimal settings

            break; // Add break to prevent fall-through
        default:
            USART2->BRR = (104 << 4) | (3 << 0); // Default to 9600 if unsupported
            break;
    }

    USART2->CR1 |= (0x3 << 2);   // Enable TE (transmit enable) and RE (receive enable)
    USART2->CR1 |= (1U << 5);     // Enable RXNE interrupt (Receive Not Empty)
    USART2->CR1 |= (1U << 7);     // Enable TXNE interrupt (Transmit Not Empty)
    USART2->CR1 |= (1U << 13);    // Enable USART2

    // Enable USART2 interrupt in NVIC
    NVIC_SetPriority(USART2_IRQn, 0); // Set priority level for USART2 interrupt
    NVIC_EnableIRQ(USART2_IRQn);       // Enable USART2 interrupt in NVIC
}

void Uart2_Transmiter(uint8_t *data, uint16_t size) {
    for (uint16_t i = 0; i < size; i++) {
     
        while (!((USART2->SR >> 7) & 0x1));

        
        USART2->DR = data[i];

        
        while (!((USART2->SR >> 6) & 0x1));
    }
}

uint16_t Uart2_Receiver(){
		
		while( !((USART2->SR)&0x1) );
		
		return USART2->DR;
}
