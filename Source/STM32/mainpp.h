/**************************************************************************************************
 *  mainpp.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This file provides the header for mainpp control functions and initialization.
 *  \endverbatim
 *************************************************************************************************/

#ifndef MAINPP_H_
#define MAINPP_H_

/**************************************************************************************************
 *  Include Section
 *************************************************************************************************/

#ifdef __cplusplus
 extern "C" {
#endif

/**************************************************************************************************
 *  Function Prototypes
 *************************************************************************************************/

/**
 * \brief  This function is called once during initialization of the system.
 * \details This function performs any necessary setup tasks like initializing hardware.
 *          It is called at the beginning of the program execution.
 */
void setup(void);

/**
 * \brief  This function is called repeatedly in an infinite loop after setup.
 * \details This function should contain the main task of the program to be executed periodically.
 */
void loop(void);

#ifdef __cplusplus
}
#endif

#endif /* MAINPP_H_ */
