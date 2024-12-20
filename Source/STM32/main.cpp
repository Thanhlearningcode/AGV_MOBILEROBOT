/***************************************************************************
 * @file    main.cpp
 * @brief   Main program for the AGV (Autonomous Guided Vehicle) project
 * @details This file serves as the core of the AGV system, providing the primary
 *          interface and functionalities required for autonomous navigation and control.
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH && PHAN DANG DANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 *****************************************************************************************************/
#include "main.h"
#include "mainpp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern "C" {
    #include "Rcc_Cfg.h"
}



int main(void)
{
	
	/* Configure RCC to 72MHZ */
	Rcc_Clock_Init () ;
/* Programming */
   setup();
  
  while (1)
  {
   
	  loop();
    
  }

}
