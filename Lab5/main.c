
/*
* Authors: Alexis and David
* Main program for touchscreen calculator
*/

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "Calc_FSM.h"
#include "UserInterface.h"
#include "TFTMaster.h"
#include "TouchScreen.h"
#include "ts_lcd.h"

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

    // Draw calculator buttons
    displayButtons();

    // Initialize calculator state machine
    calc_FSM(0, 0, '\0', '\0');

    while (true) {

        // Get button 
        int button = getButton();

        // Process valid button presses
        if (button != -1) {

            // Send button to calc FSM
            calc_FSM(0, 0, '\0', (char)button);

            // Print button for debugging
            printf("Button pressed: %c\n", (char)button);
        }

        sleep_ms(10);
    }

    return 0;
}
