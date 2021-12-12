/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.c
 *
 * Description: Source file for the TWI(I2C) AVR driver.
 *
 * Author: John Emile
 *
 * Date : 23/10/2021
 *******************************************************************************/

#include "common_macros.h"
#include <avr/io.h>

#include "twi.h"

void TWI_init(const TWI_ConfigType *Config_ptr)
{
	/* enable TWI */
	TWCR = (1<<TWEN);

	/* Insert the address while preserving the TWGCE bit (bit 0) *
	 * I2C has only 128 address.
	 */
	if ((Config_ptr->address)<128) {
		TWAR = (TWAR & 0x01) | ((Config_ptr->address)<<1);
	}
	/*
	 * Insert the pre-scaler, the other bits are Read only so equal operation doesn't
	 * affect them, what affect them if we wrote in a specific bit
	 */
	TWSR = (Config_ptr->prescaler);

	/* Calculate the value of TWBR using the equation in the datasheet */
	TWBR = (((F_CPU/(Config_ptr->sclFrequency))- 16)/(2*(4^(Config_ptr->prescaler))));

}

void TWI_start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1 to read it after the data is sent.
	 * send the start bit by TWSTA=1
	 * In order not to disable TWI by = , We enable it manually every step.
	 */

	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}
