
/*
* Authors: Alexis and David
* Main program for touchscreen display and timing system.
*/

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "UserInterface.h"
#include "TFTMaster.h"
#include "TouchScreen.h"
#include "ts_lcd.h"
#include "Display_FSM.h"
#include "timer.h"

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
    uint32_t last_time = 0;

    // Draw display screen
       

        while (true) {
            display_FSM(0);
        
        }
        
    return 0;
}
