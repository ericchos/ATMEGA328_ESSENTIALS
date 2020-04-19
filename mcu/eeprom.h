/*
 * eeprom.h
 *
 * Created: 7/22/2014 2:15:31 PM
 *  Author: Eric
 */ 

#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

#define EEPROM_SIZE 1024 /* Bytes */

unsigned char eeprom_read(unsigned int uiAddress);

void eeprom_write(unsigned int uiAddress, unsigned char ucData);

void eeprom_write_string(unsigned int uiAddress, char *str);

uint16_t eeprom_last_write();

#endif /* EEPROM_H_ */