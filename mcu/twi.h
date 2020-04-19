/*
 * twi.h
 *
 * Created: 7/3/2014 8:50:18 PM
 *  Author: eric
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <stdint.h>
#include "../config.h"

/* Define the twi timeout */
#define TWI_TIMEOUT					0xFFFF

/* Macros to Define TWI Bit Rate which is set in TWBR */
#define TWI_SPEED					100000UL /* 100KHz */
#define TWI_BIT_RATE				((F_CPU/TWI_SPEED)-16)/2
#define TWI_PRESCALER				0x00

#define TW_START					0xA4 /* Send start condition */
#define TW_READY					(TWCR & 0x80) /* Ready when TWINT returns 1 */
#define TWI_START					(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define TWI_STOP					(1<<TWINT)|(1<<TWSTO)|(1<<TWEN)

/* I2C Status codes in TWSR register */
/* Master Transmitter/Receiver status codes in TWSR */
#define TW_STATUS					(TWSR & 0xF8) /* Returns value of status register */
#define START_TRANSMITTED			0x08 /* Start condition transmitted */
#define REPEATED_START				0X10 /* Repeated start condition transmitted */
#define SLA_W_TX_ACK				0X18 /* SLA+W transmitted & ACK received */
#define SLA_W_TX_NACK				0X20 /* SLA+W transmitted & NACK received */
#define DATA_TX_ACK					0X28 /* Data byte transmitted & ACK received */
#define DATA_TX_NACK				0X30 /* Data byte transmitted & NACK received */
#define ARBITRATION_LOST_SLA_W		0x38 /* Arbitration lost in SLA+W or data bytes */
#define SLA_R_TX_ACK				0x40 /* SLA+R transmitted & ACK received */
#define SLA_R_TX_NACK				0x48 /* SLA+R transmitted & NACK received */
#define DATA_RX_ACK					0x50 /* Data byte received & ACK returned */
#define DATA_RX_NACK				0x58 /* Data byte received & NACK returned */

/* Function Protoypes */

void twi_init();
/*****************************************************************
DESCRIPTION: Set the TWI slave-clock frequency and pre-scaler

PARAMETERS: None

RETURN: None
******************************************************************/

void twi_start();
/*****************************************************************
DESCRIPTION: AVR MCU (TWI Master) sends start condition and expects 
			 a status code of 0x08 to be returned.
			 
PARAMETERS:None

RETURN: None
******************************************************************/

void twi_stop();
/*****************************************************************
DESCRIPTION: AVR MCU (TWI Master) sends stop condition

PARAMETERS: None

RETURN: None
******************************************************************/

void twi_write_addr(uint8_t u8address);
/*****************************************************************
DESCRIPTION: Write the 8-bit slave address to initiate communication

PARAMETERS: unsigned int (1-byte unsigned)

RETURN: None
******************************************************************/

void twi_write(uint8_t u8data);
/*****************************************************************
DESCRIPTION: Write a single byte of data into the two-wire data 
			 register (TWDR)

PARAMETERS: unsigned int (1-byte unsigned)

RETURN: None
******************************************************************/

uint8_t twi_get_status();
/*****************************************************************
DESCRIPTION: Returns the status code after a TWI action

PARAMETERS: None

RETURN: unsigned int (1-byte unsigned)
******************************************************************/

uint8_t twi_read_ack();
/*****************************************************************
DESCRIPTION: Receive a single byte of data from the slave device 
			 stored in the TWDR register along with an 
			 acknowledge bit.

PARAMETERS: None

RETURN: unsigned int (1-byte unsigned)
******************************************************************/

uint8_t twi_read_nack();
/*****************************************************************
DESCRIPTION: Receive a single byte of data from the slave device 
			 stored in the TWDR register along with a 
			 not-acknowledge bit.

PARAMETERS: None

RETURN: unsigned int (1-byte unsigned)
******************************************************************/

uint8_t twi_detect_device(uint8_t addr);
/*****************************************************************
DESCRIPTION: Look for device at specified address; 
			 return 1=found, 0=not found.

PARAMETERS: unsigned int (1-byte unsigned)

RETURN: unsigned int (1-byte unsigned)
******************************************************************/

uint8_t twi_find_devices(uint8_t start);
/*****************************************************************
DESCRIPTION: Find devices on TWI(I2C) Bus.

PARAMETERS: unsigned int (1-byte unsigned)

RETURN: unsigned int (1-byte unsigned)
******************************************************************/

uint8_t twi_timeout(uint16_t timeout);

#endif /* TWI_H_ */