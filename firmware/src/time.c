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
#include <stdbool.h>
#include "time.h"

void
timer0_enable(void)
{
	timer0_en_write(1);
}

void
timer0_disable(void)
{
	timer0_en_write(0);
}

void
timer0_init(void)
{
	timer0_disable();
	timer0_reload_write(0);
	timer0_load_write(0);
}

timer0_t
timer0_get_current_value(void)
{
	timer0_update_value_write(1);
	return timer0_value_read();
}

timer0_t
timer0_get_time_passed_since_last_load(void)
{
	timer0_t start_value = timer0_reload_read();

	if (start_value == 0)
	{
		start_value = timer0_load_read();
	}

	return start_value - timer0_get_current_value();
}

timer0_t
timer0_ms_to_ticks(timer0_t duration_ms)
{
	return (CONFIG_CLOCK_FREQUENCY / 1000U) * duration_ms;
}

timer0_t
timer0_ticks_to_ms(timer0_t duration_ticks)
{
	return duration_ticks / (CONFIG_CLOCK_FREQUENCY / 1000);
}

void
timer0_set_one_shot_mode_ticks(timer0_t duration_ticks)
{
	timer0_disable();
	timer0_load_write(duration_ticks);
	timer0_reload_write(0);
	timer0_enable();
}

void
timer0_set_one_shot_mode_ms(timer0_t duration_ms)
{
	timer0_t duration_ticks = timer0_ms_to_ticks(duration_ms);
	timer0_set_one_shot_mode_ticks(duration_ticks);
}

void
timer0_set_periodic_mode_ticks(timer0_t duration_ticks)
{
	timer0_disable();
	timer0_load_write(0);
	timer0_reload_write(duration_ticks);
	timer0_enable();
}

void
timer0_set_periodic_mode_ms(timer0_t duration_ms)
{
	timer0_t duration_ticks = timer0_ms_to_ticks(duration_ms);
	timer0_set_periodic_mode_ticks(duration_ticks);
}

bool
timer0_is_expired(void)
{
	if (timer0_reload_read() == 0 && timer0_load_read() == 0)
	{
		return true;
	}
	return timer0_get_current_value() == 0;
}

void
timer0_wait_to_expire(void)
{
	while (!timer0_is_expired())
	{
		;
	}
}

void
timer0_delay_ticks(timer0_t duration_ticks)
{
	timer0_set_one_shot_mode_ticks(duration_ticks);

	timer0_wait_to_expire();
}

void
timer0_delay_ms(timer0_t duration_ms)
{
	timer0_set_one_shot_mode_ms(duration_ms);

	timer0_wait_to_expire();
}

timer0_t
timer0_get_duration(timer0_t start_time, timer0_t end_time)
{
	timer0_t time_diff;

	if (end_time >= start_time)
	{
		time_diff = end_time - start_time;
	}
	else
	{
		/*
		 *	Timer has overflowed
		 */
		time_diff = (timer0_reload_read() - start_time) + end_time;
	}

	return time_diff;
}

timer0_t
timer0_get_duration_ms(timer0_t start_time, timer0_t end_time) {
	return timer0_ticks_to_ms(timer0_get_duration(start_time, end_time));
}
