/*
* Defining the functions in the pong FSM
*/
#include "pong_FSM.h"
#include "timer.h"
#include "led_out.h"

uint32_t ballMoveDelay = 300;
uint32_t last_move_time = 0;
int ballPosition = 0;


state_t current_state = SERVE_LEFT;


void pong_FSM(bool button1, bool button2){
    uint32_t current_time = timer_read(); 
    switch(current_state) {
        case SERVE_LEFT:
            if(button1){
                current_state  = BALL_MOVING_RIGHT;
                last_move_time = current_time;
            }
            break;
        case SERVE_RIGHT:
            if(button2){
                current_state  = BALL_MOVING_LEFT;
                last_move_time = current_time;
            }
            break;
        case BALL_MOVING_LEFT:
            if (timer_elapsed_ms(last_move_time, current_time) >= ballMoveDelay){
                last_move_time = current_time;
                if(ballPosition > 0){
                    ballPosition--; // move the ball to the left
                } else if((ballPosition == 0)&&(button1 == true)){
                    current_state = BALL_MOVING_RIGHT; // ball reached the left edge
                    if(ballMoveDelay > 100){
                        ballMoveDelay -= 25; // increase the speed of the ball
                    }
                } else if((ballPosition == 0)&&(button1 == false)){
                    current_state = FLASH_WINNER; // ball reached the left edge and button1 is not pressed
                }
            }
            break;
        case BALL_MOVING_RIGHT:
            if (button2) {
                if(ballPosition == 7){
                    current_state = BALL_MOVING_LEFT; // ball reached the right edge
                    if (ballMoveDelay > 100) {
                        ballMoveDelay -= 25;
                    }
                } else {
                    current_state = FLASH_WINNER; // Right player pressed too early
                }
            } else if (timer_elapsed_ms(last_move_time, current_time) >= ballMoveDelay) {
                last_move_time = current_time;
                if(ballPosition < 7){
                    ballPosition++; // move the ball to the right
                } else {
                    current_state = FLASH_WINNER; // ball reached the right edge
                }
            }
            break;
        case FLASH_WINNER:

            break;
        default:
            break;
    } //end of switch

    led_out_write(1 << ballPosition);
}//end of void pong FSM