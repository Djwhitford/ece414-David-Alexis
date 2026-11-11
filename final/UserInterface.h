/*
* H file for the user interface of the timer.
*Authors Alexis and Davidd
*/
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <stdint.h>

//Updates the bottom display screen
void displayStartingScreen(void);
void displayRunningScreen(void);
void displayRunningTime(uint32_t elapsedTime);
void displayStoppedScreen(void);
void displayResultsScreen(void);

int getTouch(void); 

#endif // USER_INTERFACE_H

