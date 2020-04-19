/*
 * wdt.c
 *
 * Created: 8/27/2014 10:32:08 AM
 *  Author: eric
 */ 

#include "wdt.h"
#include "../config.h"
#include <avr/wdt.h>

uint8_t mcusr_mirror __attribute__ ((section (".noinit")));

void get_mcusr(void)
{
	mcusr_mirror = MCUSR;
	MCUSR = 0;
	wdt_disable();
}