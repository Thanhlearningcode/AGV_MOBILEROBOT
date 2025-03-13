#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "stm32f4xx.h"

// C?u hình Watchdog
void IWDG_Init(void);

void IWDG_Feed(void) ;
#endif /* WATCHDOG_H */
