/*
This is the header file for the Calc_FSM.c file. It contains the function prototypes for the functions in that file.
* Authors Alexis and David
*/
#include <stdint.h>

#ifndef CALC_FSM_H
#define CALC_FSM_H

#include "pico/stdlib.h"

 typedef enum{STATE_INIT, WAITING_FOROP1, WAITING_FOROP2,  WAITING_FOR_OPERATOR, DISPLAY_RESULT, ERROR_STATE } state_t;

 void calc_FSM(int number1, int number2, char operator);

#endif