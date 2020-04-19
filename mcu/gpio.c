/*
 * gpio.c
 *
 * Created: 10/15/2014 2:57:58 PM
 *  Author: Eric
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.h"

void gpio_external_interrupts_init()
{
	//Initialize INT0 ISR (PD2)
	WRITE(EIMSK, (1<<INT0));
	WRITE(EICRA, (1<<ISC00));
}