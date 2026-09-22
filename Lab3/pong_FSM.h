/* 
 * File:   pong_FSM.h
 *
 * The header file for the pong FSM
 */
#ifndef PONG_FSM_H
#define PONG_FSM_H

#include "pico/stdlib.h"

 typedef enum{STATE_INIT, SERVE_RIGHT, SERVE_LEFT, BALL_MOVING_RIGHT, BALL_MOVING_LEFT, FLASH_WINNER } state_t;

 void pong_FSM(bool *button1, bool *button2); 

#endif
 