/*
 * adc.c
 *
 * Created: 7/3/2014 8:51:23 PM
 *  Author: eric
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "adc.h"

/* Initialize ADC peripheral */
void adc_init()
{
	/* Select Vref=AVcc */
	adc_enable_vref();
	
	/* Set prescaller to 128 and enable ADC */
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

void adc_enable_vref()
{
	/* Select Vref=AVcc */
	ADMUX |= (1<<REFS0);
}

void adc_disable_vref()
{
	/* Clear Vref bit */
	ADMUX &= ~(1<<REFS0);
}

/* Set the ADC sleep mode */
void adc_set_sleep_mode()
{
	set_sleep_mode(SLEEP_MODE_ADC);
	
	ADCSRA |= (1<<ADIE);
	
	sei();
}

/* Interrupt handler for the ADC sleep mode */
EMPTY_INTERRUPT(ADC_vect);

/* Average the ADC readings in sleep mode */
uint16_t adc_averaged_sleep_read(uint8_t ADCChannel, uint8_t samples)
{
	uint16_t results = 0;
	
	/* Select ADC channel with safety mask */
	ADMUX = (ADMUX & 0xF0) | (ADCChannel & 0x0F);
	
	//Take 5 conversions and not use the values
	for(uint8_t i=0; i<5; i++)
	{
		sleep_mode();
		
		results = ADC;
	}
	
	//Reset the results variable to take new readings
	results = 0;
	
	for(uint8_t i=0; i<samples; i++)
	{
		/* Go to sleep & make conversion */
		sleep_mode();
		
		results += ADC;
	}
	
	return results/samples;
}

/* Get the A/D reading */
uint16_t adc_single_conversion(uint8_t ADCchannel)
{
	/* Select ADC channel with safety mask */
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	
	/* Single conversion mode */
	ADCSRA |= (1<<ADSC);
	
	/* Wait until ADC conversion is complete */
	while( ADCSRA & (1<<ADSC) );
	
	/* Return the ADC value */
	return ADC;
}

/* Take an average reading to "smooth" ADC readings */
uint16_t adc_read(uint8_t sensorNo, uint8_t noOfSamples)
{
	/* Declare variables */
	uint16_t sum = 0, analogSensorVal[noOfSamples];
	
	if(noOfSamples == 1)
	{
		return adc_single_conversion(sensorNo);
	}
	else
	{
		for(uint8_t i = 0; i<noOfSamples; i++)
		{
			analogSensorVal[i] = adc_single_conversion(sensorNo);
		
			sum += analogSensorVal[i];
		}
		
		return sum/noOfSamples;
	}
}

/*****************************************************************
Take an oversampled ADC reading to increase the 
resolution to 12-bits.
	
This is done by adding 16 10-bit samples and diving the result by 4
to get a 12 bit result.
	
Mathematically if you want n bits, you take a sum of 2^(2^n) samples
and bit shift the result n times to the right (equivalent of dividing
by 2^n).
******************************************************************/
uint16_t adc_12bit_oversampled_read(uint8_t sensorNo)
{
	//Declare variables
	uint16_t sum = 0, analogSensorVal[16];
	
	for(uint8_t i = 0; i<16; i++)
	{
		analogSensorVal[i] = adc_single_conversion(sensorNo);
		
		sum += analogSensorVal[i];
	}	
	
	return (sum >> 2);
}

/*****************************************************************
* Take a number of ADC samples and toss out outliers
******************************************************************/
uint16_t adc_read_outlier_filter(uint8_t adc_channel, uint8_t noOfSamples, uint8_t tolerance)
{
	volatile uint16_t referenceRead;
	uint16_t highLimit, lowLimit;
	uint16_t samples[noOfSamples];
	
	//Take one ADC sample, toss out the result and take another
	for(uint8_t i = 0; i<2; i++)
	{
		referenceRead = adc_read(adc_channel, 5);	
	}
	
	//Calculate the highest and lowest acceptable values for the reading
	highLimit = referenceRead + tolerance;
	lowLimit = referenceRead - tolerance;
	
	//Take ADC averages and toss out outliers
	uint8_t samplesCnt = 0, retries = 0; //Counter for averaging loop
	do 
	{
		samples[samplesCnt] = adc_single_conversion(adc_channel);
		
		if((samples[samplesCnt] > lowLimit) && (samples[samplesCnt] < highLimit))
			samplesCnt++;
		else
		{
			++retries;
			if(retries > 3)
				return 0;
		}

	} while (samplesCnt < noOfSamples);
	
	return 0;
}