/*
*File: ts_lcd.h
*Authors Alexis and Davidd
*/


#ifndef TS_LCD_H
#define TS_LCD_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

/*
 * Pin Assigments for toucscreen
 *  Y+ => GP27 (Pin 32)
 *  Y- => GP21 (Pin 27)
 *  X+ => GP22 (Pin 29)
 *  X- => GP26 (Pin 31)
 * 
 */


/*GPIO pin positions four touchscreen terminals*/
#define XPbit 22
#define XMbit 26
#define YPbit 27
#define YMbit 21

/*ADC positions*/
#define XMchan 0
#define YPchan 1

/*resistance between X+ and X- terminals*/
#define RXPLATE 275

/*
*initalize the touchscreen
 */
void ts_lcd_init(void);

/*
* Reads the touchscreen status and position 
*returns true when the screen is touched. 
*px and py contain the current position in LCD coordinates
*/
bool get_ts_lcd(uint16_t *px, uint16_t *py);

#endif