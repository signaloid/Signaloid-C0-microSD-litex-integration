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


#include <generated/csr.h>
#include "uart.h"
#include <stdlib.h>
#include <stdarg.h>
#include "str_utils.h"

void
uart_echo(void)
{
	uint32_t buf = 0;

	/*
	 *	Check for incoming bytes
	 */
	if (uart_rxempty_read())
	{
		return;
	}

	/*
	 *	Loop until we read all bytes
	 */
	do
	{
		/*
		 *	Read an incoming byte
		 */
		buf = uart_rxtx_read();

		/*
		 * 	Tell the UART that we read a byte out of the FIFO
		 * 	and that it can give us another.
		 */
		uart_ev_pending_write(kUartEvRX);

		/*
		 * 	Mirror the bytes back
		 */
		uart_rxtx_write(buf);
	}
	while (!uart_rxempty_read());

	uart_rxtx_write('\n');
}

void
uart_putchar(char c)
{
	/*
	 * 	Wait until the UART is ready to send a byte
	 */
	while (uart_txfull_read());
	uart_rxtx_write(c);
}

/**
 * 	@brief Writes a buffer on UART.
 *
 * 	@param buf
 * 	@param len
 */
void
uart_print_buf(char *  buf, uint8_t len)
{
	for (uint8_t i = 0; i < len; i++)
	{
		uart_putchar(buf[i]);
	}
}

int
uart_printf(const char *  format, ...)
{
	if (format == NULL)
	{
		return -1;
	}

	/*
	 * 	Buffer for the formatted string
	 */
	char buf[kUART_PRINTF_CONF_BUFFER_SIZE];

	/*
	 * 	Variable argument list
	 */
	va_list args;
	va_start(args, format);

	/*
	 * 	Format the string
	 */
	int len = str_utils_format_args(buf, format, args);

	/*
	 * 	End variable argument list
	 */
	va_end(args);

	/*
	 * 	Check if the format was successful
	 */
	if (len < 0)
	{
		return -1;
	}

	/*
	 * 	Write the formatted string on UART
	 */
	uart_print_buf(buf, len);

	/*
	 * 	Return the number of characters written
	 */
	return len;
}
