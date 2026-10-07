/*
* Authors: Alexis and David
* C file for main.c. This file combines the user interface and the calculator finite state machine to create a simple calculator application.
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "Calc_FSM.h"
#include "UserInterface.h"
#include "TFTMaster.h"
#include "TouchScreen.h"
#include "ts_lcd.h"




int main() {
   
   //global variables for the calculator

    stdio_init_all();
    tft_init_hw();
    tft_begin();
    tft_setRotation(3);
    displayButtons();
    //displayResult(0);
    displayError();
    int button1_location;
    int button2_location;
    char operator_location;

    while (true){
        
        //displayButtons();
            //tft_fillRect(220, 95, 60, 40, ILI9340_GREEN);

        //calc_FSM(button1_location,  button2_location, operator_location);

    }
}