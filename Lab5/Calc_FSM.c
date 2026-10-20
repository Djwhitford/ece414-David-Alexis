/*
*Authors Alexis and David*
* C file for the user interface of the calculator. This file contains the functions for getting button presses and updating the display.
*/
#include "Calc_FSM.h"
#include <stdio.h>

//declare variables

state_t current_state = STATE_INIT;
static int saved_number1 = 0;
static int saved_number2 = 0;
static char saved_operator = '\0';

static void calculateResult();

void calc_FSM(int number1, int number2, char operator, char button){
    
    // Check if clear
    if(button == 'C'){
        current_state = STATE_INIT;
    }
    
    switch(current_state) {
        case STATE_INIT:
            saved_number1 = 0;
            saved_number2 = 0;
            saved_operator = '\0';

            displayResult(0);

            current_state = WAITING_FOROP1;
            break;
        case WAITING_FOROP1:
             // Is button pressed
            if(button >= '0' && button <= '9'){

                int digit = button - '0';

                saved_number1 = saved_number1 * 10 + digit;

                displayResult(saved_number1);
            }

            // Is operator pressed
            if(button == '+' || button == '-' ||
            button == '*' || button == '/'){

                saved_operator = button;
                current_state = WAITING_FOR_OPERATOR;
            }
            break;
        
        case WAITING_FOR_OPERATOR:
            // Wait for first digit of second number
            if(button >= '0' && button <= '9'){
                saved_number2 = button - '0';
                displayResult(saved_number2);
                current_state = WAITING_FOROP2;
            }
            break;
              
        case WAITING_FOROP2:
            // Build second number
            if(button >= '0' && button <= '9'){
                int digit = button - '0';
                saved_number2 = saved_number2 * 10 + digit;
                displayResult(saved_number2);
            }
            else if(button == '='){
                current_state = DISPLAY_RESULT;
                calculateResult();
            }
            break;


        case DISPLAY_RESULT:
            // Wait until C is pressed
            break;
        case ERROR_STATE:
            // Stay in error until C pressed
            break;
        
        default:
            break;
    } //end of switch

    
    
}//end of void calc fsm

static void calculateResult(){ //helper function
    if(saved_operator == '+'){
        displayResult(saved_number1 + saved_number2);
    }
    else if(saved_operator == '-'){
        displayResult(saved_number1 - saved_number2);
    }
    else if(saved_operator == '*'){
        displayResult(saved_number1 * saved_number2);
    }
    else if(saved_operator == '/'){
        if(saved_number2 != 0){
            displayResult(saved_number1 / saved_number2);
        }
        else {
            current_state = ERROR_STATE;
            displayError();
        }
    }
}