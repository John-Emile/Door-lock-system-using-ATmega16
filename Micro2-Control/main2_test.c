/******************************************************************************
 *
 * File Name: main1.c
 *
 * Description: 
 *
 * Author: John Emile
 *
 * Date : Nov 2, 2021
 *
 *******************************************************************************/

#include "application_micro2.h"

#define F_CPU 8000000UL
/************************************************************************
 *                           Global variables                           *
 ************************************************************************/

/* To hold the value of passwords coming from uc1 */
uint8 g_first_password[10];
uint8 g_second_password[10];
uint8 counter1 = 0;
uint8 counter2 = 0;

int main(void)
{
	/* To hold the value sent by micro1 */
	uint8 received_byte = 0;

	/* Modules initialization */
	MICROCONTROLLER2_init();

	/* Enable Global Interrupt */
	SREG |= (1<<7);

	/* Send MC2_READY byte to MC1 */
	UART_sendByte(MICRO2_READY);

	/* Wait until MC1 is ready to initialize communication */
	while(UART_recieveByte() != MICRO1_READY);

	APP_checkIfFirstTimeEntry();

	for (;;)
	{

		received_byte = UART_recieveByte();

		switch(received_byte)
		{

		/* The following two cases are only used once */
		case PASSWORD_UNCHECKED_FIRST_TIME :

			/* Wait until Mc1 finish sending the password */
			APP_receivePassword(g_first_password);

			break;

		case SECOND_PASSWORD_UNCHECKED_FIRST_TIME :

			/* Wait until Mc1 finish sending the password */
			APP_receivePassword(g_second_password);

#if 0
			/* Hold the value of received byte */
			uint8 i=0;
			LCD_clearScreen();
			while (g_first_password[i]!= '\0')
			{
				LCD_moveCursor(0,i);
				LCD_intgerToString(g_first_password[i]);
				LCD_moveCursor(1,i);
				LCD_intgerToString(g_second_password[i]);
				_delay_ms(2000);
				i++;
			}
#endif
			APP_comparePasswordsFirstTime(g_first_password,g_second_password);
			break;

		case PASSWORD_UNCHECKED_FOR_DOOR :

			g_change=0;
			APP_receivePassword(g_first_password);
			APP_comparePasswords(g_first_password);
			break;

		case PASSWORD_UNCHECKED_FOR_CHANGE:

			g_change=1;
			APP_receivePassword(g_first_password);
			APP_comparePasswords(g_first_password);
			break;

			/* Regular compare with eeprom */
		case  PASSWORD_UNCHECKED_LOGIN :

			/* Wait until Mc1 finish sending the password */
			APP_receivePassword(g_first_password);

			//APP_setEEPROMCompare();

			APP_comparePasswords(g_first_password);

			break;

		case APP_mainMenuCheck :

			APP_mainMenuChecker();
			break;
		}
	}

}
