/*
 * timer.h
 *
 * Created: 7/3/2014 8:54:19 PM
 *  Author: eric
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

#define TIMER1_PRESCALER			1024	
#define TIMER1_TARGET_FREQ			1		/* Hz */
#define TIMER1_INTERRUPT_FREQ		((F_CPU/(TIMER1_PRESCALER*TIMER1_TARGET_FREQ))-1)

struct timer
{
	volatile uint16_t timeout;
	volatile uint16_t transmit;
	volatile uint8_t transmitReady;
	volatile uint8_t iteration;
}timer;

/****************************************************************

void timer1_init();

DESCRIPTION: 

RETURN: none
****************************************************************/
void timer1_init();

#endif /* TIMER_H_ */