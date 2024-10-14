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


#ifndef __LEDS_H
#define __LEDS_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 	@brief Turns on the Red LED.
 */
void leds_red_on(void);

/**
 * 	@brief Turns off the Red LED.
 */
void leds_red_off(void);

/**
 * 	@brief Returns the Red LED's state.
 */
bool leds_red_get(void);

/**
 * 	@brief Turns on the Red LED.
 */
void leds_green_on(void);

/**
 * 	@brief Turns off the Red LED.
 */
void leds_green_off(void);

/**
 * 	@brief Returns the Green LED's state.
 */
bool leds_green_get(void);

/**
 * 	@brief Initializes the LEDs' default state.
 *
 * 	* Red   : off
 * 	* Green : off
 */
void leds_init(void);

/**
 * 	@brief Toggles the two LEDs, and writes their state on UART.
 * 	When the red led is on, the green led is turned off, and vice versa.
 */
void leds_toggle(void);

#ifdef __cplusplus
}
#endif

#endif
