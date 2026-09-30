/*
* Authors: Alexis and David
* C file for main.c. This file combines the user interface and the calculator finite state machine to create a simple calculator application.
*/

#include <stdio.h>
#include "pico/stdlib.h"



int main() {
   
   //global variables for the calculator

    stdio_init_all();
    led_out_init();
    sw_in_init();
    debounce_sw1_init();
    debounce_sw2_init();

    while (true){
        


        calc_FSM(int button1_location, int button2_location, char operator_location);

    }
}