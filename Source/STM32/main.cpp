/***************************************************************************
 * @file    main.cpp
 * @brief   Main program for the AGV (Autonomous Guided Vehicle) project
 * @details This file serves as the core of the AGV system, providing the primary
 *          interface and functionalities required for autonomous navigation and control.
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH && PHAN DANG DANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 **************************************************************************/ 

#include "main.h"
#include "mainpp.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Uart2.h"
extern "C" {
    #include "Rcc_Cfg.h"
}

/**
 * @brief Main entry point for the program
 * @return int Exit status of the program
 */
int main() {
    /* Configure RCC to 72MHz */
    Rcc_Clock_Init();
		Uart2_Init (115200);
    /*Initialize setup*/
    setup();
   
  while (true) {
    loop();
    }
    return 0; 
}
