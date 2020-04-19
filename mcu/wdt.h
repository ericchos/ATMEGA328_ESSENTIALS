/*
 * wdt.h
 *
 * Created: 7/9/2014 11:05:41 PM
 *  Author: Eric
 *
 * Some Macros to use the watchdog timer:
 *	wdt_reset(); //Resets watchdog timer
 *  wdt_disable(); //Disable watchdog timer
 *	wdt_enable(TIMEOUT); //Sets watchdog pre-scaler
 */ 

#ifndef WDT_H_
#define WDT_H_

//#define wdt_reset(); //Reset watchdog timer
//define wdt_disable(); //Disable watchdog timer
//#define wdt_enable(timeout); //Sets watchdog pre-scaler

#define WDT0_15MS  0
#define WDT0_30MS  1
#define WDT0_60MS  2
#define WDT0_120MS  3
#define WDT0_250MS  4
#define WDT0_500MS  5

#define WDT0_1S  6
#define WDT0_2S  7
#define WDT0_4S  8
#define WDT0_8S  9

void get_mcusr(void);

#endif /* WDT_H_ */