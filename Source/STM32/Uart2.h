/**************************************************************************************************
 *  Uart2.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Date: 2024-12-30
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  Description: Driver header for controlling UART2 communication in STM32F411.
 *               Provides functions for initialization, data transmission, and reception.
 *  \endverbatim
 *************************************************************************************************/

#ifndef _Uart2_H_  /* Prevent multiple inclusions of the header file */
#define _Uart2_H_

#include "stm32f411xe.h"  /* Include STM32F411 header for hardware register access */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes UART2 with the specified baud rate.
 * 
 * This function configures the UART2 peripheral with the given baud rate
 * and initializes any necessary settings like word length, stop bits, 
 * and parity based on the system requirements.
 *
 * @param[in] baudrate Baud rate to configure the UART2 communication (e.g., 9600, 115200).
 * 
 * @return None
 * 
 * @pre UART2 peripheral should be powered and ready for configuration.
 * @post UART2 will be initialized and ready for data transmission and reception.
 */
void Uart2_Init(uint16_t baudrate);

/**
 * @brief Transmits data through UART2.
 * 
 * This function sends the specified data over UART2. The data is provided 
 * as a pointer to a byte array, and the number of bytes to be transmitted 
 * is specified by the size parameter.
 *
 * @param[in] data Pointer to the byte array that contains the data to be transmitted.
 * @param[in] size The number of bytes to transmit.
 * 
 * @return None
 * 
 * @pre UART2 should be initialized.
 * @post Data is transmitted through UART2.
 */
void Uart2_Transmiter(uint8_t *data, uint16_t size);

/**
 * @brief Receives a byte of data from UART2.
 * 
 * This function retrieves one byte of data received from UART2. It will return
 * the data received by UART2.
 *
 * @return Received byte from UART2.
 * 
 * @pre UART2 should be initialized and data should be available.
 * @post None.
 */
uint16_t Uart2_Receiver(void);

/**
 * @brief Transmits data via DMA through UART2.
 * 
 * This function sends a block of data using DMA (Direct Memory Access) to transmit
 * data over UART2. This method is efficient for sending large blocks of data.
 *
 * @param[in] data Pointer to the byte array that contains the data to be transmitted.
 * @param[in] length The length of the data to be transmitted.
 * 
 * @return None
 * 
 * @pre DMA should be initialized and configured for UART2 transmission.
 * @post Data is transmitted via DMA over UART2.
 */
void DMA_UART_Transmit(uint8_t* data, uint16_t length);

/**
 * @brief Receives data via DMA from UART2.
 * 
 * This function receives a block of data using DMA and stores it in the provided 
 * buffer. This method is efficient for receiving large amounts of data.
 *
 * @param[in] buffer Pointer to the buffer where received data will be stored.
 * @param[in] length The length of the data to be received.
 * 
 * @return None
 * 
 * @pre DMA should be initialized and configured for UART2 reception.
 * @post Data is received via DMA and stored in the buffer.
 */
void DMA_UART_Receive(uint8_t* buffer, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* _Uart2_H_ */
