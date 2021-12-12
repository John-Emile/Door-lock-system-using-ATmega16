/******************************************************************************
 *
 * File Name: motor.h
 *
 * Description: Header file for the DC Motor module.
 *
 * Author: John Emile
 *
 * Date : Oct 11, 2021
 *
 *******************************************************************************/
#ifndef MOTOR_H_
#define MOTOR_H_

#include "gpio.h" /*To use the ports & pins */

/*******************************************************************************
 * 								Definitions									   *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID				PORTB_ID
#define DC_MOTOR_FIRST_PIN_ID 			PIN4_ID
#define DC_MOTOR_SECOND_PIN_ID			PIN5_ID

/*******************************************************************************
 *                    		  	Enumerations                                   *
 *******************************************************************************/

/* Responsible for motor rotation or stoppage */
typedef enum
{
	DC_MOTOR_STOP , DC_MOTOR_CLOCKWISE , DC_MOTOR_ANTI_CLOCKWISE
}DcMotor_State;


/*******************************************************************************
 *							Functions prototypes 							   *
 *******************************************************************************/

/* Responsible for the initialization of the DC Motor. */
void DCMOTOR_init(void);

/* Responsible for the rotation of the DC Motor. */
void DCMotor_Rotate(DcMotor_State state); //,uint8 speed


#endif /* MOTOR_H_ */
