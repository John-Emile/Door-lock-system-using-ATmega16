/******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for the External EEPROM Memory
 *
 * Author: John Emile
 *
 * Date : 24/10/2021
 *******************************************************************************/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"
#define F_CPU 8000000UL
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/* The following section for delays between eeprom operations */
#if (F_CPU==1000000)
#define EEPROM_DELAY 10		/* For 1Mhz*/
#endif

#if (F_CPU==8000000)
#define EEPROM_DELAY 80    /* For 8Mhz*/
#endif
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 address,uint8 data);
uint8 EEPROM_readByte(uint16 address,uint8 *data);
void EEPROM_init(void);
#endif /* EXTERNAL_EEPROM_H_ */
