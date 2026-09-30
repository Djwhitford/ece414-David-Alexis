/*
* H file for the user interface of the calculator. This file contains the function prototypes for getting button presses and updating the display.
*Authors Alexis and Davidd
*/

#include <stdint.h>

//Returns which button (if any) was pressed.
int getButton();

//Updates the top display screen
void displayResult(int32_t value);

//Updates the bottom display screen
void displayButtons();

//Updates the top display screen with an error message
void displayError();

