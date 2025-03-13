#include "watchdog.h"

void IWDG_Init(void) {
    IWDG->KR = 0x5555;  // M? khóa các thanh ghi IWDG

    // C?u hình Prescaler và Reload value
   IWDG->PR = 0x06;  // Prescaler = 64
    IWDG->RLR = 200;          // Reload value cho 4 giây (37kHz * 4s / 64 = 200)

    // Kh?i d?ng IWDG
    IWDG->KR = 0xAAAA;  // Kh?i d?ng IWDG
}

void IWDG_Feed(void) {
    IWDG->KR = 0xAAAA;  // Refresh the watchdog, preventing it from resetting the system
}