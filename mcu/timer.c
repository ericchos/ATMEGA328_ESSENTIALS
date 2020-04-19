/*
 * timer.c
 *
 * Created: 7/3/2014 8:54:05 PM
 *  Author: eric
 */ 

#include <avr/interrupt.h>
#include "../config.h"
#include "timer.h"

/*****************************************************************
* Initialize timer
******************************************************************/
void timer1_init()
{	
	TCCR1B |= (1<<WGM12);
	
	TIMSK1 = (1<<OCIE1A);
	
	OCR1A = TIMER1_INTERRUPT_FREQ;
	
	TCCR1B |= (1<<CS10)|(1<<CS12);
}