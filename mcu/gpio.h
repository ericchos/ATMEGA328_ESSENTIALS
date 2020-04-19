/*
 * gpio.h
 *
 * Created: 10/15/2014 2:58:09 PM
 *  Author: Eric
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include "../config.h"

void gpio_external_interrupts_init();
/*****************************************************************
DESCRIPTION: Initialize GPIO functions

PARAMETERS: None

RETURN: None
******************************************************************/

//ISR(INT0_vect);

//ISR(INT1_vect);

#endif /* GPIO_H_ */