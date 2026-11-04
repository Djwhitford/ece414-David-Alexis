/*
*Authors Alexis and David*
* C file for the Screen Display Finite State Machine (FSM) of our timing system. 
*/
#include "Display_FSM.h"
#include <stdio.h>

//declare variables

screen_t current_state = STATE_INIT;

static void calculateResult();

void display_FSM(int screen){
    
    switch(current_state) {
        case STATE_INIT:
            current_state = STARTING_SCREEN;
            break;
        case STARTING_SCREEN:
            displayStartingScreen();

            break;
        case RUNNING_SCREEN:
            displayRunningScreen();

            break;
        case STOPPED_SCREEN:


            break;  
        case RESULTS_SCREEN:


            break;
        default:
            break;
    } //end of switch

    
    
}//end of void calc fsm
