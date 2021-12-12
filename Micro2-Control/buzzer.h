/*
 * buzzer.h
 *
 *  Created on: Nov 4, 2021
 *      Author: John
 */

#include "gpio.h"

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_PORT_ID          PORTC_ID
#define BUZZER_PIN_ID 			PIN7_ID

void BUZZER_init(void);
void BUZZER_OFF(void);
void BUZZER_ON(void);



#endif /* BUZZER_H_ */
