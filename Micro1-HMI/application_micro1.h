/******************************************************************************
 *
 * File Name: application.h
 *
 * Description: Door lock system functions header file.
 *
 * Author: John Emile
 *
 * Date : Oct 30, 2021
 *
 *******************************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "std_types.h"
#include "keypad.h" /* To use getButton function */
#include "lcd.h"
#include "uart.h"
#include "uart_messages.h" /* To use predefined messages */
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_delay.h"
/************************************************************************
 *                           Global variables                           *
 ************************************************************************/

extern uint8 g_change;
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define APP_REQUIRED_PASSWORD_NUMBER_OF_DIGITS				5
#define BUTTON_DELAY 										3000

#define TIMER_LCD_SCREEN_DELAY_ID							  1
#define TIMER_BUZZER_DELAY_ID								  2
#define TIMER_BUTTON_DELAY_ID								  3
#define TIMER_MOTOR_MOVE_SCREEN_DELAY_ID					  4
#define TIMER_MOTOR_STOP_SCREEN_DELAY_ID					  5
/*******************************************************************************
 *                    		 Functions Prototypes                              *
 *******************************************************************************/

/* Responsible for taking the password from the user for the first time only */
void APP_askForPasswordFirstTime(void);

/* Responsible for confirming the password from the user for the first time only */
void APP_confirmPasswordFirstTime(void);

/* Holds the call of the first time functions */
void APP_getNewPassword (void);

/* Regular check for password */
void APP_askForPassword(void);

/* Menu call */
void APP_mainMenu(void);

/* Microcontroller drivers init */
void MICROCONTROLLER_init(void);

void APP_invalidInput(void);
void APP_changePassword(void);
void APP_doorProcessing(void);
void invalidInput(void);
void APP_wrongPassword(void);




#endif /* APPLICATION_H_ */
