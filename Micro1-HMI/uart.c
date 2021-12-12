/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: John Emile
 *
 * Date: 2/11/2021
 *******************************************************************************/

#include "uart.h"
#include <avr/io.h> /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
//#include <avr/interrupt.h>

/************************************************************************
 *                           Global variables                           *
 ************************************************************************/
///* holds the UDR of UART whenever there's data in it */
//volatile uint8 g_recievedValue=0;
//
///*Flag that is set to one whenever there's data in UDR */
//volatile uint8 g_recievedFlag=1;

/*******************************************************************************
 *                		 Interrupt Service Routine                      	   *
 *******************************************************************************/
//ISR(USART_RXC_vect)
//{
//	/* Hold the value of the message */
//	g_recievedValue = UDR ;
//
//	/* To indicate that the interrupt service routine has been called and there's data in buffer*/
//	g_recievedFlag =1 ;
//
//}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);


	/************************** UCSRB Description **************************
	 * RXCIE = 1 Enable USART RX Complete Interrupt Enable  (To use UART messages)
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = Number of Bits using Dynamic Configuration
	 * RXB8 & TXB8 is used only for 9-bit data mode (when UCSZ2 = 1)
	 ***********************************************************************/ 

	UCSRB = (1<<RXEN) | (1<<TXEN); //| (1<<RXCIE);

	/*
	 * & with FB to clear UCSZ2 bit (bit2) and preserve the other bits.
	 * &(1<<2) to get the UCSZ2 bit without UCSZ1 & UCSZ0
	 */
	UCSRB = (UCSRB & 0xFB) | ((Config_Ptr ->data_bits) & (1<<2));

	/* Set RXB8 & TXB8 if we're operating 9-bits mode */
	if ( (Config_Ptr ->data_bits) & (1<<2))
		{
			UCSRB |= (1<<RXB8) | (1<<TXB8);
		}


	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = Determine Number of parity bits using dynamic Configuration.
	 * USBS    = Determine Number of stop bits using dynamic configuration.
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/ 	
	UCSRC = (1<<URSEL);

	/*
	 * &0xCF to clear UPM1 (bit 5) & UPM2 (bit4) and preserve the other bits.
	 * <<4 to insert the parity bits in UMP1 & UMP2.
	 */
	UCSRC = (UCSRC & 0xCF) | ((Config_Ptr ->parity)<<4);

	/*
	 * &0xF7 to clear USBS (bit 3) and preserve the other bits.
	 * <<3 to insert the stop bit in USBS
	 *
	 */
	UCSRC = (UCSRC & 0xF7) | ((Config_Ptr ->stop)<<3);

	/*
	 * &0xF9 to clear UCSZ0 (bit 1) & UCSZ1 (bit 2) and preserve the other bits.
	 * &0x03 to get UCSZ0 & UCSZ1 without UCSZ2.
	 * <<1 to insert the character size bits in UCSZ1 & UCSZ0.
	 *
	 */
	UCSRC = (UCSRC & 0xF9) | ( ((Config_Ptr ->data_bits)&0x03) <<1);


	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr->bitRate) * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH
	 * Example : 111100000000
	 * UBRRL is = 00000000
	 * UBRRH = 111100000000>>8 = xxxxxxxx1111
	 */
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	 *******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#'
	 * '#' is an agreement between you and the user to facilitate the communication
	 */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	/* Can be done by do while to receive the first byte safely */

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
