/*
*Authors Alexis and David*
* C file for the Screen Display Finite State Machine (FSM) of our timing system. 
*/
#include "Display_FSM.h"
#include <stdio.h>  
#include <stdbool.h>
#include "userInterface.h"
#include "ts_lcd.h"
#include "timer.h"




//declare variables

screen_t current_state = STATE_INIT;
static screen_t last_displayed_state = STATE_INIT;
static bool breakbeam = true; // Simulated breakbeam state for testing
static float timeElapsed = 0.0;
static float averageSpeed = 0.0;
uint32_t start_time = 0;
uint32_t elapsed_time = 0;

static void calculateResult(){

}

void setBreakbeamActivated(bool activated) {
    breakbeam = activated;
}

void display_FSM(int screen) {
    switch(current_state) {
        case STATE_INIT:
            current_state = STARTING_SCREEN;
            break;
        case STARTING_SCREEN:
            if (last_displayed_state != STARTING_SCREEN ) {
                displayStartingScreen();
                last_displayed_state = STARTING_SCREEN;
            }
            sleep_ms(5000); // Wait for 5 seconds before transitioning to the running screen
            current_state = RUNNING_SCREEN;
            break;
        case RUNNING_SCREEN:
            if (last_displayed_state != RUNNING_SCREEN) {
                start_time = timer_read(); // Reset only once, when entering the running screen
                elapsed_time = 0;
                displayRunningScreen();
                last_displayed_state = RUNNING_SCREEN;
            }
            elapsed_time = timer_elapsed_ms(start_time, timer_read());
            if (elapsed_time >= 10000) {
                elapsed_time = 10000;
                current_state = STOPPED_SCREEN;
            }
            displayRunningTime(elapsed_time);

            break;
        case STOPPED_SCREEN:
            if (last_displayed_state != STOPPED_SCREEN) {
                displayStoppedScreen();
                last_displayed_state = STOPPED_SCREEN;
            }
            if (get_ts_lcd(NULL, NULL)) { // Check if the touchscreen is pressed
                current_state = RUNNING_SCREEN;
            }
            sleep_ms(5000); // Wait for 1 second before transitioning to the results screen
            current_state = RESULTS_SCREEN;
            break;  
        case RESULTS_SCREEN:
            if (last_displayed_state != RESULTS_SCREEN) {
                displayResultsScreen();
                last_displayed_state = RESULTS_SCREEN;
            }
            if(get_ts_lcd(NULL, NULL)){
                current_state = STARTING_SCREEN;
            }
            break;
        default:
            break;
    } //end of switch

    
    
}//end of void calc fsm
