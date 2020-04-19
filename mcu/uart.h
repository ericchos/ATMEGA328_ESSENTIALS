/*
 * usart.h
 *
 * Created: 7/3/2014 8:49:39 PM
 *  Author: eric
 */ 

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

//#define UART0_BAUD				115200UL
#define UART0_BAUD				9600UL
#define UART0_UBRR				(F_CPU/16/UART0_BAUD-1)
#define UART0_RX_BUF_SIZE		32

void uart0_init();
/****************************************************************
Initialize USART hardware

DESCRIPTION:

RETURN: none
****************************************************************/

void uart0_tx(unsigned char data);
/****************************************************************
USART Transmit
void usart0_tx(char data);

DESCRIPTION:

RETURN: none
****************************************************************/

char uart0_rx();
/****************************************************************
USART Receive Byte

DESCRIPTION: The USART receives a byte and is stored in the 
register UDR0. The value of UDR0 is then stored into a char 
variable

RETURN: char (8-bits)
****************************************************************/

void uart0_print(char *str);
/*****************************************************************
USART Print Function

DESCRIPTION: Write a null terminated string to usart

RETURN: none
*****************************************************************/

void uart0_print_F(const char *fdata);
/*****************************************************************
Write a string of characters stored in flash to LPT100 module

DESCRIPTION:

RETURN: none
*****************************************************************/

//void uart0_flush();
/****************************************************************
UART Flush.
void uart0_flush();

DESCRIPTION: The receiver buffer FIFO will be flushed when the 
Receiver is disabled, i.e., the buffer will be emptied of its 
contents. Unread data will be lost. If the buffer has to be flushed 
during normal operation, due to for instance an error condition, 
read the UDRn I/O location until the RXCn Flag is cleared.

RETURN: None
****************************************************************/

void uart0_print_8(uint8_t integerVal);
/*****************************************************************
Print 8-Bit Unsigned Integer to ASCII

DESCRIPTION: Write an 8-bit integer value as ASCII characters

RETURN: None
******************************************************************/

void uart0_print_16(uint16_t integerVal);
/*****************************************************************
Print 16-Bit Unsigned Integer to ASCII

DESCRIPTION: Write an 16-bit integer value as ASCII characters

RETURN: None
******************************************************************/

void uart0_print_32(uint32_t longVal);
/*****************************************************************
Print 32-Bit Unsigned Integer to ASCII

DESCRIPTION: Write convert a 32-bit integer value to ASCII characters

RETURN: None
******************************************************************/

void uart0_scan(char *string_ptr);
/*****************************************************************
DESCRIPTION: Receive a string of characters

PARAM: String

RETURN: None
******************************************************************/

void uart0_wait_for_char(char waitChar);
/*****************************************************************
DESCRIPTION: Wait for a character to be received

PARAM: Character to wait for

RETURN: None
******************************************************************/

//ISR(USART_RX_vect, ISR_BLOCK);
/*****************************************************************
DESCRIPTION: USART ISR when data is received. Each character will
be stored in a buffer. 

ARGUMENTS: None
RETURN: None
******************************************************************/

#endif /* UART_H_ */