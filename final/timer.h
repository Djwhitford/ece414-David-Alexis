/*
 * Simple Timer Module
 * Read & calculate elapsed time with 32-bit timestamps
 * Note that the hardware_time module provides similar
 * functions using 64-bit timestamps
 *
 * ECE 414 - Lafayette College
 * J. Nestor July 2023
 */

#ifndef TIMER_H
#define TIMER_H

#include <stddef.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Read the current time in microseconds
uint32_t timer_read();

// Calculate elapsed time in microseconds
uint32_t timer_elapsed_us(uint32_t t1, uint32_t t2);

// Calculate elapsed time in milliseconds
uint32_t timer_elapsed_ms(uint32_t t1, uint32_t t2);

//Calculate minutes
uint32_t timer_elapsed_min(uint32_t t1, uint32_t t2);

//calculate elapsed time in seconds
uint32_t timer_elapsed_s(uint32_t t1, uint32_t t2);

// Split elapsed milliseconds into minutes, seconds, and remaining milliseconds
void timer_split_ms(uint32_t elapsed_ms, uint32_t *minutes, uint32_t *seconds, uint32_t *milliseconds);

//Helper function to convert elapsed time in milliseconds to a string format "MM:SS.mmm"
void timer_format_time(uint32_t elapsed_ms, char *buffer, size_t buffer_size);

// Reset the timer by reading the current time and returning it
void reset_timer();

#endif