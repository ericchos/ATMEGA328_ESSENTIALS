/*
 * adc.h
 *
 * Created: 7/3/2014 8:51:34 PM
 *  Author: eric
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

//#define ADC_MODE	
//#define ADC_12BIT_OVERSAMPLED	1
//#define ADC_TOSS_FIRST_SAMPLE	1

void adc_init();
/****************************************************************
DESCRIPTION: Initializes the ADC hardware.
ARGUMENTS: NONE
RETURN: NONE
****************************************************************/

void adc_enable_vref();
void adc_disable_vref();

uint16_t adc_single_conversion(uint8_t ADCchannel);
/****************************************************************
DESCRIPTION:Takes the ADC reading.
ARGUMENTS: uint8_t ADCchannel: ADC Pin
RETURN: uint16_t: ADC Reading
****************************************************************/

uint16_t adc_read(uint8_t sensorNo, uint8_t noOfSamples);
/****************************************************************
DESCRIPTION:
Takes the sum of a specified number of ADC samples and averages
them. 
ARGUMENTS: 
	- uint8_t sensorNo: ADC pin
	- uint8_t noOFSamples: Number of ADC samples to take 
RETURN: uint16_t: Averaged ADC reading
****************************************************************/

uint16_t adc_12bit_oversampled_read(uint8_t sensorNo);
/****************************************************************
DESCRIPTION:
Take an oversampled ADC reading to increase the
resolution to 12-bits.
This is done by adding 16 10-bit samples and diving the result by 4
to get a 12 bit result.
Mathematically if you want n bits, you take a sum of 2^(2^n) samples
and bit shift the result n times to the right (equivalent of dividing
by 2^n).
ARGUMENTS: uint8_t sensorNo: ADC pin 
RETURN: uint16_t: Oversampled 12-bit ADC result
****************************************************************/

#endif /* ADC_H_ */