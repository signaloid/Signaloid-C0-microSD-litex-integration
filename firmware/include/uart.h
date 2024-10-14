/*
 *	Copyright (c) 2024, Signaloid.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */


#ifndef __UART_H
#define __UART_H

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	kUartEvTX = 0x1,
	kUartEvRX = 0x2,
} UartEv;

/**
 * 	@brief Echoes incoming UART data from TX back to the UART RX.
 */
void uart_echo(void);


typedef enum UART_PRINTF_CONF_enum
{
	/*
	 * 	Max buffer size for printf
	 */
	kUART_PRINTF_CONF_BUFFER_SIZE = INT8_MAX,
} UART_PRINTF_CONF;

/**
 * 	@brief Writes a character on UART.
 */
void uart_putchar(char c);

/**
 * 	@brief Writes a formatted string on UART.
 * 	Tries to imitate the printf functionality, with very small code size.
 * 	It supports the following format specifiers:
 * 	- %c: character
 * 	- %s: string
 * 	- %d: decimal
 * 	- %x: hexadecimal
 * 	- %%: prints a single %
 * 	- %*<specifier>: left padding with spaces (width is given in the arguments)
 * 		example    : 	uart_printf("%*d", 5, 123);
 * 		result     : 	"  123"
 * 		explanation: 	the width is 5 and the value is 123, so we print 2 spaces for padding, then the number,
 * 				for a total of 5 characters.
 *
 * 	@param format is the format string
 * 	@param ... is the arguments for the format string
 * 	@return int the number of characters written, or -1 if an error occurred
 */
int  uart_printf(const char *  format, ...);

#ifdef __cplusplus
}
#endif

#endif
