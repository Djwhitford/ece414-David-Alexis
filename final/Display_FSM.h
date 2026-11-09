#ifndef DISPLAY_FSM_H
#define DISPLAY_FSM_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    STATE_INIT,
    STARTING_SCREEN,
    RUNNING_SCREEN,
    STOPPED_SCREEN,
    RESULTS_SCREEN,
} screen_t;

void display_FSM(int screen, uint32_t elapsedTime);
void setBreakbeamActivated(bool activated);

#endif