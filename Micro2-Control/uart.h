 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: John Emile
 *
 * Date: 2/11/2021
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"


/*******************************************************************************
 *                    		  	Enumerations                                   *
 *******************************************************************************/

/* Enum that holds the value of data modes in USART module in AVR */
typedef enum {
	UART_FIVE_BIT_DATA_MODE,UART_SIX_BIT_DATA_MODE,UART_SEVEN_BIT_DATA_MODE,
	UART_EIGHT_BIT_DATA_MODE,UART_NINE_BIT_DATA_MODE=7
}UART_DataBits;

/* Enum that holds the parity type */
typedef enum {
	UART_PARITY_DISABLED,UART_EVEN_PARITY=2,UART_ODD_PARITY
}UART_ParityMode;

/* Enum that holds the number of stop bits to the frame used */
typedef enum {
UART_ONE_STOP_BIT,UART_TWO_STOP_BIT
}UART_StopBits;

/* Enum that holds the standard baud rates of UART */
typedef enum {
UART_BIT_RATE_10_BITS_PER_SECONDS=10,UART_BIT_RATE_300_BITS_PER_SECONDS=300,
UART_BIT_RATE_600_BITS_PER_SECONDS=600,UART_BIT_RATE_1200_BITS_PER_SECONDS=1200,
UART_BIT_RATE_2400_BITS_PER_SECONDS=2400,UART_BIT_RATE_4800_BITS_PER_SECONDS=4800,
UART_BIT_RATE_9600_BITS_PER_SECONDS=9600,UART_BIT_RATE_14400_BITS_PER_SECONDS=14400,
UART_BIT_RATE_19200_BITS_PER_SECONDS=19200,UART_BIT_RATE_38400_BITS_PER_SECONDS=38400,
UART_BIT_RATE_57600_BITS_PER_SECONDS=57600,UART_BIT_RATE_115200_BITS_PER_SECONDS=115200UL,
UART_BIT_RATE_128000_BITS_PER_SECONDS=128000UL,UART_BIT_RATE_256000_BITS_PER_SECONDS=256000UL
}UART_BitRate;

/*******************************************************************************
 *                    		  	  Structures                                   *
 *******************************************************************************/
/* Structure to configure the settings of UART module in AVR Module */
typedef struct {
	UART_BitRate bitRate;
	UART_DataBits data_bits;
	UART_ParityMode parity;
	UART_StopBits stop;
}UART_ConfigType;

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device using dynamic configuration by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
