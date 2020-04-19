/*
 * uart.c
 *
 * Created: 7/3/2014 8:49:51 PM
 *  Author: eric
 */ 

#include "../config.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

/***************************************************************** 
* Initialize UART hardware 
******************************************************************/
void uart0_init()
{
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)/*|(1<<RXCIE0)*/;
	
	/* Set frame format: 8 bit data, 1 stop bit */
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
	/* Set baud rate */
	UBRR0H = (uint8_t)(UART0_UBRR>>8);
	UBRR0L = (uint8_t) UART0_UBRR;
}

/***************************************************************** 
* UART Transmit 
******************************************************************/
void uart0_tx(unsigned char data)
{
	volatile uint16_t timeOut = 0xFFFF;
	
	/* Wait for empty transmit buffer */
	while(!(UCSR0A & (1<<UDRE0)) && timeOut > 0)
		timeOut--;
	
	/* Put data into buffer, and send data */
	UDR0 = data;
}

/***************************************************************** 
* UART Flush. 
*	Empties receive buffer when receiver is disabled. 
******************************************************************/
/* Not using at the moment, but may have future use
void usart0_flush()
{
	unsigned char temp;
	
	while(UCSR0A & (1<<RXC0))
		temp = UDR0;
}
*/

/*****************************************************************
* UART Receive 
******************************************************************/
char uart0_rx(void)
{
	/*
	volatile uint16_t timeOut = 0xFFFF;
	
	// Wait for data to be received
	while(!(UCSR0A & (1<<RXC0)) && timeOut > 0) 
		timeOut--;
	*/
	while(!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

/***************************************************************** 
* Write a null terminated string to UART
*****************************************************************/
void uart0_print(char *str)
{
	/* If string is empty or has reached the NULL terminator, 
		exit function */
	if(str == 0 || *str == 0)
		return;
	
	/* Each character of the string starting with the first
	character will be sent off into the USART buffer to be 
	transmitted until the string reaches the last character */
	do 
	{
		uart0_tx(*str++);
	} while(*str != 0);	
}

/***************************************************************** 
* Write a string of characters stored in flash to LPT100 module 
*****************************************************************/
void uart0_print_F(const char *fdata)
{
	while(pgm_read_byte(fdata) != 0x00)
	{
		uart0_tx(pgm_read_byte(fdata++));
	}
}

/*****************************************************************
* Write an 8-bit integer value as ASCII characters
******************************************************************/
void uart0_print_8(uint8_t integerVal)
{
	uint16_t temp[3];
	int16_t i,j;
	
	for(i=0; i<=2; i++)
	{
		temp[i] = integerVal % 10;
		integerVal = integerVal/10;
	}
	
	/* Skip all the leading zeros */
	for (j = 2; j >= 1; j--)
	{
		if (temp[j] != 0)
		{
			break;
		}
	}
	
	/* Send converted int to ascii value to uart */
	for (; j >= 0; j--)
	{
		uart0_tx(temp[j]+'0');
	}
}

/*****************************************************************
* Write an 16-bit integer value as ASCII characters
******************************************************************/
void uart0_print_16(uint16_t integerVal)
{
	uint16_t temp[5];
	int16_t i,j;
	
	for(i=0; i<=4; i++)
	{
		temp[i] = integerVal % 10;
		integerVal = integerVal/10;
	}
	
	/* Skip all the leading zeros */
	for (j = 4; j >= 1; j--)
	{
		if (temp[j] != 0)
		{
			break;
		}
	}
	
	/* Send converted int to ascii value to uart */
	for (; j >= 0; j--)
	{
		uart0_tx(temp[j]+'0');
	}
}

/*****************************************************************
* Write convert a 32-bit integer value to ASCII characters
******************************************************************/
void uart0_print_32(uint32_t longVal)
{
	uint32_t temp[10];
	int32_t i,j;
	
	for(i=0; i<=9; i++)
	{
		temp[i] = longVal % 10;
		longVal = longVal/10;
	}
	
	/* Skip all the leading zeros */
	for (j = 9; j >= 1; j--)
	{
		if (temp[j] != 0)
		{
			break;
		}
	}
	
	/* Send converted int to ascii value to uart */
	for (; j >= 0; j--)
	{
		uart0_tx(temp[j]+'0');
	}
}

/*****************************************************************
* Receive a string
******************************************************************/
void uart0_scan(char *string_ptr)
{
	char ch;
	
	while(1)
	{
		ch = uart0_rx(); //Receive character
		
		//Read data until newline or carriage return
		if(ch == '\n')
		{
			*string_ptr = 0;
			break;
		}
		
		*string_ptr = ch; //Copy character into string
		string_ptr++; //Increment the pointer
	}
}

/*****************************************************************
* Wait for a character to be received
******************************************************************/
void uart0_wait_for_char(char waitChar)
{
	volatile char ch;
	
	do
	{
		ch = uart0_rx();
	} while (ch != waitChar);
}