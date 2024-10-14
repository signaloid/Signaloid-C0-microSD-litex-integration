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
#include "leds.h"

#include <stdbool.h>


/**
 * 	@brief Saves the LEDs' current state.
 */
bool leds_red_is_on = false;
bool leds_green_is_on = false;

void
leds_set(void)
{
	leds_out_write(
		0
		| (leds_red_is_on << CSR_LEDS_OUT_RED_OFFSET)
		| (leds_green_is_on << CSR_LEDS_OUT_GREEN_OFFSET)
	);
}

void
leds_red_on(void)
{
	leds_red_is_on = true;
	leds_set();
}

void
leds_red_off(void)
{
	leds_red_is_on = false;
	leds_set();
}

bool
leds_red_get(void)
{
	return leds_red_is_on;
}

void
leds_green_on(void)
{
	leds_green_is_on = true;
	leds_set();
}

void
leds_green_off(void)
{
	leds_green_is_on = false;
	leds_set();
}

bool
leds_green_get(void)
{
	return leds_green_is_on;
}

void
leds_init(void)
{
	leds_red_off();
	leds_green_off();
}

void
leds_toggle(void)
{
	leds_red_is_on = !leds_red_is_on;
	leds_green_is_on = !leds_red_is_on;
	leds_set();
}
