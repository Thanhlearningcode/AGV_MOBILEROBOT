#ifndef ROS_STM32_HARDWARE_H_
#define ROS_STM32_HARDWARE_H_

#include "stm32f411xe.h"  // STM32F411 register definitions
#include "Uart2.h"
#include "ros.h"
extern "C" {
    uint32_t get_tick(void);  // Declare get_tick with C linkage
}
class STM32Hardware{
  public:
    static const uint16_t rbuflen = 512; // Buffer length for reception
    uint8_t rbuf[rbuflen];
    uint32_t rind;
  
    // Get the current index for the DMA receive buffer
    inline uint32_t getRdmaInd(void) {
        // Directly accessing DMA register to get the remaining counter
        return ( rbuflen - DMA1_Stream5->NDTR ) & ( rbuflen - 1 );  // DMA1 Stream5 is used for USART2 RX
    }

    static const uint16_t tbuflen = 512; // Buffer length for transmission
    uint8_t tbuf[tbuflen];
    uint32_t twind, tfind;

    STM32Hardware() : rind(0), twind(0), tfind(0) {
        // Initialize UART2 settings and DMA
    }

    void init() {
        reset_rbuf();
    }

    // Reset the receive buffer and start DMA reception
    void reset_rbuf(void) {
        DMA_UART_Receive(rbuf, rbuflen);
    }

    // Read a byte from the receive buffer
    int read() {
        int c = -1;
        if ( rind != getRdmaInd() ) {
            c = rbuf[rind++];
            rind &= rbuflen - 1;  // Wrap around buffer index
        }
        return c;
    }

    // Flush the transmit buffer (start transmission via DMA)
    void flush(void) {
        static bool mutex = false;

        if ( !mutex ) {
            mutex = true;

            if ( twind != tfind ) {
                uint16_t len = tfind < twind ? twind - tfind : tbuflen - tfind;
                DMA_UART_Transmit( &( tbuf[tfind]), len );
                tfind = ( tfind + len ) & ( tbuflen - 1 );
            }

            mutex = false;
        }
    }

    // Write data to the transmit buffer and start transmission
    void write(uint8_t* data, int length) {
        int n = length;
        n = n <= tbuflen ? n : tbuflen;

        int n_tail = n <= tbuflen - twind ? n : tbuflen - twind;
        memcpy( & ( tbuf[twind] ), data, n_tail );
        twind = ( twind + n ) & ( tbuflen - 1 );

        if ( n != n_tail ) {
            memcpy( tbuf, &( data[n_tail] ), n - n_tail );
        }

        flush();
    }

    // Return the system tick count
    unsigned long time() {
        return (unsigned long)get_tick();
    }
};



#endif
