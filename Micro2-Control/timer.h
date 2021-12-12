/******************************************************************************
 *
 * File Name: timer0.h
 *
 * Description: Header file for Timer0 AVR driver.
 *
 * Author: John Emile
 *
 * Date : Oct 28, 2021
 *
 *******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/* Enum to choose Timer ID */
typedef enum {
	TIMER0_ID,TIMER1_ID,TIMER2_ID
}TIMER_ID;

/* Enum to choose timer mode */
typedef enum {
	TIMER02_MODE_NORMAL=0,TIMER02_MODE_PWM_PHASE_CORRECT=1,TIMER02_MODE_COMPARE=2,TIMER02_MODE_FAST_PWM=3,
	TIMER1_MODE_NORMAL=0,TIMER1_MODE_PWM_PHASE_CORRECT=1,TIMER1_MODE_COMPARE_OCR1A=4,TIMER1_MODE_COMPARE_ICR1=12,
	TIMER1_MODE_FAST_PWM_ICR1=14,TIMER1_MODE_FAST_PWM_OCR1A=15
}TIMER_Waveform_Mode;

/* Enum to set the clock of timer */
typedef enum {
	TIMER_CLOCK_DISABLE,TIMER_CLOCK_CPU,TIMER_CLOCK_CPU_8,TIMER_CLOCK_CPU_64,TIMER_CLOCK_CPU_256,TIMER_CLOCK_CPU_1024,
	TIMER_CLOCK_CPU_EXTERNAL_FALLING_EDGE,TIMER_CLOCK_CPU_EXTERNAL_RISING_EDGE
}TIMER_PRESCALER;

typedef struct {
	TIMER_ID identification;
	TIMER_Waveform_Mode mode;
	uint16 initial_value; /*16 for timer 1 also */
	uint16 compare_value; /* 16 for timer 1 also */
	TIMER_PRESCALER prescaler;
}TIMER_ConfigType;


void TIMER_init(const TIMER_ConfigType *Config_ptr);
void TIMER0_setCallback (void(*a_ptr)(void));
void TIMER1_setCallback (void(*a_ptr)(void));
void TIMER2_setCallback (void(*a_ptr)(void));
void TIMER_DeInit (uint8 TIMER_DeInit_ID);




#endif /* TIMER_H_ */
