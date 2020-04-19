# ATMEGA328_ESSENTIALS
Code base for the ATMEGA 328 MCU peripherals.
I made this for those who want to program the ATmega328 without using Arduino IDE.
Use this as a cheatsheet so you can write your own embedded applications in C.

Included Peripherals
- GPIO
- ADC
- Watchdog Timer
- EEPROM
- UART
- I2C
- SPI

To use this project, clone this repository and open this project with Atmel Studio 6+.

Sample code for each ATmega328 peripheral is under the "mcu" folder each with it's own .c and .h file.
To use the functions from each of the peripherals include the files in "main.c". 

'''
#include "adc.h" // To use the ADC files
#include "wdt.h" 
// And etc...
'''
