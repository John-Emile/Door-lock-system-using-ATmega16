/******************************************************************************
 *
 * File Name: uart_messages.h
 *
 * Description: Header file for USART AVR driver door lock system application.
 *
 * Author: John Emile
 *
 * Date : Nov 4, 2021
 *
 *******************************************************************************/

#ifndef UART_MESSAGES_H_
#define UART_MESSAGES_H_

/*******************************************************************************
 *                    		  Preprocessor Macros                              *
 *******************************************************************************/
#define MICRO1_READY 										0x10
#define MICRO2_READY										0x11
#define PASSWORD_UNCHECKED_FIRST_TIME						'!'
#define SECOND_PASSWORD_UNCHECKED_FIRST_TIME				')'
#define PASSWORDS_UNMATCHED_FIRST_TIME						';'
#define PASSWORDS_MATCHED									'@'
#define PASSWORDS_UNMATCHED									'$'
#define INVALID_INPUT										'%'
#define APP_END_OF_PASSWORD									'^'
#define PASSWORD_WRONG										'&'
#define DOOR_OPENING										'*'
#define DOOR_CLOSING										'('
#define ASK_FOR_PASSWORD									'?'
#define NOT_FIRST_TIME										'N'
#define APP_mainMenuCheck									'{'
#define ASK_FOR_NEW_PASSWORD								'}'
#define ASK_FOR_CONFIRM_PASSWORD							':'
#define PASSWORDS_TAKEN										'>'
#define ASK_FOR_CHANGING_PASSWORD							'C'
#define ASK_FOR_DOOR_PASSWORD								'D'
#define SHOW_MENU											'S'
#define PASSWORD_UNCHECKED_FOR_DOOR							'K'
#define PASSWORD_UNCHECKED_FOR_CHANGE						'M'
#define CHANGE_PASSWORD										'Z'
#define PASSWORD_UNCHECKED_LOGIN							'L'
#endif /* UART_MESSAGES_H_ */
