/******************************************************************************
 *
 * File Name: timer_delay.h
 *
 * Description: Header file for timer delay functions.
 *
 * Author: John Emile
 *
 * Date : NOV 5, 2021
 *
 *******************************************************************************/

#ifndef TIMER_DELAY_H_
#define TIMER_DELAY_H_

/*******************************************************************************
 *                    		  Functions Prototypes	                           *
 *******************************************************************************/

void setCallBackFunctionTimer1 (void);

/* The main idea for these functions is to minimize number of interrupts by setting different compare values
 * using the Formula Compare value = Number of seconds wanted * F_CPU/Pre-scaler
 */
void APP_startTimer_1Sec(void);
void APP_startTimer_3Sec(void);
void APP_startTimer_6Sec(void);

/* These functions is to check on the ticks */
void APP_Timer1DelayForScreenCheck(void);
void APP_Timer1DelayForBuzzerCheck(void);



#endif /* TIMER_DELAY_H_ */
