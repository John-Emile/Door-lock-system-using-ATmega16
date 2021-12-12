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
#include "lcd.h"
#include "uart.h"
#include "uart_messages.h" /* To use predefined messages */
#include "buzzer.h"
#include "timer.h"
#include "external_eeprom.h"
#include "motor.h"
#include "twi.h"
#include "timer_delay.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/delay.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define APP_REQUIRED_PASSWORD_NUMBER_OF_DIGITS				5
#define BUTTON_DELAY 										500
#define SUCCESS												1
#define ERROR												0
#define MAX_TRIALS_ERROR									3
#define EEPROM_PASSWORD_ADDRESS_FLAG						0x3E8
#define EEPROM_PASSWORD_ADDRESS								0x0311
#define EEPROM_PASS_SIZE									0x3E0

/* Timer delay */
#define TIMER_LCD_SCREEN_DELAY_ID							  1
#define TIMER_BUZZER_DELAY_ID								  2
#define TIMER_BUTTON_DELAY_ID								  3
#define TIMER_MOTOR_MOVE_SCREEN_DELAY_ID					  4
#define TIMER_MOTOR_STOP_SCREEN_DELAY_ID					  5
/*******************************************************************************
 *                            Global Variables                                 *
 *******************************************************************************/
extern uint8 g_first_time_flag;

/* result of compare */
extern uint8 status;
extern uint8 g_change;

/* Hold the value of passwords */
extern uint8 g_first_password[10];
extern uint8 g_second_password[10];
/*******************************************************************************
 *                    		Functions Prototypes                               *
 *******************************************************************************/

/*
 * [function Name] : APP_receivePassword
 * [Description] : This function is responsible for receiving password from Uc1
 * [Args] :
 * [in] : uint8* password_entry
 * This argument shall indicate an array that is passed by reference which store the password in it
 * [Returns] : None
 */
void APP_receivePassword(uint8* a_password_entry_Ptr);

/*
 * [function Name] : APP_checkPassword
 * [Description] : A function that assign the eeprom to a global variable to be compared in APP_comparePasswords function
 * [Args] :
 * [in] : uint8* a_checkPassword_Ptr
 * This argument shall indicate an array that is passed by reference to store the eeprom password in it.
 * [Returns] :
 */

void APP_comparePasswords(const uint8* a_first_pass_Ptr);

void APP_comparePasswordsFirstTime(const uint8* a_first_pass_Ptr ,const uint8* a_second_pass_Ptr);


void APP_mainMenuChecker (void);
void APP_doorProcessing (void);
void MICROCONTROLLER2_init(void);
void APP_checkIfFirstTimeEntry(void);



#endif /* APPLICATION_H_ */
