/******************************************************************************
 *
 * File Name: timer0.c
 *
 * Description: Source file for Timer0 AVR driver.
 *
 * Author: John Emile
 *
 * Date : Oct 28, 2021
 *
 *******************************************************************************/

#include "timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callbackTimer0Ptr)(void) = NULL_PTR;
static volatile void (*g_callbackTimer1Ptr)(void) = NULL_PTR;
static volatile void (*g_callbackTimer2Ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_callbackTimer0Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callbackTimer0Ptr)();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callbackTimer0Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callbackTimer0Ptr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callbackTimer1Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callbackTimer1Ptr)();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callbackTimer1Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callbackTimer1Ptr)();
	}
}
ISR(TIMER1_COMPB_vect)
{
	if(g_callbackTimer1Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callbackTimer1Ptr)();
	}
}
ISR(TIMER2_OVF_vect)
{
	if(g_callbackTimer2Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callbackTimer2Ptr)();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_callbackTimer2Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callbackTimer2Ptr)();
	}
}


void TIMER_init(const TIMER_ConfigType *Config_ptr)
{
	switch (Config_ptr->identification)
	{
	case TIMER0_ID :

		/* Load TCNT0 with initial value */
		TCNT0 = Config_ptr->initial_value;

		/* Insert the pre-scaler bits :
		 * &0xB7 to clear WGM00 (bit 6) & WGM01 (bit3)
		 * &0x01 to get WGM00 & <<6 to insert it
		 * &0x02 to get WGM01 & <<3 to insert it
		 */
		TCCR0 = (TCCR0 & 0xB7) | ((Config_ptr->mode & 0x01)<<6) | ((Config_ptr->mode & 0x02)<<3);

		/* Insert the clock bits :
		 * &0xF8 to clear CS00 (bit 0) & CS01 (bit 1) & CS02 (bit 2)
		 */
		TCCR0 = (TCCR0 & 0xF8) | (Config_ptr->prescaler);

		switch ((Config_ptr->mode))
		{

		case TIMER02_MODE_COMPARE :
			/* Load OCR0 with compare value if compare mode is on */
			OCR0 = Config_ptr->compare_value;

			/* Clear OCIE0 & TOIE0 (bit 0 & 1) & Enable Timer0 COMPARE Interrupt (OCIE0) */
			TIMSK = (TIMSK & 0xFC) | (1<<OCIE0);

			/* FOC0 bit is only active when the WGM00 bit specifies a non-PWM mode */
			TCCR0 = (TCCR0 & 0x7F) | (1<<FOC0);

			break;

		case TIMER02_MODE_NORMAL :
			/* Clear OCIE0 & TOIE0 & Enable Timer0 NORMAL Interrupt (TOIE0) */
			TIMSK = (TIMSK & 0xFC) | (1<<TOIE0);

			/* FOC0 bit is only active when the WGM00 bit specifies a non-PWM mode */
			TCCR0 = (TCCR0 & 0x7F) | (1<<FOC0);

			break;
		case TIMER02_MODE_FAST_PWM :
			/* FOC0 bit is only active when the WGM00 bit specifies a non-PWM mode */
			TCCR0 &= ~(1<<FOC0);

			/* PWM Configuration at main application */
			break;

		}
		break;

		case TIMER1_ID :
			/* Load TCNT1 with initial value */
			TCNT1 = Config_ptr->initial_value;

			/* Insert the pre-scaler bits in TCCR1A :
			 * &0xFC to clear WGM10 (bit 0) & WGM11 (bit1)
			 * &0x03 to get WGM10 & WGM11
			 */
			TCCR1A = (TCCR1A & 0xFC) | ( (Config_ptr->mode) & 0x03);

			/* Insert the pre-scaler bits in TCCR1B :
			 * &0xE7 to clear WGM12 (bit 3) & WGM13 (bit4)
			 * &0x0C to get WGM12 (bit 3) & WGM13 (bit 4) & << 1 to insert it.
			 */
			TCCR1B = (TCCR1B & 0xE7 ) | ((((Config_ptr->mode)&0x0C)<<1)) ;

			/* Insert the clock bits :
			 * &0xF8 to clear CS10 (bit 0) & CS11 (bit 1) & CS12 (bit 2)
			 */
			TCCR1B = (TCCR1B & 0xF8) | (Config_ptr->prescaler);



			switch ((Config_ptr->mode))
			{

			case TIMER1_MODE_COMPARE_OCR1A :

				/* Clear TICIE1 & TOIE1 & OCIE1B & OCIE1A (bit 2 & 3 & 5 & 6 ) & Enable Timer1 COMPARE A match Interrupt (OCIE1A) */
				TIMSK = (TIMSK & 0xC3) | (1<<OCIE1A);

				/* FOC1A bit is only active when the WGM13:10 bits specifies a non-PWM mode */
				TCCR1A = (TCCR1A & 0xF7) | (1<<FOC1A);

				/* Load OCR1A with compare value if compare mode is on */
				OCR1A = Config_ptr->compare_value;

				break;

			case TIMER1_MODE_NORMAL :
				/* Clear TICIE1 & TOIE1 & OCIE1B & OCIE1A (bit 2 & 3 & 5 & 6 ) & Enable Timer1 Normal(overflow) Interrupt (TOIE1) */
				TIMSK = (TIMSK & 0x03) | (1<<TOIE1);

				/* FOC0 bit is only active when the WGM13:10 bits specifies a non-PWM mode */
				TCCR1A = (TCCR0 & 0xF7) | (1<<FOC1A);

				break;
			case TIMER1_MODE_FAST_PWM_OCR1A :
				/* FOC1A & FOC1B bit is only active when the WGM01:00 bits specifies a non-PWM mode */
				TCCR1A &= ~(1<<FOC1A) & ~(1<<FOC1B);

				/* PWM Configuration at main application */
				break;

			}
			break;

			case TIMER2_ID :

				/* Load TCNT0 with initial value */
				TCNT2 = Config_ptr->initial_value;

				/* Insert the pre-scaler bits :
				 * &0xB7 to clear WGM20 (bit 6) & WGM21 (bit3)
				 * &0x01 to get WGM20 & <<6 to insert it
				 * &0x02 to get WGM21 & <<3 to insert it
				 */
				TCCR2 = (TCCR0 & 0xB7) | ((Config_ptr->mode & 0x01)<<6) | ((Config_ptr->mode & 0x02)<<3);

				/* Insert the clock bits :
				 * &0xF8 to clear CS20 (bit 0) & CS21 (bit 1) & CS22 (bit 2)
				 */
				TCCR2 = (TCCR0 & 0xF8) | (Config_ptr->prescaler);

				switch ((Config_ptr->mode))
				{

				case TIMER02_MODE_COMPARE :

					/* Load OCR0 with compare value if compare mode is on */
					OCR2 = Config_ptr->compare_value;

					/* Clear OCIE0 & TOIE0 (bit 0 & 1) & Enable Timer0 COMPARE Interrupt (OCIE0) */
					TIMSK = (TIMSK & 0x3F) | (1<<OCIE2);

					/* FOC0 bit is only active when the WGM13:10 bits specifies a non-PWM mode */
					TCCR2 = (TCCR2 & 0x7F) | (1<<FOC2);

					break;


				case TIMER02_MODE_NORMAL :

					/* Clear OCIE2 & TOIE2 & Enable Timer2 NORMAL Interrupt (TOIE2) */
					TIMSK = (TIMSK & 0x3F) | (1<<TOIE2);

					/* FOC2 bit is only active when the WGM00 bit specifies a non-PWM mode */
					TCCR2 = (TCCR2 & 0x7F) | (1<<FOC2);

					break;

				case TIMER02_MODE_FAST_PWM :

					/* FOC2 bit is only active when the WGM21:20 bits specifies a non-PWM mode */
					TCCR2 &= ~(1<<FOC2);

					/* PWM Configuration at main application */
					break;
				}
				break;
	}
}

void TIMER0_setCallback (void(*a_ptr)(void))
{
	g_callbackTimer0Ptr = a_ptr;
}

void TIMER1_setCallback (void(*a_ptr)(void))
{
	g_callbackTimer1Ptr = a_ptr;
}

void TIMER2_setCallback (void(*a_ptr)(void))
{
	g_callbackTimer2Ptr = a_ptr;
}

void TIMER_DeInit (uint8 TIMER_DeInit_ID)
{
	switch (TIMER_DeInit_ID)
	{

	case TIMER0_ID :

		/* Clear Timer values */
		TCNT0 = 0;
		TCCR0 = 0;
		OCR0 = 0;

		/* Disable Interrupts */
		TIMSK &= ~(1<<TOIE0) & ~(1<<OCIE0);
		break;

	case TIMER1_ID :

		/* Clear Timer values */
		TCNT1 = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		OCR1A = 0;
		OCR1B = 0;

		/* Disable Interrupts */
		TIMSK &= ~(1<<TOIE1) & ~(1<<OCIE1A) & ~(1<<OCIE1B);
		break;

	case TIMER2_ID :

		/* Clear Timer values */
		TCNT2 = 0;
		TCCR2 = 0;
		OCR2 = 0;

		/* Disable Interrupts */
		TIMSK &= ~(1<<TOIE2) & ~(1<<OCIE2);

	}
}
