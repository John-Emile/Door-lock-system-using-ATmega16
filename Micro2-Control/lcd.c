/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the AVR LCD driver
 *
 * Author: John Emile
 *
 * Date : 3/10/2021
 *******************************************************************************/

/*******************************************************************************
 *                     			   Includes	                                   *
 *******************************************************************************/
#include "lcd.h" /* Every C file includes its header file */
#include "gpio.h" /* The LCD interacts with the GPIO pins */
#include "util/delay.h" /* To use the delay function */
#include <stdlib.h> /* to use itoa function */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Initialize the LCD
 */
void LCD_init(void)
{
	/* Configure the direction for RS, RW and E pins as output pins */
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

	/* Specify data register as output register */
	GPIO_setupPortDirection(PORTC_ID,PORT_OUTPUT);

	/* use 2-line LCD + 8-bit Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

	/* cursor off */
	LCD_sendCommand(LCD_CURSOR_OFF);

	/* clear LCD at the beginning */
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}

/*
 * Description:
 * Send the required command to LCD
 */
void LCD_sendCommand(uint8 command)
{
	/* RS = 0; Transferring instruction data  */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);

	/* Writing on LCD */
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);

	/* Will do all the delay as 1 ms to make it easier */

	/* Address setup time minimum as 50 ns */
	_delay_ms(1);

	/* Enable the LCD */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);

	/* Enable high level width - Data set-up time = 290 - 100 = 190 ns minimum*/
	_delay_ms(1);

	/* Send command */
	GPIO_writePort(LCD_DATA_PORT_ID,command);

	/* Data set-up time = 100 ns minimum */
	_delay_ms(1);

	/* Disable the lCD */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);

	/* Data hold time = 13 ns minimum */
	_delay_ms(1);

}

/*
 * Description:
 * Display the required character on LCD
 * Same function as the send command, except the register select
 * @Send command -> Rs = 0 as we send an instruction
 * @Display char -> Rs = 1 as we send data to display
 */
void LCD_displayCharacter(uint8 data)
{
	/* RS = 1; Transferring display data */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);

	/* Writing on LCD */
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);

	/* Will do all the delay as 1 ms to make it easier */

	/* Address setup time minimum as 50 ns */
	_delay_ms(1);

	/* Enable the LCD */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);

	/* Enable high level width - Data set-up time = 290 - 100 = 190 ns minimum*/
	_delay_ms(1);

	/* Send command */
	GPIO_writePort(LCD_DATA_PORT_ID,data);

	/* Data set-up time = 100 ns minimum */
	_delay_ms(1);

	/* Disable the lCD */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);

	/* Data hold time = 13 ns minimum */
	_delay_ms(1);

}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char* str)
{
	/* Counter for the array of characters */
	uint8 i =0;
	while (str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Address of the cursor depends on the row */
	switch (row) {
	case 0 : /* First line */
		lcd_memory_address = LCD_FIRST_LINE_START_ID + col ;
		break;
	case 1 : /* Second line */
		lcd_memory_address = LCD_SECOND_LINE_START_ID + col;
		break;
	case 2 : /* Third line */
		lcd_memory_address = LCD_THIRD_LINE_START_ID + col;
		break;
	case 3 : /* Fourth line */
		lcd_memory_address = LCD_FOURTH_LINE_START_ID + col;
		break;
	}
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);

}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str)
{
	/* Move cursor to the desired position */
	LCD_moveCursor(row, col);

	/* Start printing the string from that position */
	LCD_displayString(str);
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
	/* String to hold the ascii result*/
	char buffer[16]; /* The maximum size of characters in one line in screenis 16 */

	/* Use itoa (integer to ascii) C function to convert the data to its corresponding ASCII value, included in stdlib header file*/
	itoa(data,buffer,10);  /*10 is the base for decimal*/
	/* data transfers its content to buffer with base 10 */

	LCD_displayString(buffer); /* Display the string */

}


/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	/* Send clear display command */
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

