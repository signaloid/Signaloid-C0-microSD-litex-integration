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


#ifndef __STR_UTILS_H
#define __STR_UTILS_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum STR_UTILS_CONF_enum
{
	/*
	 * 	Max buffer size for str_utils_format_args integer to decimal/hexadecimal conversion
	 */
	kSTR_UTILS_CONF_BUFFER_SIZE = 10,
} STR_UTILS_CONF;

/**
 * 	@brief Creates a formatted string, given a format string and arguments.
 * 	Tries to imitate the snprintf functionality, with very small code size.
 *
 * 	To be used by str_utils_format, and other functions that have already parsed the variable argument list.
 *
 * 	It supports the following format specifiers:
 * 	- %c: character
 * 	- %s: string
 * 	- %d: decimal
 * 	- %x: hexadecimal
 * 	- %%: prints a single %
 * 	- %*<specifier>: left padding with spaces (width is given in the arguments)
 *
 * 	@param res_buf is the resulting string pointer
 * 	@param format is the format string
 * 	@param ... is the arguments for the format string
 * 	@return int the number of characters written, or -1 if an error occurred
 */
int str_utils_format_args(char *  res_buf, const char *  format, va_list args);

/**
 * 	@brief Creates a formatted string, given a format string and arguments.
 * 	Tries to imitate the snprintf functionality, with very small code size.
 * 	It supports the following format specifiers:
 * 	- %c: character
 * 	- %s: string
 * 	- %d: decimal
 * 	- %x: hexadecimal
 * 	- %%: prints a single %
 * 	- %*<specifier>: left padding with spaces (width is given in the arguments)
 * 		example    : 	str_utils_format(res_str, "%*d", 5, 123);
 * 		result     : 	res_str="  123"
 * 		explanation: 	the width is 5 and the value is 123, so we print 2 spaces for padding, then the number,
 * 				for a total of 5 characters.
 *
 * 	@param res_buf is the resulting string pointer
 * 	@param format is the format string
 * 	@param ... is the arguments for the format string
 * 	@return int the number of characters written, or -1 if an error occurred
 */
int str_utils_format(char *  res_buf, const char *  format, ...);

#ifdef __cplusplus
}
#endif

#endif
