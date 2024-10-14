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


#include "str_utils.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

int
str_utils_format_args(char *  res_buf, const char *  format, va_list args)
{
	if (format == NULL)
	{
		return -1;
	}

	uint8_t len = 0;
	char	buf[kSTR_UTILS_CONF_BUFFER_SIZE];

	/*
	 * 	Loop until we reach the end of the format string
	 */
	while (*format != '\0')
	{
		/*
		 * 	If we don't find a % character, we just copy the character
		 */
		if (*format != '%')
		{
			res_buf[len] = *format;
			len++;
			format++;
			continue;
		}

		/*
		 * 	Skip the % character
		 */
		format++;

		/*
		 * 	Check if we have a left padding
		 */
		int space = 0;
		if (*format == '*')
		{
			/*
			 * 	Get the padding width
			 */
			space = va_arg(args, int);
			format++;
		}

		/*
		 * 	Check the format specifier
		 */
		switch (*format)
		{
			/*
			 * 	Print a single %
			 */
			case '%':
				/*
				 * 	check if we have a left padding
				 */
				if (space > 1)
				{
					for (int i = 0; i < space - 1; i++)
					{
						res_buf[len] = ' ';
						len++;
					}
				}

				/*
				 * 	print the %
				 */
				res_buf[len] = '%';

				len++;
				format++;
				break;

			/*
			 * 	Print a character
			 */
			case 'c':
				/*
				 * 	check if we have a left padding
				 */
				if (space > 1)
				{
					for (int i = 0; i < space - 1; i++)
					{
						res_buf[len] = ' ';
						len++;
					}
				}

				format++;

				/*
				 * 	print the character
				 */
				char c	     = (char)va_arg(args, int);
				res_buf[len] = c;

				len++;
				break;

			/*
			 * 	Print a string
			 */
			case 's':
				format++;
				char *	s     = (char *)va_arg(args, int);
				uint8_t s_len = strlen(s);

				/*
				 * 	check if we have a left padding
				 */
				if (space > s_len)
				{
					for (int i = 0; i < space - s_len; i++)
					{
						res_buf[len] = ' ';
						len++;
					}
				}

				/*
				 * 	print the string
				 */
				while (*s != '\0')
				{
					res_buf[len] = *s;
					len++;
					s++;
				}
				break;

			/*
			 * 	Print a decimal
			 */
			case 'd':
				format++;
				int    d     = va_arg(args, int);

				/*
				 * 	convert the decimal to a string
				 */
				char *  str_d = itoa(d, buf, 10);

				uint8_t str_d_len = strlen(str_d);

				/*
				 * 	check if we have a left padding
				 */
				if (space > str_d_len)
				{
					for (int i = 0; i < space - str_d_len; i++)
					{
						res_buf[len] = ' ';
						len++;
					}
				}

				/*
				 * 	print the decimal string
				 */
				while (*str_d != '\0')
				{
					res_buf[len] = *str_d;
					len++;
					str_d++;
				}
				break;

			/*
			 * 	Print a hexadecimal
			 */
			case 'x':
				format++;
				int    x     = va_arg(args, int);

				/*
				 * 	convert the hexadecimal to a string
				 */
				char *  str_x = itoa(x, buf, 16);

				uint8_t str_x_len = strlen(str_x);

				/*
				 * 	check if we have a left padding
				 */
				if (space > str_x_len)
				{
					for (int i = 0; i < space - str_x_len; i++)
					{
						res_buf[len] = ' ';
						len++;
					}
				}

				/*
				 * 	print the hexdecimal string
				 */
				while (*str_x != '\0')
				{
					res_buf[len] = *str_x;
					len++;
					str_x++;
				}
				break;

			/*
			 * 	Should never happen, but just in case, copy the character
			 */
			default:
				res_buf[len] = *format;
				len++;
				format++;
				break;
		}
	}

	/*
	 * 	Return the number of characters written
	 */
	return len;
}

int
str_utils_format(char *  res_buf, const char *  format, ...)
{
	if (format == NULL)
	{
		return -1;
	}

	/*
	 * 	Variable argument list
	 */
	va_list args;
	va_start(args, format);

	/*
	 * 	Format the string
	 */
	int len = str_utils_format_args(res_buf, format, args);

	/*
	 * 	End variable argument list
	 */
	va_end(args);

	/*
	 * 	Return the number of characters written
	 */
	return len;
}
