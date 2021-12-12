/******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: John Emile
 *
 * Date : 24/10/2021
 *******************************************************************************/

#include "twi.h"
#include "external_eeprom.h"

void EEPROM_init(void)
{
	/* Initialize the TWI/I2C Driver for interfacing with EEPROM */
	/* F_CPU Must be > 8*TWI Frequency because registers can't hold any negative numbers */
	/* I.E F_CPU = 8Mhz, we can't use any frequency above 8Mhz/8= 1MHz, max is smaller than 1Mhz */
	TWI_ConfigType configuration = {I2C_PRESCALER_1,1,I2C_DATA_TRANSFER_400_KBS};
	TWI_init(&configuration);
}
uint8 EEPROM_writeByte(uint16 address, uint8 data)
{
	/* Phase 1 : Send the start bit */
	TWI_start();

	/* Phase 2 : Send the device address, write request and receive ack from the receiver *

	 * /
	 * Send the device address, we need A10,A9,A8 address bit from the memory location
	 * Write the location address first
	 * & 0xA0 to write the 24C16 constant (0b1010)
	 * address & 0x0700 to get the MSB 3 bits of eeprom 11 bit address
	 * >>7 to move them to bit 3,2,1 (bit 0 is for read)
	 */
	TWI_writeByte((uint8)((0xA0) | ((address & 0x0700)>>7)));

	/* Check if the address have been sent correctly and if the slave ack the write request */
	if (TWI_getStatus() != TWI_MASTER_TRANSMIT_SLAVE_WRITE_ACK)
	{
		return ERROR;
	}


	/* Phase 3 : Send the location address to the receiver
	 * No need to ask for the write request as it's has been requested in phase 2 */

	/* Send the required memory location address of eeprom (0-2047) */
	TWI_writeByte((uint8)address); /* A7 to A0 */

	/* Check if byte have been written correctly */
	if (TWI_getStatus() != TWI_MASTER_TRANSMIT_DATA_ACK)
	{
		return ERROR;
	}

	/* Phase 4 : send the data */
	TWI_writeByte(data);

	/* Check if byte have been written correctly */
	if (TWI_getStatus() != TWI_MASTER_TRANSMIT_DATA_ACK)
	{
		return ERROR;
	}

	/* Phase 5 : Stop the TWI*/
	TWI_stop();

	return SUCCESS;

}

/* read from memory using pointer to facilitate the movement of pointer */
uint8 EEPROM_readByte(uint16 address, uint8 *data)
{

	/* Phase 1 : Start the TWI */
	TWI_start();

	/* Phase 2 : Send the device address, write request and receive ack from the receiver */
	TWI_writeByte((uint8)(0xA0) | ((address&0x0700)>>7));

	/* Check if the address have been sent correctly and if the slave ack the write request */
	if (TWI_getStatus() != TWI_MASTER_TRANSMIT_SLAVE_WRITE_ACK)
	{
		return ERROR;
	}

	/* Phase 3 : send the location address (word address), the rest of bits (A10,A9,A8) will
	 * be sent among the slave address in phase 2
	 */
	TWI_writeByte((uint8)address);

	/* Check if byte have been written correctly */
	if (TWI_getStatus() != TWI_MASTER_TRANSMIT_DATA_ACK)
	{
		return ERROR;
	}

	/* Phase 4 : Send a repeated start to begin reading from the eeprom */
	TWI_start();

	/* Check if repeated start is send */
	if (TWI_getStatus() != TWI_REP_START)
	{
		return ERROR;
	}

	/* Phase 5 : Send the device address again but with Read request and return with ack*/
	/* |1 to enable the read */
	TWI_writeByte((uint8)(0xA0)|(((address&0x0700)<<7)|1));

	if (TWI_getStatus() != TWI_MASTER_TRANSMIT_SLAVE_READ_ACK)
	{
		return ERROR;
	}

	/* Phase 6 : Read the byte from memory without send Ack to end communication */
	*data = TWI_readByteWithNACK();

	if (TWI_getStatus() != TWI_MASTER_READ_DATA_NACK)
	{
		return ERROR;
	}

	/* Send the Stop Bit */
	TWI_stop();

	return SUCCESS;

}
