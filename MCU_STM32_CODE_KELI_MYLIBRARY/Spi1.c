#include "Spi1.h"


void Spi1_Init(void){
		/* Enable Clock to access SPI1 & GPIOB */
				RCC		 ->       AHB1ENR |= ( 1U << 2 	);  // Enable clock to access GPIOB
				RCC		 ->       APB2ENR |= ( 1U << 12	);  // Enable clock to access Spi1
		/* Configuration GPIOB set PB3 -> SCK to AF mode
										       set PB4 -> MISO to AF mode
										       set PB5 -> MOSI to AF mode
										       set PB6 -> NSS  to output pushpull ( or open drain )  */

				GPIOB	 ->       MODER  |=  ( 0xFFFF << 6 ); // Clear bit
				GPIOB	 ->       MODER	 |=  ( 0x1222 << 6 ); // AF mode PA3 -> PA5 , PA6 output 
				GPIOB	 ->				OTYPER &=~ ( 1U  << 6 ); // NSS  to output pushpull
		/* Alternate function AF05 mapping ( 0101: AF5 ) */
 				GPIOB  -> 			AFR[0] |=  ( 5U << 12 ); // PA3
				GPIOB	 ->       AFR[0] |=  ( 5U << 16 ); // PA4
				GPIOB  ->       AFR[0] |=  ( 5U << 20 ); // PA5
		
	/* Configuration Spi  */
				SPI1   ->       CR1    &=~ ( 1U << 0) | ( 1U << 1 ) ; // CPOL set CK to 0 when idel , CPHA set the first clock transition is the first data capture edge
				SPI1   ->       CR1	   |=  (	1U << 2	 ); // Master configuration
				SPI1   ->				CR1    |=  ( 3U << 3  ); // Fplck/4 <=> 72/4 => 4mhz 
				SPI1   ->       CR1		 &=~ ( 1U << 7  ); // MSB transmitted first 
				SPI1   ->       CR1    |=  ( 1U << 8  )| ( 1U << 9 ) ;// SSI and SSM enable
				SPI1   ->       CR1   &=~  ( 3U << 10 ); // Full duxplex and 8-bit data frame format
				SPI1   ->       CR1		 |=  ( 1U << 6  ); // Enable SPI1			
}	

void Spi1_Transmitrer( uint8_t *data, uint8_t size){
			 uint8_t i=0;
			 uint8_t temp;
		while ( i < size ){
				/* Wait until Tx is set */
				while ( ! ( ( SPI1->SR>>1 ) &0x1 ) );
						SPI1->DR = data[i];
						i++;		
		}
			while( ! ( ( SPI1->SR>>1 )&0x1 ) );
	/* Wait until busy flag is not busy */
		while(! ( ( SPI1->SR>>7 )&0x1 ) );
/* Clearing the OVR bit is done by a read operation by read to access to the SPI_SR register		*/
}	
void Spi1_ReceiveData ( uint8_t *data, uint8_t size ){
	int i=0;
	while ( size ){
	/* Wait Rx is emty */
		while( !( ( SPI1->SR )&0x1 ) );
		
		SPI1->DR =0xFF; // Send dummy 
	  while ( !( SPI1->SR & SPI_SR_RXNE  ));
	data[i]=SPI1->DR;
		i++;
		size--;
	}
}