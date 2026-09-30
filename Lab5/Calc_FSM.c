/*
*Authors Alexis and David*
* C file for the user interface of the calculator. This file contains the functions for getting button presses and updating the display.
*/
#include "Calc_FSM.h"
#include <stdio.h>

//declare variables

state_t current_state = STATE_INIT;


void calc_FSM(int number1, int number2, char operator){
    switch(current_state) {
        case STATE_INIT:
            // Initialize variables and set the state to WAITING_FOROP1
            if(number1 != 0){
                current_state = WAITING_FOR_OPERATOR;
            }
            
        
        
            break;
        case WAITING_FOROP1:
            // Wait for the first operand to be entered
            if(number1 != 0){
                current_state = WAITING_FOR_OPERATOR;
            }
        
        
            break;
        case WAITING_FOR_OPERATOR:
            // Wait for the operator to be entered
            if(operator == '+' || operator == '-' || operator == '*' || operator == '/'){
                current_state = WAITING_FOROP2;
            }
        
        
            break;
        case WAITING_FOROP2:
            // Wait for the second operand to be entered
            if(number2 != 0){
                current_state = DISPLAY_RESULT;
            }
        
            break;
        case DISPLAY_RESULT:
            // Display the result of the calculation
            if(operator == '+'){
                displayResult(number1 + number2);
            } else if(operator == '-'){
                displayResult(number1 - number2);
            } else if(operator == '*'){
                displayResult(number1 * number2);
            } else if(operator == '/'){
                if(number2 != 0){
                    displayResult(number1 / number2);
                } else {
                    current_state = ERROR_STATE;
                }
            }
        
        
            break;
        case ERROR_STATE:
            // Handle any errors that occur during the calculation
            if(operator == '/' && number2 == 0){
                displayError();
            }
        
        
            break;
        
        default:
            break;
    } //end of switch

    
    
}//end of void calc fsm