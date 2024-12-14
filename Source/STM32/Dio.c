#include "Dio.h"

void Dio_Init(void){
	//	RCC->AHB1ENR|=(1U<<02); // System configuration GPIOC clock enable
			GPIOC->MODER &= ~ ( 3U << 12 ); // Input mode PC6
			GPIOC->MODER &= ~ ( 3U << 16 ); // Input mode PC8
			
			GPIOC->PUPDR &= ~ ( 3U << 12 ); // No pull-up and No pull-down
			GPIOC->PUPDR &= ~ ( 3U << 12 ); // No pull-up and No pull-down
}
int readEncoder1(void){
	int c = ( ( GPIOC->IDR>>8 ) & 0x1 ) ;
	return c;

}
int readEncoder2(void){
int c1 =( ( GPIOC->IDR>>6 ) &0x1 );
	return c1;
}