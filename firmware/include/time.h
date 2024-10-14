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


#ifndef __TIME_H
#define __TIME_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t timer0_t;


/**
 * 	@brief 	Enables the timer0 peripheral.
 *
 */
void timer0_enable(void);

/**
 * 	@brief 	Disables the timer0 peripheral.
 *
 */
void timer0_disable(void);

/**
 * 	@brief 	Initializes the timer0 peripheral.
 *
 */
void timer0_init(void);

/**
 * 	@brief 	Returns the current value of the timer.
 *
 * 	@return timer0_t
 */
timer0_t timer0_get_current_value(void);

/**
 * 	@brief 	Returns the time passed since the last load/reload.
 *
 * 	@return timer0_t
 */
timer0_t timer0_get_time_passed_since_last_load(void);

/**
 * 	@brief 	Converts milliseconds to ticks.
 *
 * 	@param 	duration_ms	The duration in milliseconds.
 * 	@return timer0_t
 */
timer0_t timer0_ms_to_ticks(timer0_t duration_ms);

/**
 * 	@brief 	Converts ticks to milliseconds.
 *
 * 	@param 	duration_ticks	The duration in ticks.
 * 	@return timer0_t
 */
timer0_t timer0_ticks_to_ms(timer0_t duration_ticks);

/**
 * 	@brief 	Sets the timer to one-shot mode.
 * 		The timer will be loaded with the specified duration in ticks,
 * 		and start counting down from there. Once the timer expires,
 * 		meaning its current value is zero, the timer will stop.
 *
 * 	@param 	duration_ticks	The duration in ticks.
 */
void timer0_set_one_shot_mode_ticks(timer0_t duration_ticks);

/**
 * 	@brief 	Sets the timer to one-shot mode.
 * 		The timer will be loaded with the specified duration in
 * 		milliseconds, and start counting down from there. Once the timer
 * 		expires, meaning its current value is zero, the timer will stop.
 *
 * 	@param 	duration_ms	The duration in milliseconds.
 */
void timer0_set_one_shot_mode_ms(timer0_t duration_ms);

/**
 * 	@brief 	Sets the timer to periodic mode.
 * 		The timer will be loaded with the specified duration in ticks,
 * 		and start counting down from there. Once the timer expires,
 * 		meaning its current value is zero, the timer will be reloaded
 * 		with the specified duration, and start counting down again from
 * 		there.
 *
 * 	@param 	duration_ticks	The duration in ticks.
 */
void timer0_set_periodic_mode_ticks(timer0_t duration_ticks);

/**
 * 	@brief 	Sets the timer to periodic mode.
 * 		The timer will be loaded with the specified duration in
 * 		milliseconds, and start counting down from there. Once the timer
 * 		expires, meaning its current value is zero, the timer will be
 * 		reloaded with the specified duration, and start counting down
 * 		again from there.
 *
 * 	@param 	duration_ms	The duration in milliseconds.
 */
void timer0_set_periodic_mode_ms(timer0_t duration_ms);

/**
 * 	@brief 	Checks if the timer has expired.
 * 		The timer is considered expired if its current value is zero,
 * 		and was loaded with a non-zero value.
 *
 * 	@return true
 * 	@return false
 */
bool timer0_is_expired(void);

/**
 * 	@brief 	Waits until the timer expires.
 * 		This is blocking, and will not return until the timer expires.
 *
 */
void timer0_wait_to_expire(void);

/**
 * 	@brief 	Delays for the specified duration in ticks.
 * 		This is blocking, and will not return until the timer expires.
 *
 * 	@param 	duration_ticks	The duration in ticks.
 */
void timer0_delay_ticks(timer0_t duration_ticks);

/**
 * 	@brief 	Delays for the specified duration in milliseconds.
 * 		This is blocking, and will not return until the timer expires.
 *
 * 	@param 	duration_ms	The duration in milliseconds.
 */
void timer0_delay_ms(timer0_t duration_ms);

/**
 * 	@brief 	Returns the duration between two times in ticks.
 *		This is useful for calculating the time passed between two
 *		events.
 *		It also works even if the timer has reloaded. Multiple reloads
 *		will NOT be taken into account.
 *
 *		Timestamps should be acquired using:
 *		timer0_t timestamp = timer0_get_timer0_passed_since_last_load();
 *
 *		Example:
 *		timer0_set_periodic_mode_ticks(UINT32_MAX);
 *		timer0_t start_time = timer0_get_timer0_passed_since_last_load();
 *		do_something();
 *		timer0_t end_time = timer0_get_timer0_passed_since_last_load();
 *		timer0_t duration = timer0_get_duration(start_time, end_time);
 *
 * 	@param 	start_time	The start time in ticks.
 * 	@param 	end_time	The end time in ticks.
 * 	@return timer0_t
 */
timer0_t timer0_get_duration(timer0_t start_time, timer0_t end_time);

/**
 * 	@brief 	Returns the duration between two times in milliseconds.
 *		This is useful for calculating the time passed between two
 *		events.
 *		It also works even if the timer has reloaded. Multiple reloads
 *		will NOT be taken into account.
 *
 *		Timestamps should be acquired using:
 *		timer0_t timestamp = timer0_get_time_passed_since_last_load();
 *
 *		Example:
 *		timer0_set_periodic_mode_ticks(UINT32_MAX);
 *		timer0_t start_time = timer0_get_time_passed_since_last_load();
 *		do_something();
 *		timer0_t end_time = timer0_get_time_passed_since_last_load();
 *		timer0_t duration = timer0_get_duration(start_time, end_time);
 *
 * 	@param 	start_time	The start time in ticks.
 * 	@param 	end_time	The end time in ticks.
 * 	@return timer0_t
 */
timer0_t timer0_get_duration_ms(timer0_t start_time, timer0_t end_time);

#ifdef __cplusplus
}
#endif

#endif
