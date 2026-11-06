
/*
* Authors: Alexis and David
* Main program for touchscreen calculator
*/

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "UserInterface.h"
#include "TFTMaster.h"
#include "TouchScreen.h"
#include "ts_lcd.h"
#include "Display_FSM.h"

int main() {

    //input/output
    stdio_init_all();

    // Initialize LCD
    tft_init_hw();
    tft_begin();
    tft_setRotation(3);

    // Initialize touchscreen
    ts_lcd_init();
    sleep_ms(500);

    // Draw display screen
     bool breakbeam = false; // Simulated breakbeam state for testing
     setBreakbeamActivated(breakbeam);
    while (1) {
       display_FSM(0);
       sleep_ms(5000); // Add a small delay to avoid overwhelming the display

         breakbeam = !breakbeam;
         //setBreakbeamActivated(breakbeam); // Toggle the simulated breakbeam state
    }

    return 0;
}
