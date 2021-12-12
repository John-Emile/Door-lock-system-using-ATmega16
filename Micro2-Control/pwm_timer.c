/******************************************************************************
 *
 * File Name: timer0_pwm.c
 *
 * Description: Source file for AVR Timer0 PWM mode.
 *
 * Author: John Emile
 *
 * Date : Oct 10, 2021
 *
 *******************************************************************************/

#include <avr/io.h> /* To use timer0 registers */
#include "gpio.h" /* To use GPIO driver */
#include "pwm_timer.h"

/*******************************************************************************
 *                    		  Functions definitions                            *
 *******************************************************************************/


void PWM_Timer_start(const PWM_ConfigType *Config_Ptr)
{

	switch (Config_Ptr->identification)
	{
	case TIMER0_ID :

		/* Configure PB3/OC0 as output pin -> pin where the PWM signal is generated from MC */
		GPIO_setupPinDirection(PORTB_ID,PIN3,PIN_OUTPUT);

		/* Insert PWM Waveform mode
		 * &0xCF to clear COM01 (bit 5) & COM00 (bit 4)
		 * <<4 to insert them in COM01 & COM00
		 */
		TCCR0 = (TCCR0 & 0xCF) | ((Config_Ptr->mode)<<4);


		/* F_CPU = 8Mhz , F_PWM = 200-700 -> using F_PWM = F_CPU/N*256 -> N(pre-scaler)= 64 */
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->prescaler);

		/* Set value for the compare */
		OCR0 = Config_Ptr->duty_cycle;

		break;

	case TIMER1_ID :

		/* Configure PD5/OC1A as output pin -> pin where the PWM signal is generated from MC */
		GPIO_setupPinDirection(PORTD_ID,PIN5,PIN_OUTPUT);

		/* Insert PWM Waveform mode
		 * &0x3F to clear COM1A1 (bit 7) & COM1A0 (bit 6)
		 * <<6 to insert them in COM1A1 & COM1A0
		 */
		TCCR1A = (TCCR1A & 0x3F) | ((Config_Ptr->mode)<<6);

		/* F_CPU = 8Mhz , F_PWM = 200-700 -> using F_PWM = F_CPU/N*(1+TOP) -> N(pre-scaler)= 64 , You choose the top value */
		TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler);

		/* Choose top value using TOP = (F_CPU/N*F_PWM)-1 */
		OCR1A = Config_Ptr->duty_cycle;

		break;


		break;
	case TIMER2_ID :

		/* Configure PD7/OC2 as output pin -> pin where the PWM signal is generated from MC */
		GPIO_setupPinDirection(PORTD_ID,PIN7,PIN_OUTPUT);

		/* Insert PWM Waveform mode
		 * &0xCF to clear COM21 (bit 5) & COM20 (bit 4)
		 * <<4 to insert them in COM21 & COM20
		 */
		TCCR2 = (TCCR2 & 0xCF) | ((Config_Ptr->mode)<<4);

		/* F_CPU = 8Mhz , F_PWM = 200-700 -> using F_PWM = F_CPU/N*256 -> N(pre-scaler)= 64 */
		TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->prescaler);

		/* Set value for the compare */
		OCR2 = Config_Ptr->duty_cycle;

		break;
	}
}
