#include "Spi2.h"
/* PB12 -> NSS  -> OUTPUT 
	 PB13 -> SCK 	-> AF MODE 
	 PB14 -> MISI -> AF MODE 
	 PB15 -> MOSI -> AF MODE 
*/

void Spi2_Init(void){
		/* Configure clock to access GPIOB */
		RCC -> AHB1ENR |=  ( 1U << 1  ); 
		/* Configure clock to access  SPI2 */
		RCC -> APB1ENR |-  ( 1U << 14 ); 
	  /* Configure GPIOB to AF-MODE */
		GPIOB -> MODER &=~ ( 0xFF << 24 ); // clear bit
		GPIOB -> MODER |=  ( 1U  << 24 ); // PB12 Output
		GPIOB -> MODER |=  ( 2U  << 26 ); // PB13 set AF-Mode
		GPIOB -> MODER |=  ( 2U  << 28 ); // PB14 set AF-Mode
		GPIOB -> MODER |=  ( 2U  << 30 ); // PB15 set AF-Mode
		/* Configure PB12 to Output Push-up */
		GPIOB ->MODER  &=  ( 1U  << 24 );
		/* Configure Spi2 */
		SPI2 -> CR1 &=~ ( 3U << 0  ); // CPOL 0 CPHA 0
		SPI2 -> CR1 |=  ( 1U << 2  ); // Master configuration 
		SPI2 -> CR1 |=  ( 3U << 3  ); // Fpclk/16 -> 16/16 =1mhz
		SPI2 -> CR1 |=  ( 1U << 7  ); // MSB
		SPI2 -> CR1 |=  ( 3U << 8  ); // SSI & SSM enable
		SPI2 -> CR1 &=~ ( 1U << 10 ); // Full-duplex
		SPI2 -> CR1 &=~ ( 1U << 11 ); // 8-bit data
		SPI2 -> CR1 |=  ( 1U << 6  ); // SPI2 Enable
}
void Spi2_Transmitrer ( uint8_t *data, uint8_t size ){
			 uint8_t i=0;
			 uint8_t temp;
		while ( i < size ){
				/* Wait until Tx is emty */
				while( !( ( SPI1->SR>>1 )&0x1 ) );
						SPI2->DR = data[i];
						i++;		
		}
			while( !( ( SPI2->SR>>1 )&0x1 ) );
	/* Wait until busy flag is not busy */
		while( !( ( SPI2->SR>>7 )&0x1 ) );

}	
void Spi2_ReceiveData(uint8_t *data, uint8_t size){
	int i=0;
	while( size ){
	/* Wait Rx is emty */
		while( !  (( SPI2->SR)&0x1) );
		SPI2->DR =0xFF; // Send dummy 
	  while (!(SPI2->SR & SPI_SR_RXNE));
		/* Clearing the OVR bit is done by a read operation by read to access to the SPI_SR register		*/
	data[i]=SPI2->DR;
		i++;
		size--;
	}
}