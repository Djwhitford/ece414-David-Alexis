#ifndef DISPLAY_FSM_H
#define DISPLAY_FSM_H

#include <stdbool.h>

typedef enum {
    STATE_INIT,
    STARTING_SCREEN,
    RUNNING_SCREEN,
    STOPPED_SCREEN,
    RESULTS_SCREEN,
} screen_t;

void display_FSM(int screen);
void setBreakbeamActivated(bool activated);

#endif