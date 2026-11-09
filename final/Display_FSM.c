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
static screen_t last_displayed_state = STATE_INIT;
static bool breakbeam = true; // Simulated breakbeam state for testing
static float timeElapsed = 0.0;
static float averageSpeed = 0.0;

static void calculateResult(){

}

void setBreakbeamActivated(bool activated) {
    breakbeam = activated;
}

void display_FSM(int screen, uint32_t elapsedTime) {
    switch(current_state) {
        case STATE_INIT:
            current_state = STARTING_SCREEN;
            break;
        case STARTING_SCREEN:
            if (last_displayed_state != STARTING_SCREEN) {
                displayStartingScreen();
                last_displayed_state = STARTING_SCREEN;
            }
            if (breakbeam) {
                current_state = RUNNING_SCREEN;
            }
            break;
        case RUNNING_SCREEN:
            if (last_displayed_state != RUNNING_SCREEN) {
                displayRunningScreen();
                last_displayed_state = RUNNING_SCREEN;
            }
            displayRunningTime(elapsedTime);
            if (!breakbeam) {
                current_state = STOPPED_SCREEN;
            }
            if(elapsedTime >= 10000) {
                current_state = STOPPED_SCREEN;
            }

            break;
        case STOPPED_SCREEN:
            if (last_displayed_state != STOPPED_SCREEN) {
                displayStoppedScreen();
                last_displayed_state = STOPPED_SCREEN;
            }
            //TIMER 5 SECONDS
            current_state = RESULTS_SCREEN;
            break;  
        case RESULTS_SCREEN:
            if (last_displayed_state != RESULTS_SCREEN) {
                displayResultsScreen();
                last_displayed_state = RESULTS_SCREEN;
            }
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
