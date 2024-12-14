#ifndef _Uart2_H_
#define _Uart2_H_

#include "stm32f411xe.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function prototypes
void Uart2_Init ( uint16_t baudrate );
void Uart2_Transmiter ( uint8_t *data, uint16_t size );
uint16_t Uart2_Receiver();
void DMA_UART_Transmit ( uint8_t* data, uint16_t length );
void DMA_UART_Receive ( uint8_t* buffer, uint16_t length );

#ifdef __cplusplus
}
#endif

#endif // _Uart2_H_
