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
#include <time.h>
#include "uart.h"
#include "leds.h"


/*
 *	Parameter Definitions
 */
typedef enum
{
	kAppConfigLedTogglePeriodMs = 250,
} AppConfig;


/**
 * 	@brief Interrupt Service Routine
 *
 * 	Handles all interrupts
 *
 * 	* Currently does nothing, because we do not implement interrupts.
 */
void
isr(void)
{
	;
}


/**
 * 	@brief The setup function
 * 	This is called once, before the main loop, and is responsible for
 * 	configuring peripherals.
 */
static void
setup(void)
{
	timer0_init();
	leds_init();
}

/**
 * 	@brief The main loop.
 * 	This is called infinitely, and is only interrupted by interrupts handled by
 * 	the Interrupt Service Routine (ISR).
 */
static void
loop(void)
{
	uart_echo();

	/*
	 * 	Toggle LEDs every 500ms
	 */
	if (timer0_is_expired())
	{
		leds_toggle();
		if (leds_red_get())
		{
			uart_printf("LED: Red\n");
		}
		else
		{
			uart_printf("LED: Green\n");
		}
		timer0_set_one_shot_mode_ms(kAppConfigLedTogglePeriodMs);
	}
}

/**
 * 	@brief The main entry point
 */
int
main(void)
{
	setup();

	while (1)
	{
		loop();
	}

	return 0;
}
