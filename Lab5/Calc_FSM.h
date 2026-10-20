#ifndef CALC_FSM_H
#define CALC_FSM_H

typedef enum {
    STATE_INIT,
    WAITING_FOROP1,
    WAITING_FOR_OPERATOR,
    WAITING_FOROP2,
    DISPLAY_RESULT,
    ERROR_STATE
} state_t;

void calc_FSM(int number1, int number2, char operator, char button);

#endif