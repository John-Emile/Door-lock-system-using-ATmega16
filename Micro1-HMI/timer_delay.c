/******************************************************************************
 *
 * File Name: timer_delay.c
 *
 * Description: Source file for timer delay functions.
 *
 * Author: John Emile
 *
 * Date : NOV 5, 2021
 *
 *******************************************************************************/
#include "timer_delay.h"
#include "timer.h"

/*******************************************************************************
 *                    		Global Variables                                   *
 *******************************************************************************/
/* For timer setcallback */
uint8 g_tick;

/*******************************************************************************
 *                    		  Function Declarations                            *
 *******************************************************************************/
void setCallBackFunctionTimer1 (void)
{
	g_tick++;
}

void APP_startTimer_1Sec(void)
{
	/* Timer delay Configurations for 1 Second delay:
	 * Timer 1, 1024 Pre-scalar
	 * OCR1A = Number of seconds wanted per interrupt*F_CPU/Prescalar = 1*8Mhz/1024 = 7812.5
	 * Generates interrupt every 1 second
	 */

	g_tick=0;

	TIMER1_setCallback(setCallBackFunctionTimer1);
	//	g_flag = TIMER_LCD_SCREEN_DELAY_ID;

	TIMER_ConfigType configuration1 = {TIMER1_ID,TIMER1_MODE_COMPARE_OCR1A,0,7812,TIMER_CLOCK_CPU_1024};
	TIMER_init(&configuration1);
}
void APP_startTimer_3Sec(void)
{

	/* Timer delay Configurations for 3 seconds delay:
	 * Timer 1, 1024 Pre-scalar , Comparing mode with top value of 1024 (1 sec).
	 * OCR1A = Number of seconds wanted per interrupt*F_CPU/Prescalar = 3*8Mhz/1024 = 23437.5
	 * Generates interrupt every 5 second
	 */

	g_tick=0;

	TIMER1_setCallback(setCallBackFunctionTimer1);
	//		g_flag = TIMER_MOTOR_MOVE_SCREEN_DELAY_ID;

	TIMER_ConfigType configuration1 = {TIMER1_ID,TIMER1_MODE_COMPARE_OCR1A,0,23437,TIMER_CLOCK_CPU_1024};
	TIMER_init(&configuration1);
}

void APP_startTimer_6Sec(void)
{
	/* Timer delay Configurations for 6 Second delay:
	 * Timer 1, 1024 Pre-scalar
	 * OCR1A = Number of seconds wanted per interrupt*F_CPU/Prescalar = 6*8Mhz/1024 = 46875
	 * Generates interrupt every 6 seconds
	 */
	g_tick=0;

	TIMER1_setCallback(setCallBackFunctionTimer1);
	//	g_flag = TIMER_BUZZER_DELAY_ID;

	TIMER_ConfigType configuration1 = {TIMER1_ID,TIMER1_MODE_COMPARE_OCR1A,0,46875,TIMER_CLOCK_CPU_1024};
	TIMER_init(&configuration1);
}

void APP_Timer1DelayForScreenCheck(void)
{
	while (g_tick !=1);
	g_tick=0;
	TIMER_DeInit(TIMER1_ID);

}
void APP_Timer1DelayForBuzzerCheck(void)
{
	/* Must call APP_startTimer_6Sec before to identify g_tick every 6 sec */
	/* Delay for 60 second */
	while (g_tick !=10);
	g_tick = 0;
	TIMER_DeInit(TIMER1_ID);

}




