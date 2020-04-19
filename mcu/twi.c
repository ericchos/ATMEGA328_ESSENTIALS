/*
 * twi.c
 *
 * Created: 7/3/2014 8:50:05 PM
 *  Author: eric
 
   ATmega328 I2C functions
   
   TWBR: Selects the division factor for the bit rate generator.
   
   TWCR: Control register. Controls the operation of the TWI/I2C.
   [TWINT|TWEA|TWSTA|TWSTO|TWWC|TWEN|----|TWIE]
   TWINT - Interrupt flag
   TWEA - Enable acknowledge bit
   TWSTA - Start condition bit
   TWSTO - Stop condition bit
   TWWC - Write collision flag
   TWEN - Enable bit. Enables TWI operation
   TWIE - Interrupt enable bit
   TWSR: TWI Status Register
   [TWS
   
   TWDR: Data register which contains the next byte to be transmitted or received
   
   TWAR: Slave address register
 */ 
#include "../config.h"
#include "twi.h"

#include <avr/io.h>
#include <util/delay.h>

/*****************************************************************
Set the TWI slave-clock frequency and prescaler
******************************************************************/
void twi_init()
{
	/* The SCL Frequency is set by:
		SCL Freq = F_CPU/(16+(2*TWBR*(4^TWPS))) */
	TWSR = TWI_PRESCALER; /* Don't need additional prescalers so set to 0x00 */
	TWBR = TWI_BIT_RATE; /* Sets SCL Frequency */
  
	/* Enable TWI(I2C) */
	TWCR = (1<<TWEN);
}

/*****************************************************************
AVR MCU (TWI Master) sends start condition and expects a status 
code of 0x08 to be returned.
******************************************************************/
void twi_start()
{
	volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
	
	/* Generates START signal */
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  
	/* Wait until START condition is transmitted */
	while(!(TWCR & (1<<TWINT)) && timeOut > 0)
		timeOut--;
}

/*****************************************************************
AVR MCU (TWI Master) sends stop condition
******************************************************************/
void twi_stop()
{
	volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
	
	// Generates STOP signal
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
  
	// Wait for STOP signal to transmit
	while(!(TWCR & (1<<TWSTO)) && timeOut > 0)
		timeOut--;
}

/*****************************************************************
Write the 8-bit slave address to initiate communication
******************************************************************/
void twi_write_addr(uint8_t u8address)
{  
	volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
	
	// Load I2C slave address into TWDR
	TWDR = u8address;	
  
	// Initiate send
	TWCR = (1<<TWINT)|(1<<TWEN);
  
	// Wait for command to go through
	while(!(TWCR & (1<<TWINT)) && timeOut > 0)
		timeOut--;
}

/*****************************************************************
Write a single byte of data into the two-wire data register (TWDR)
******************************************************************/
void twi_write(uint8_t u8data)
{
	volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
	
	// Write data into data register
	TWDR = u8data;
  
	// Clear TWI interrupt flag & enable TWI
	TWCR = (1<<TWINT)|(1<<TWEN);
  
	// Wait for transmission to complete
	while(!(TWCR & (1<<TWINT)) && timeOut > 0)
		timeOut--;
}

/*****************************************************************
Returns the status code after a TWI action
******************************************************************/
uint8_t twi_get_status()
{  
	/* mask status */
	uint8_t twiStatus = TWSR & 0xF8;
	
	return twiStatus;
}

/*****************************************************************
Checks to see if acknowledge bit is sent by I2C slave device.
******************************************************************/
uint8_t twi_read_ack()
{
	volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
	
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)) && timeOut > 0)
		timeOut--;
	
	if(timeOut <= 0)
		return 0;
	else
		return TWDR;
}

/*****************************************************************
Checks to see if not-acknowledge bit is sent by I2C slave device.
******************************************************************/
uint8_t twi_read_nack()
{
	volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
	
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	// Wait for transmission to complete
	while(!(TWCR & (1<<TWINT)) && timeOut > 0)
		timeOut--;
	
	if(timeOut <= 0)
		return 0;
	else
		return TWDR;
}

/*****************************************************************
Look for device at specified address; return 1=found, 0=not found.
******************************************************************/
uint8_t twi_detect_device(uint8_t addr)
{
	volatile uint16_t timeOut = TWI_TIMEOUT; //Track if wait is too long for transmission
	
	/* Send Start Condition */
	twi_start();
	
	/* Wait for transmission to complete */
	while(!(TWCR & (1<<TWINT)) && timeOut > 0)
		timeOut--;
	
	twi_write_addr(addr);
	
	return (TW_STATUS==0x18); // return 1 if found; 0 otherwise
}