/******************************************************************************
 *
 * File Name: application_micro2.c
 *
 * Description: 
 *
 * Author: John Emile
 *
 * Date : Nov 2, 2021
 *
 *******************************************************************************/

#include "application_micro2.h"
#include "util/delay.h"
#define F_CPU 8000000UL

/*******************************************************************************
 *                    		Global Variables                                   *
 *******************************************************************************/
/* Hold the number of incorrect input of user */
uint8 g_trial_times =0;

/* result of compare */
uint8 g_status;

/* To hold the password in eeprom */
uint8 g_eeprom_pass[12];

/* To indicate whether there's a saved password in memory or not */
uint8 password_check;

/* To determine which procedure to do after comparing passwords */
uint8 g_change=0;


extern uint8 g_tick;

/*******************************************************************************
 *                    		Functions Definitions                              *
 *******************************************************************************/

void MICROCONTROLLER2_init(void)
{
	LCD_init();

	BUZZER_init();
	DCMOTOR_init();

	EEPROM_init();

	UART_ConfigType UART_configPtr = {UART_BIT_RATE_9600_BITS_PER_SECONDS,UART_EIGHT_BIT_DATA_MODE,UART_PARITY_DISABLED,UART_ONE_STOP_BIT};
	UART_init(&UART_configPtr);

}

/*
 * [function Name] : APP_receivePassword
 * [Description] : This function is responsible for receiving password from Uc1.
 * [Args] :
 * [in] : uint8* password_entry
 * This argument shall indicate an array that is passed by reference which store the password in it.
 * This is argument will be modified to have a null character at the end.
 * [Returns] : None
 */
void APP_receivePassword(uint8* a_password_entry_Ptr)
{

#if 0

	/* Counter for the if 0 loop to check with it */
	uint8 j=0;
#endif

	/* Index */
	uint8 i=0;

	/* Flag to break out of loop */
	uint8 password_entry_finished=0;

	/* Holds the value received , every UART_receive byte get another byte so you can't call it to compare */
	uint8 received_byte=0;

	/* This part of code will make you take a byte and skip another, solution is to use received byte */
#if 0
	while (UART_recieveByte() != APP_END_OF_PASSWORD)
	{
		a_password_entry_Ptr[i] = UART_recieveByte();
	}
#endif

	while (password_entry_finished==0)
	{
		/* Hold the value of received byte */
		received_byte = UART_recieveByte();

		if (received_byte != APP_END_OF_PASSWORD)
		{
			a_password_entry_Ptr[i]= received_byte;

			/* To see at the Micro2 what we received */
			//			LCD_intgerToString(a_password_entry_Ptr[i]);
			i++;
		}
		else
		{
			/* Break out of loop */
			password_entry_finished=1;
		}
	}

	/* Put a null character at the end of password */
	a_password_entry_Ptr[i]='\0';

	/* This code is to ensure that a_password_entry_ptr have saved the password sent */
#if 0

	LCD_clearScreen();
	for (j=0;j<i;j++)
	{
		LCD_intgerToString(a_password_entry_Ptr[j]);
		_delay_ms(1000);
	}
	_delay_ms(10000);
	LCD_clearScreen();
	LCD_displayString("FINISHED");
	_delay_ms(3000);

#endif

}

void APP_checkIfFirstTimeEntry(void)
{
	/* For comparing */
	uint8 i=0;

	/* Holds the size of password*/
	uint8 size=0;
#if 0 /* To get the suitable delay between every EEPROM operation (10ms is not enough as we work 8Mhz not 1Mhz) */
	/* Saving Password status in password_check if it's valid */
	LCD_clearScreen();
	EEPROM_writeByte(EEPROM_PASSWORD_ADDRESS_FLAG,0x07);
	_delay_ms(EEPROM_DELAY);

	EEPROM_readByte(EEPROM_PASSWORD_ADDRESS_FLAG,&password_check);
	_delay_ms(EEPROM_DELAY);

	LCD_intgerToString(password_check);

#endif

	/* Assign the flag to password check as we can check on its value */
	EEPROM_readByte(EEPROM_PASSWORD_ADDRESS_FLAG,&password_check);
	_delay_ms(EEPROM_DELAY);

	/* Checking if there is any password saved in memory already */
	if (password_check != NOT_FIRST_TIME)
	{
		/* Taking password for the first time */
		UART_sendByte(ASK_FOR_NEW_PASSWORD);
	}

	/* Ask for existing password */
	else
	{
		/* Read the size of password & put in in local variable size */
		EEPROM_readByte(EEPROM_PASS_SIZE,&size);
		_delay_ms(EEPROM_DELAY);
		//
		//		LCD_clearScreen();
		//		LCD_intgerToString(size);

		/* Assign the address from memory to global variable g_eeprom_pass */
		do {
			EEPROM_readByte(EEPROM_PASSWORD_ADDRESS+i,&g_eeprom_pass[i]);
			_delay_ms(EEPROM_DELAY);
			//
			//			LCD_moveCursor(1,i);
			//			LCD_intgerToString(g_eeprom_pass[i]);
			i++;
			//		}while(g_eeprom_pass[i]!='\0');
		}while(i<=size);

		UART_sendByte(SHOW_MENU);
	}
}


void APP_comparePasswordsFirstTime(const uint8* a_first_pass_Ptr ,const uint8* a_second_pass_Ptr)
{
	/* Index */
	uint8 i=0;
	/* Holds the size of our password */
	uint8 size=0;

	//	LCD_clearScreen();
	/* Compare with the null character that we put at the end of password */
	for(i=0;(a_first_pass_Ptr[i]!='\0') || (a_second_pass_Ptr[i]!='\0') ;i++)
	{
#if 0 /* Test if the arrays hold the value of passwords */
		LCD_moveCursor(0,i);
		LCD_intgerToString(a_first_pass_Ptr[i]);
		LCD_moveCursor(1,i);
		LCD_intgerToString(a_second_pass_Ptr[i]);
		_delay_ms(2000);
#endif
		if (a_first_pass_Ptr[i]!=a_second_pass_Ptr[i]) /*Password doesn't match -> Send to microcontroller1 */
		{
			/* To skip the password matches loop */
			g_status = ERROR;

			/* break out of loop if password doesn't match */
			break;
		}
		else
		{
			/* Write password byte by byte in eeprom
			 *  We don't have to increment the address of eeprom as the hardware automatically do it
			 */
			EEPROM_writeByte(EEPROM_PASSWORD_ADDRESS+i,a_first_pass_Ptr[i]);
			_delay_ms(EEPROM_DELAY); /* Delay between every operation on EEPROM */
			size =i;
#if 0
			/* To test if the eeprom had the value correctly written in it */
			EEPROM_readByte(EEPROM_PASSWORD_ADDRESS+i,&g_eeprom_pass[i]);
			_delay_ms(EEPROM_DELAY); /* Delay between every operation on EEPROM */
			LCD_intgerToString(g_eeprom_pass[i]);
#endif
			g_status = SUCCESS;
		}

	}
	if (g_status == SUCCESS)
	{
		/* Save a place in memory that indicate that we have a password saved */
		EEPROM_writeByte(EEPROM_PASSWORD_ADDRESS_FLAG,NOT_FIRST_TIME);
		_delay_ms(EEPROM_DELAY); /* Delay between every operation on EEPROM */

		/* Saving the size of password in EEPROM */
		EEPROM_writeByte(EEPROM_PASS_SIZE,size);
		_delay_ms(EEPROM_DELAY); /* Delay between every operation on EEPROM */

		//		EEPROM_readByte(EEPROM_PASS_SIZE,&i);
		//		LCD_clearScreen();
		//		LCD_displayString("SIZE OF PASS");
		//		LCD_moveCursor(1,0);
		//		LCD_intgerToString(i);
		/* Send to Micro 1 that Password are matched */
		UART_sendByte(PASSWORDS_MATCHED);
		UART_sendByte(SHOW_MENU);
	}
	else
	{
		/* Send that password are unmatched */
		UART_sendByte(PASSWORDS_UNMATCHED_FIRST_TIME);
	}
}


/* [function Name] : APP_comparePassword
 * [Description] : This function is responsible for comparing between 2 new passwords from Uc1 and save if match
 * [Args] :
 * [in] : const uint8* first_pass, const uint8* second_pass
 * These argument shall indicate two arrays that is passed by reference to store the passwords in it
 * These arguments are Read-Only (constant data).
 * [Returns] : uint8 state
 * This argument shall have the result of compare.
 */
void APP_comparePasswords(const uint8* a_first_pass_Ptr)
{
	/* Index */
	uint8 i=0;

	/* Hold the size of password */
	uint8 size=0;

	/* Get the password size */
	EEPROM_readByte(EEPROM_PASS_SIZE,&size);
	_delay_ms(EEPROM_DELAY);

	do {
		EEPROM_readByte(EEPROM_PASSWORD_ADDRESS+i,&g_eeprom_pass[i]);
		_delay_ms(EEPROM_DELAY);

		//		LCD_moveCursor(1,i);
		//		LCD_intgerToString(eeprom_pass[i]);
		//		_delay_ms(200);

		i++;
	}while(i<=size);

	/* Compare with the null character that we put at the end of password */
	for (i=0;a_first_pass_Ptr[i]!='\0';i++)
	{
		if (a_first_pass_Ptr[i]!=g_eeprom_pass[i]) /*Password doesn't match -> Send to microcontroller1 */
		{
			/* Hold the unmatch status */
			g_status = ERROR;

			break;
		}
		else
		{
			g_status = SUCCESS;
		}
	}
	if (g_status != ERROR)
	{
		g_trial_times = 0;

		if (g_change ==0)
		{
			APP_doorProcessing();
		}
		else if (g_change ==1)
		{
			UART_sendByte(CHANGE_PASSWORD);
		}
	}

	else if (g_status == ERROR)
	{
		g_trial_times++;
		UART_sendByte(PASSWORDS_UNMATCHED);
		if (g_trial_times == MAX_TRIALS_ERROR)
		{

			UART_sendByte(PASSWORD_WRONG);

			BUZZER_ON();

			/* Delay for 60 seconds */
			APP_startTimer_6Sec();
			APP_Timer1DelayForBuzzerCheck();


			BUZZER_OFF();


			UART_sendByte(SHOW_MENU);
		}

		if (g_change == 0)
		{
			UART_sendByte(ASK_FOR_DOOR_PASSWORD);
		}
		else if (g_change==1)
		{
			UART_sendByte(ASK_FOR_CHANGING_PASSWORD);
		}

	}


}
void APP_mainMenuChecker (void)
{

	/* Holds the value received , every UART_receive byte get another byte so you can't call it to compare */
	uint8 received_byte=0;

	/* Hold the value of received byte */
	received_byte = UART_recieveByte();

	/* Based on user choice */
	switch (received_byte)
	{
	case '+' :

		//		LCD_clearScreen();
		//		LCD_displayCharacter(received_byte);

		UART_sendByte(ASK_FOR_DOOR_PASSWORD);

		break;

	case '-' :

		//		LCD_clearScreen();
		//
		//		LCD_displayCharacter(received_byte);

		UART_sendByte(ASK_FOR_CHANGING_PASSWORD);

		break;

		/* If the input is invalid, assign an error message to the variable sent to micro1 */
	default :

		//		LCD_clearScreen();
		//
		//		LCD_intgerToString(received_byte);

		UART_sendByte(INVALID_INPUT);
		UART_sendByte(SHOW_MENU);

		break;
	}


}
void APP_doorProcessing (void)
{
	DCMotor_Rotate(DC_MOTOR_CLOCKWISE);
	APP_startTimer_3Sec();

	UART_sendByte(DOOR_OPENING);
	//	LCD_clearScreen();
	//	LCD_displayString("CW");

	while (g_tick !=5);
	g_tick = 0;

	DCMotor_Rotate(DC_MOTOR_STOP);
	//	LCD_clearScreen();
	//	LCD_displayString("STOP");

	/* Delay for 3 second */
	while (g_tick !=1);
	g_tick = 0;


	DCMotor_Rotate(DC_MOTOR_ANTI_CLOCKWISE);
	//	UART_sendByte(DOOR_CLOSING);
	//	LCD_clearScreen();
	//	LCD_displayString("ACW");
	//	LCD_clearScreen();
	//	LCD_displayString("Door is Closing");

	/* Delay for 15 second */
	while (g_tick !=5);

	g_tick=0;
	DCMotor_Rotate(DC_MOTOR_STOP);
	TIMER_DeInit(TIMER1_ID);


	UART_sendByte(SHOW_MENU);

}
