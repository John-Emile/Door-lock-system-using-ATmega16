/******************************************************************************
 *
 * File Name: timer0_pwm.h
 *
 * Description: Header file for AVR Timer0 PWM mode.
 *
 * Author: John Emile
 *
 * Date : Oct 10, 2021
 *
 *******************************************************************************/


#ifndef PWM_TIMER_H_
#define PWM_TIMER_H_

#include "std_types.h"
#include "timer.h"


/* Enum to choose PWM mode */
typedef enum {
	PWM_MODE_NORMAL,PWM_MODE_RESERVED,PWM_MODE_NON_INVERTING,PWM_MODE_INVERTING
}PWM_Waveform_Mode;

/* Enum to choose PWM prescaler */
typedef enum {
	PWM_CLOCK_DISABLE,PWM_CLOCK_CPU,PWM_CLOCK_CPU_8,PWM_CLOCK_CPU_64,PWM_CLOCK_CPU_256,PWM_CLOCK_CPU_1024,
	PWM_CLOCK_CPU_EXTERNAL_FALLING_EDGE,PWM_CLOCK_CPU_EXTERNAL_RISING_EDGE
}PWM_PRESCALER;

typedef struct {
	TIMER_ID identification;
	PWM_Waveform_Mode mode;
	PWM_PRESCALER prescaler;
	uint16 duty_cycle;
}PWM_ConfigType;

/*******************************************************************************
 *                    		  Functions Prototypes                             *
 *******************************************************************************/

void PWM_Timer_start(const PWM_ConfigType *Config_Ptr);


#endif /* PWM_TIMER_H_ */
