/*
 * eeprom.c
 *
 * Created: 7/22/2014 2:15:42 PM
 *  Author: Eric
 */ 
#include <avr/io.h>
#include "eeprom.h"

unsigned char eeprom_read(unsigned int uiAddress)
{
	//Wait for completion of previous write
	while(EECR & (1<<EEPE));
	
	//Set up address register
	EEAR = uiAddress;
	
	//Start eeprom read by writing EERE
	EECR |= (1<<EERE);
	
	//Return data from the data register
	return EEDR;
}

void eeprom_write(unsigned int uiAddress, unsigned char ucData)
{
	//Wait for completion of previous write
	while(EECR & (1<<EEPE));
	
	//Setup address and data registers
	EEAR = uiAddress;
	EEDR = ucData;
	
	//Write logical one to EEMPE
	EECR |= (1<<EEMPE);
	
	//Start eeprom write by setting EEPE
	EECR |= (1<<EEPE);
}

void eeprom_write_string(unsigned int uiAddress, char *str)
{
	if(str == 0 || *str == 0)
		return;
	
	do
	{
		eeprom_write(uiAddress, *str++);
		++uiAddress;
	} while(*str != 0);
}

uint16_t eeprom_last_write()
{
	uint16_t eepromPositon;
	uint8_t tempData;
	
	for(eepromPositon=0 ; eepromPositon<EEPROM_SIZE; eepromPositon++)
	{
		tempData = eeprom_read(eepromPositon);
		if(tempData == 0xFF)
			break;
	}
	return eepromPositon;
}