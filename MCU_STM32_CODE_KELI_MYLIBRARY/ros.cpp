/***************************************************************************
 * @file    ros.cpp
 * @brief   Main program for the Ros.h
 * @details This file serves as the core of the AGV system, providing the primary
 *          interface and functionalities required for autonomous navigation and control.
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH && PHAN DANG DANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 *****************************************************************************************************/


#include "ros.h"

namespace ros {
    void normalizeSecNSec ( unsigned& sec, unsigned& nsec ) {
        while ( nsec >= 1000000000 ) {
            nsec -= 1000000000;
            ++sec;
        }
    }
}
