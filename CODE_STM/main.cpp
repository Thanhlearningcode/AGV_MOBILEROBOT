///***************************************************************************
// * @file    main.c
// * @brief   Main program for the AGV (Autonomous Guided Vehicle) project
// * @details This file serves as the core of the AGV system, providing the primary 
// *          interface and functionalities required for autonomous navigation and control.
// * @version 1.0
// * @date    2024-10-07
// * @author  NGUYEN VAN THANH
// * @website https://thanhlearningcode.github.io/Myprofile/
// *****************************************************************************************************/
///********************************************* Libraries *********************************************/

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
#include "main.h"
#include "main.h"
#include "mainpp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    Rcc_Init();        // 72 MHz
    Exti_Init();       // External interrupt for encoder
    Tim2_Init();       // PWM
    Uart1_Init(115200); // UART to ESP32 with baud rate 115200
    setupVectorTable(); // Set up encoder vector table to rename for user

    // Initialize the Independent Watchdog
    IWDG_Init();
Bno055_init();
	
setup();
while(1){
loop();
}
}