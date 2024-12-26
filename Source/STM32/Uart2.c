#include "Uart2.h"

void Uart2_Init(uint16_t baudrate) {
    // RCC Configure
    RCC->AHB1ENR |= (1U << 3);  // Enable RCC for GPIOD
    RCC->APB1ENR |= (1U << 17); // Enable RCC for USART2
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN; // Enable DMA1 clock

    // Configure GPIOD PD6 RX & PD5 TX to AF mode
    GPIOD->MODER &= ~(0xF << 10); // Clear bits for PD5 and PD6
    GPIOD->MODER |= (0xA << 10);  // Set PD5 and PD6 to AF mode

    GPIOD->AFR[0] |= (0x7 << 20); // Set AF mapping for PD6 (RX)
    GPIOD->AFR[0] |= (0x7 << 24); // Set AF mapping for PD5 (TX)

    // UART Configure
    switch (baudrate) {
        case 9600:
            USART2->BRR = (468 << 4) | 12; 
            break;
        case 115200:
            USART2->BRR = (625 << 4) | 0;
            break;
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
    NVIC_EnableIRQ  (USART2_IRQn);       // Enable USART2 interrupt in NVIC
}

void Uart2_Transmiter (uint8_t *data, uint16_t size) {
    for (uint16_t i = 0; i < size; i++) {
        while (!((USART2->SR >> 7) & 0x1)); // Wait until TX is ready
        USART2->DR = data[i];                // Transmit data
        while (!((USART2->SR >> 6) & 0x1)); // Wait until TX complete
    }
}

uint16_t Uart2_Receiver() {
    while( !((USART2->SR >> 5) & 0x1) ); // Wait until data is received
    return (USART2->DR);                    // Return received data
}

void DMA_UART_Transmit ( uint8_t* data, uint16_t length ) {
    // Enable DMA1 Stream6 (for UART2 TX)
    DMA1_Stream6->CR &= ~DMA_SxCR_EN;       // Disable DMA stream
    DMA1_Stream6->CR &= ~DMA_SxCR_DIR;      // Set direction for memory-to-peripheral
    DMA1_Stream6->CR |= DMA_SxCR_MINC;      // Enable memory increment mode
    DMA1_Stream6->CR |= DMA_SxCR_PINC;      // Disable peripheral increment mode
    DMA1_Stream6->CR |= DMA_SxCR_CIRC;      // Enable circular mode (if required)
    DMA1_Stream6->CR |= DMA_SxCR_PL_1;      // Set high priority
    DMA1_Stream6->CR |= DMA_SxCR_MSIZE_1;   // Set memory size to 16 bits
    DMA1_Stream6->CR |= DMA_SxCR_PSIZE_1;   // Set peripheral size to 16 bits

    // Configure DMA stream with memory address and data size
    DMA1_Stream6->M0AR = (uint32_t)data;
    DMA1_Stream6->NDTR = length;            // Set number of data items to transfer
    DMA1_Stream6->PAR = (uint32_t)&USART2->DR; // Set peripheral address (USART2 data register)

    // Enable DMA stream for TX
    DMA1_Stream6->CR |= DMA_SxCR_EN;
}

void DMA_UART_Receive ( uint8_t* buffer, uint16_t length ) {
    // Enable DMA1 Stream5 (for UART2 RX)
    DMA1_Stream5->CR &= ~DMA_SxCR_EN;       // Disable DMA stream
    DMA1_Stream5->CR &= ~DMA_SxCR_DIR;      // Set direction for peripheral-to-memory
    DMA1_Stream5->CR |= DMA_SxCR_MINC;      // Enable memory increment mode
    DMA1_Stream5->CR |= DMA_SxCR_PINC;      // Disable peripheral increment mode
    DMA1_Stream5->CR |= DMA_SxCR_PL_1;      // Set high priority
    DMA1_Stream5->CR |= DMA_SxCR_MSIZE_1;   // Set memory size to 16 bits
    DMA1_Stream5->CR |= DMA_SxCR_PSIZE_1;   // Set peripheral size to 16 bits

    // Configure DMA stream with memory address and data size
    DMA1_Stream5->M0AR = (uint32_t)buffer;
    DMA1_Stream5->NDTR = length;            // Set number of data items to transfer
    DMA1_Stream5->PAR = (uint32_t)&USART2->DR; // Set peripheral address (USART2 data register)

    // Enable DMA stream for RX
    DMA1_Stream5->CR |= DMA_SxCR_EN;
}
