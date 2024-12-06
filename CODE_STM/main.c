/***************************************************************************
 * @file    main.c
 * @brief   Main program for the AGV (Autonomous Guided Vehicle) project
 * @details This file serves as the core of the AGV system, providing the primary 
 *          interface and functionalities required for autonomous navigation and control.
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 *****************************************************************************************************/
/********************************************* Libraries *********************************************/

#include "stm32f411xe.h"        
#include <stdio.h>               
#include <string.h>              
#include <stdlib.h>              
#include "Uart1.h"              
#include "Uart2.h"              
#include "Encoder.h"             
#include "HSCR04.h"              
#include "Rcc.h"                 
#include "Motor.h"              
#include "kernel.h"              
#include "BNO055.h"
/****************************************** Data *****************************************************/


uint8_t RxData[50];            // Buffer to receive data
uint8_t txData[50];            // Buffer to transmit data
int isSent = 1;                // Flag to indicate if data has been sent


volatile int i0, i1, i2;      // Used for multi-tasking
#define QUANTA 10              // Time quanta for kernel


char rx_buffer[50];            // Buffer for received data
char process_buffer[50];       // Buffer to process data


int data1;                     // Data variable 1
int data2;                     // Data variable 2
int data3;                     // Data variable 3


volatile int bit_rs;           // Bit register for system
float linear_x;                // Linear velocity (x-axis)
float angular_z;               // Angular velocity (z-axis)
extern volatile long pos_left; // Left wheel position (external reference)
extern volatile long pos_right;// Right wheel position (external reference)

/****************************************** Functions *****************************************************/


void USART1_IRQHandler(void);  // UART interrupt handler
void IWDG_Init(void);          // Initialize the Independent Watchdog (IWDG)
void IWDG_Refresh(void);       // Refresh the Independent Watchdog (IWDG)

uint32_t a = 1;                // A simple variable (example usage)

/****************************************** Programming *****************************************************/
int main(int argc, char *argv[]) {
    Rcc_Init();        // 72 MHz
    Exti_Init();       // External interrupt for encoder
    Tim2_Init();       // PWM
    Uart1_Init(115200); // UART to ESP32 with baud rate 115200
    setupVectorTable(); // Set up encoder vector table to rename for user

    // Initialize the Independent Watchdog
    IWDG_Init();
Bno055_init();
    while (1) {
  switch (bit_rs) {
    case 0:
        ModeMotor(Stop, 0, 0);
        break;
    case 1:
        ModeMotor(Forward, 66534, 66534);
        break;
    case 2:
        ModeMotor(Backward, 66534, 66534);
        break;
    case 3:
        ModeMotor(Left, 20000, 20000);
        break;
    case 4:
        ModeMotor(Right, 20000, 20000);
        break;
    default:
        /* Not do something */
        break;
}

        sprintf((char *)txData, "%ld, %ld\n", pos_left, pos_right);
        Uart2_Transmiter(txData, strlen((char *)txData));

       
        IWDG_Refresh(); // Refresh the watchdog timer
    }
}

void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) { // Check RXNE flag
        char *start_ptr = strstr((char *)RxData, "DATA:");
        if (start_ptr != NULL) {
            char *data_ptr = start_ptr + 5;
            int received_data = atoi(data_ptr);
            bit_rs = received_data / 1000000;
        }
    }
}

