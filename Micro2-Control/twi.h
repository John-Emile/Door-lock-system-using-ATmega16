 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.h
 *
 * Description: Header file for the TWI(I2C) AVR driver.
 *
 * Author: John Emile
 *
 * Date : 23/10/2021
 *******************************************************************************/

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         					 0x08 /* start has been sent */
#define TWI_REP_START     					 0x10 /* repeated start */
#define TWI_MASTER_TRANSMIT_SLAVE_WRITE_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MASTER_TRANSMIT_SLAVE_READ_ACK   0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MASTER_TRANSMIT_DATA_ACK         0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MASTER_READ_DATA_ACK             0x50 /* Master received data and send ACK to slave. */
#define TWI_MASTER_READ_DATA_NACK  			 0x58 /* Master received data but doesn't send ACK to slave. */


/*******************************************************************************
 *                    		  	Enumerations                                   *
 *******************************************************************************/
typedef enum {
	I2C_PRESCALER_1, I2C_PRESCALER_4 , I2C_PRESCALER_16 , I2C_PRESCALER_64
}TWI_Prescaler;

/* Enum to hold the value of SCL frequency */
typedef enum {
I2C_DATA_TRANSFER_100_KBS=(100000UL),I2C_DATA_TRANSFER_400_KBS=(400000UL),
I2C_DATA_TRANSFER_1_MBS=(1000000UL),I2C_DATA_TRANSFER_3_point_4_MBS=(3400000UL)
}TWI_DataTransfer;
/*******************************************************************************
 *                    		    	Structures                                 *
 *******************************************************************************/

/* Struct that will control the dynamic configuration */
typedef struct{
	TWI_Prescaler prescaler;
	uint8 address;
	TWI_DataTransfer sclFrequency;
}TWI_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(const TWI_ConfigType *Config_ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
