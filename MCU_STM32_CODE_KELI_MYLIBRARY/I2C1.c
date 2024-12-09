/**************************************************************************************************
 *  I2C.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 2/11/2024
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software is provided for controlling driver BTS7960 motor
 *  \endverbatim
 *************************************************************************************************/

#include "I2C1.h"
#define		SR2_BUSY			( 1U << 1 )
#define   CR1_START			( 1U << 8 )
#define		SR1_SB				( 1U << 0 )
#define		SR1_ADDR			( 1U << 1 )
#define		SR1_TXE				( 1U << 7 )
#define		CR1_ACK				( 1U << 10 )
#define   CR1_STOP			( 1U << 9 )
#define		SR1_RXNE			( 1U << 6 )
#define	  SR1_BTF				( 1U << 2 )

/**
 * @brief  Initializes the I2C1 peripheral for communication.
 * Configures GPIO pins for I2C1, sets up clock frequency, and enables the I2C1 peripheral.
 */
void I2C1_Init(void){
			/* Enable Clock to access I2C1 */
				RCC -> APB1ENR  |= ( 1U << 21 ); 
			/* Enable Clock to access I2C1 */
				RCC -> AHB1ENR  |= ( 1U << 1  ); 
			/* Set PE6 and PE9 to Alternate functions */
				GPIOB -> MODER &=~ ( 3U << 12 ); // Clear bit
				GPIOB -> MODER &=~ ( 3U << 18 ); // Clear bit
				GPIOB -> MODER |=  ( 2U << 12 ); // PE6
				GPIOB -> MODER |=  ( 2U << 18 ); // PE9
			/* Enable Pull-up for PE6 and PE9 */
				GPIOB ->OTYPER &=~ ( 1U << 6  ); 
				GPIOB ->OTYPER &=~ ( 1U << 9  ); 
			/* Set Alternate functions for PE6 and PE9 mapping AF04 */
				GPIOB -> AFR[0] &=~ ( 0xF << 24 ); // clear bit
				GPIOB	-> AFR[0] |=  ( 1U  << 26 );
				GPIOB -> AFR[1] &=~ ( 0xF << 4  );
				GPIOB	-> AFR[1] |=  ( 1U  << 4 );
			/* Reset mode I2C1 */
				I2C1->CR1 |=  ( 1U << 15 );
				I2C1->CR1 &=~ ( 1U << 15 );		
				/*Set Peripheral clock frequency*/
				I2C1->CR2 =   ( 1U << 4  ) ;   //16 Mhz

				/*Set I2C to standard mode, 100kHz clock */
				I2C1->CCR = 80 ; // //0B 0101 0000 => Decimal = 80

				/*Set rise time */
				I2C1->TRISE = 17;

				/*Enable I2C1 module */
				I2C1->CR1 |= ( 1U << 0 ) ;
}		
/**
 * @brief  Reads a single byte from a specific memory address on the I2C device.
 * @param  saddr: The I2C slave address.
 * @param  maddr: The memory address on the slave device.
 * @param  data: Pointer to a variable to store the read data.
 */
void I2C1_byteRead ( char saddr, char maddr , char *data ){
			 volatile int tmp;

	  /* Wait until bus not busy */
	  while ( I2C1->SR2 & ( 1U << 1 ) ){}

	  /* Generate start in master , Repeated start generation in slave mode */
	  I2C1->CR1 |= 1U << 8;

	  /* Wait until start flag is set */
	  while ( !(I2C1->SR1 & ( 1U << 0 ) ) ){}

	  /* Transmit slave address + Write */
	   I2C1->DR = saddr << 1;

	  /* Wait until addr flag is set */
	   while ( !( I2C1->SR1 & ( 1U << 1 ) ) ){}

	  /* Clear addr flag */
	  tmp = I2C1->SR2;

      /* Send memory address */
      I2C1->DR = maddr;

      /*Wait until transmitter empty */
     while ( !( I2C1->SR1 & ( 1U<<7 ) ) ){}

     /*Generate restart */
      I2C1->CR1 |= ( 1U << 8 );

      /* Wait until start flag is set */
     while ( !( I2C1->SR1 & ( 1U << 0 ) ) ){}

     /* Transmit slave address + Read */
     I2C1->DR = saddr << 1 | 1;

     /* Wait until addr flag is set */
    while ( !(I2C1->SR1 & ( 1U << 1 ) ) ){}

    /* Disable Acknowledge */
    I2C1->CR1 &= ~( 1U << 10 );

    /* Clear addr flag */
    tmp = I2C1->SR2;

    /* Generate stop after data received */
     I2C1->CR1 |= ( 1U<<9 ) ;

    /* Wait until RXNE flag is set */
    while ( !( I2C1->SR1 & ( 1U<<6 ) ) ){}

    /* Read data from DR */
      *data++ = I2C1->DR;

	}
/**
 * @brief  Reads multiple bytes from a specific memory address on the I2C device.
 * 
 * @param  saddr: The I2C slave address.
 * @param  maddr: The memory address on the slave device.
 * @param  n: The number of bytes to read.
 * @param  data: Pointer to a buffer to store the read data.
 */
void I2C1_burstRead ( char saddr, char maddr, int n, char *data ){
volatile int tmp;

	 /* Wait until bus not busy */
	  while ( I2C1->SR2 & ( SR2_BUSY ) ){}

      /* Generate start */
    I2C1->CR1 |= CR1_START;

    /* Wait until start flag is set */
     while ( !( I2C1->SR1 & SR1_SB ) ){}

     /* Transmit slave address + Write */
     I2C1->DR = saddr << 1;

     /* Wait until addr flag is set */
    while ( !( I2C1->SR1 & SR1_ADDR ) ){}

    /* Clear addr flag */
     tmp = I2C1->SR2;

     /* Wait until transmitter empty */
    while ( !( I2C1->SR1 & SR1_TXE ) ){}

    /*Send memory address */
    I2C1->DR = maddr;

    /*Wait until transmitter empty */
    while ( !( I2C1->SR1 & SR1_TXE ) ){}

    /*Generate restart */
    I2C1->CR1 |= CR1_START;

    /* Wait until start flag is set */
    while ( !( I2C1->SR1 & SR1_SB ) ){}

    /* Transmit slave address + Read */
    I2C1->DR = saddr << 1 | 1;

    /* Wait until addr flag is set */
    while ( !( I2C1->SR1 & ( SR1_ADDR ) ) ){}

    /* Clear addr flag */
    tmp = I2C1->SR2;

    /* Enable Acknowledge */
      I2C1->CR1 |=  CR1_ACK;

    while(n > 0U)
    {
    	/*if one byte*/
    	if(n == 1U)
    	{
    		/* Disable Acknowledge */
    	    I2C1->CR1 &= ~CR1_ACK;

    	    /* Generate Stop */
    	    I2C1->CR1 |= CR1_STOP;

 			/* Wait for RXNE flag set */
            while ( !( I2C1->SR1 & SR1_RXNE ) ){}

            /* Read data from DR */
            *data++ = I2C1->DR;
            break;
    	}
    	else
    	{
       	 /* Wait until RXNE flag is set */
           while ( !( I2C1->SR1 & SR1_RXNE ) ){}

           /* Read data from DR */
           (*data++) = I2C1->DR;

           n--;
    	}
    }
}
/**
 * @brief  Writes multiple bytes to a specific memory address on the I2C device.
 * 
 * @param  saddr: The I2C slave address.
 * @param  maddr: The memory address on the slave device.
 * @param  n: The number of bytes to write.
 * @param  data: Pointer to the buffer holding the data to write.
 */
void I2C1_burstWrite ( char saddr, char maddr , int n, char *data ){

	volatile int tmp;

	 /* Wait until bus not busy */
	 while ( I2C1->SR2 & ( SR2_BUSY ) ){}

     /* Generate start */
    I2C1->CR1 |= CR1_START;

    /* Wait until start flag is set */
    while ( !( I2C1->SR1 & ( SR1_SB ) ) ){}

    /* Transmit slave address */
    I2C1->DR = saddr << 1;

    /* Wait until addr flag is set */
    while ( !( I2C1->SR1 & ( SR1_ADDR ) ) ){}

    /* Clear addr flag */
    tmp = I2C1->SR2;

    /* Wait until data register empty */
    while ( !( I2C1->SR1 & ( SR1_TXE ) ) ){}

    /* Send memory address */
    I2C1->DR = maddr;

    for ( int i = 0; i < n; i++) {

     /* Wait until data register empty */
        while ( ! (I2C1->SR1 & ( SR1_TXE )  ) ){}

      /* Transmit memory address */
      I2C1->DR = *data++;
    }

    /* Wait until transfer finished */
    while ( !( I2C1->SR1 & ( SR1_BTF ) ) ){}

    /* Generate stop */
   I2C1->CR1 |= CR1_STOP;
}