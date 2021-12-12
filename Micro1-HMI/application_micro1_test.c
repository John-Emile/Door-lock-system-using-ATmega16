/******************************************************************************
 *
 * File Name: application.c
 *
 * Description: Door lock system functions source file.
 *
 * Author: John Emile
 *
 * Date : Oct 30, 2021
 *
 *******************************************************************************/

#include "application_micro1.h"
#include <util/delay.h>
#define F_CPU 8000000UL

/*******************************************************************************
 *                    		Global Variables                                   *
 *******************************************************************************/

/* Flag that indicates that we have finish entering the password & To stop the timer */
uint8 g_password_entry_finished = 0;

/* To use it for timer delay functions */
extern uint8 g_tick;

/*******************************************************************************
 *                    		  Function Declarations                            *
 *******************************************************************************/

void MICROCONTROLLER_init(void)
{
	LCD_init();

	UART_ConfigType UART_configPtr = {UART_BIT_RATE_9600_BITS_PER_SECONDS,UART_EIGHT_BIT_DATA_MODE,UART_PARITY_DISABLED,UART_ONE_STOP_BIT};
	UART_init(&UART_configPtr);
}


void APP_askForPasswordFirstTime(void)
{
	/* Flag that indicates that we have finish entering the password */
	uint8 password_entry_finished = 0;

	/* To get the pressed button */
	uint8 g_keypad_button = 0;

	/* When called from New Password function */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter New Pass:");

	/* Move cursor to second line */
	LCD_moveCursor(1,0);

	/* Sends to Micro2 to be prepared to receive first time password */
	UART_sendByte(PASSWORD_UNCHECKED_FIRST_TIME);

	/* Loop responsible for number of digits in password */
	while (password_entry_finished==0) {

		/* Get key from user */
		g_keypad_button = KEYPAD_getPressedKey();

		/* Check if it's a valid number (0-9) */
		if ( ((g_keypad_button > 0) && (g_keypad_button <=9)) || (g_keypad_button == '0'))
		{
			/* Send it to Micro 2 */
			UART_sendByte(g_keypad_button);

			/* Display * for every character input */
			LCD_displayCharacter('*');
		}

		/* Check if the user finished entering the password */
		else if (g_keypad_button == KEYPAD_ENTER_BUTTON)
		{
			/* Set the flag to 1 to break out of the loop*/
			password_entry_finished=1;

			/* Send to Micro2 that user have finished entering the pass */
			UART_sendByte(APP_END_OF_PASSWORD);
		}
		/* If any button is pressed more that 1000ms , Count it as a second input */
		_delay_ms(BUTTON_DELAY);
	}

}

void APP_confirmPasswordFirstTime(void)
{
	/* Flag that indicates that we have finish entering the password */
	uint8 password_entry_finished = 0;

	/* To get the pressed button */
	uint8 g_keypad_button = 0;

	/* Show once at first and move cursor to second line*/
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Re-enter Pass:");
	LCD_moveCursor(1,0);

	/* Sends to Micro2 to be prepared to receive first time password */
	UART_sendByte(SECOND_PASSWORD_UNCHECKED_FIRST_TIME);

	/* Loop responsible for number of digits in password */
	while (password_entry_finished==0) {
		/* Get key from user */
		g_keypad_button = KEYPAD_getPressedKey();

		/* Check if it's a valid number (0-9) */
		if ( ((g_keypad_button > 0) && (g_keypad_button <=9)) || (g_keypad_button == '0'))
		{
			/* Send it to Micro 2 */
			UART_sendByte(g_keypad_button);

			/* Display * for every character input */
			LCD_displayCharacter('*');
		}

		/* Check if the user finished entering the password */
		else if (g_keypad_button == KEYPAD_ENTER_BUTTON)
		{
			/* Set the flag to 1 to break out of the loop*/
			password_entry_finished=1;

			/* Send to Micro2 that user have finished entering the pass */
			UART_sendByte(APP_END_OF_PASSWORD);
		}
		/* If any button is pressed more that 1000ms , Count it as a second input */
		_delay_ms(BUTTON_DELAY);
	}

}

void APP_askForPassword(void)
{
	/* Flag that indicates that we have finish entering the password */
	uint8 password_entry_finished = 0;

	/* To get the pressed button */
	uint8 g_keypad_button = 0;

	/* Show once at first */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Pass:");

	/* Move cursor to second line */
	LCD_moveCursor(1,0);

	if (g_change ==0)
	{
		/* Sends to Micro2 to be prepared to receive first time password */
		UART_sendByte(PASSWORD_UNCHECKED_FOR_DOOR);
	}
	else if (g_change ==1)
	{
		UART_sendByte(PASSWORD_UNCHECKED_FOR_CHANGE);
	}
	else if (g_change ==2)
	{
		UART_sendByte(PASSWORD_UNCHECKED_LOGIN);
	}
	/* Loop responsible for number of digits in password */
	while (password_entry_finished==0) {

		/* Get key from user */
		g_keypad_button = KEYPAD_getPressedKey();

		/* Check if it's a valid number (0-9) */
		if ( ((g_keypad_button > 0) && (g_keypad_button <=9)) || (g_keypad_button == '0'))
		{
			/* Send it to Micro 2 */
			UART_sendByte(g_keypad_button);

//			LCD_intgerToString(g_keypad_button);
			/* Display * for every character input */
			LCD_displayCharacter('*');
		}

		/* Check if the user finished entering the password */
		else if (g_keypad_button == KEYPAD_ENTER_BUTTON)
		{
			/* Set the flag to 1 to break out of the loop*/
			password_entry_finished=1;

			/* Send to Micro2 that user have finished entering the pass */
			UART_sendByte(APP_END_OF_PASSWORD);
		}
		/* If any button is pressed more that 1000ms , Count it as a second input */
		_delay_ms(BUTTON_DELAY);
	}

}


/* Function that get the password and its confirmation */
void APP_getNewPassword (void)
{

	/* Get a password for the first time */
	APP_askForPasswordFirstTime();

	/* Get a confirmation password */
	APP_confirmPasswordFirstTime();

}

void APP_mainMenu(void)
{
	/* To get the pressed button */
	uint8 keypad_button = 0;

	/* Screen commands */
	LCD_clearScreen();
	LCD_displayString("+ : Open Door");
	LCD_displayStringRowColumn(1,0,"- : Change Pass");

	UART_sendByte(APP_mainMenuCheck);

	/* Get key from user */
	keypad_button= KEYPAD_getPressedKey();
	//	LCD_displayCharacter(keypad_button);

	/* Send the choice of user */
	UART_sendByte(keypad_button);

}

void APP_doorProcessing(void)
{

	LCD_clearScreen();
	APP_startTimer_3Sec();


	LCD_displayString("Door is Opening");
	/* Must call APP_startTimer_3Sec before to identify g_tick every 3 sec */
	/* Delay for 15 second */
	while (g_tick !=5);
	g_tick = 0;

	/* Delay for 3 second */
	LCD_clearScreen();
	LCD_displayString("Stop");
	while (g_tick !=1);
	g_tick = 0;

	/* Delay for 15 second */
	LCD_clearScreen();
	LCD_displayString("Door is Closing");
	while (g_tick !=5);
	g_tick=0;

	TIMER_DeInit(TIMER1_ID);

}

void APP_invalidInput(void)
{
	LCD_clearScreen();
	LCD_displayString("INVALID INPUT");

	/* Delay for 1 sec */
	APP_startTimer_1Sec();
	APP_Timer1DelayForScreenCheck();

}

void APP_wrongPassword(void)
{
	LCD_clearScreen();
	LCD_displayString("WRONG PASSWORD");

	/* Delay for 1 sec */
	APP_startTimer_6Sec();
	APP_Timer1DelayForBuzzerCheck();

	/* Show menu */
	APP_mainMenu();

}
