/*
*Authors Alexis and David*
* C file for the Screen Display Finite State Machine (FSM) of our timing system. 
*/
#include "Display_FSM.h"
#include <stdio.h>  
#include <stdbool.h>
#include "userInterface.h"



//declare variables

screen_t current_state = STATE_INIT;
static bool breakbeam = false;
static float timeElapsed = 0.0;
static float averageSpeed = 0.0;

static void calculateResult(){

}

void setBreakbeamActivated(bool activated) {
    breakbeam = activated;
}

void display_FSM(int screen){
    
    switch(current_state) {
        case STATE_INIT:
            current_state = STARTING_SCREEN;
            break;
        case STARTING_SCREEN:
            displayStartingScreen();
            if (breakbeam) {
                current_state = RUNNING_SCREEN;
            }
            break;
        case RUNNING_SCREEN:
            displayRunningScreen();
            if (!breakbeam) {
                current_state = STOPPED_SCREEN;
            }
            break;
        case STOPPED_SCREEN:
            displayStoppedScreen();
            //TIMER 5 SECONDS
            current_state = RESULTS_SCREEN;
            break;  
        case RESULTS_SCREEN:
            displayResultsScreen();
            //calculateResult();
            /*
            if(touchscreenPressed){
                current_state = STARTING_SCREEN;
            }
            */
            break;
        default:
            break;
    } //end of switch

    
    
}//end of void calc fsm
