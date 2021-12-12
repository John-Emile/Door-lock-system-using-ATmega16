/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the AVR LCD driver
 *
 * Author: John Emile
 *
 * Date : 3/10/2021
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_RS_PORT_ID 				   PORTB_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_RW_PORT_ID 				   PORTB_ID
#define LCD_RW_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID 				   PORTB_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTA_ID

#define LCD_FIRST_LINE_START_ID 		0x00
#define LCD_SECOND_LINE_START_ID		0x40
#define LCD_THIRD_LINE_START_ID        	0x10
#define LCD_FOURTH_LINE_START_ID		0x50

/* LCD commands */
#define LCD_CLEAR_COMMAND	 	  	    0x01
#define LCD_RETURN_HOME 			    0x02
#define LCD_CURSOR_OFF				    0x0C
#define LCD_CURSOR_ON			 		0x0E
#define LCD_SET_CURSOR_LOCATION	 		0x80
#define LCD_TWO_LINES_EIGHT_BITS_MODE   0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE    0x28
#define LCD_ONE_LINE_EIGHT_BITS_MODE    0x30
#define LCD_ONE_LINE_FOUR_BITS_MODE     0x20

/*******************************************************************************
 *							Functions prototypes 							   *
 *******************************************************************************/

/*
 * Description:
 * Initialize the LCD
 */
void LCD_init(void);


/*
 * Description:
 * Send the required command to LCD
 */
void LCD_sendCommand(uint8 command);


/*
 * Description:
 * Display the required character on LCD
 * Same function as the send command, except the register select
 * @Send command -> Rs = 0 as we send an instruction
 * @Display char -> Rs = 1 as we send data to display
 */
void LCD_displayCharacter(uint8 data);


/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char* Str);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col);


/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);


/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data);


/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);


#endif /* LCD_H_ */
