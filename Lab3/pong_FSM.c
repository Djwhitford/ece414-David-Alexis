/*
* Defining the functions in the pong FSM
*/
#include "pong_FSM.h"
#include "timer.h"
#include "led_out.h"
#include <stdio.h>

uint32_t ballMoveDelay = 300;
uint32_t last_move_time = 0;
uint32_t last_flash_time = 0;
int ballPosition = 0;
int winner = 0; // 1 = left player, 2 = right player
int flashCount = 0;
bool flashOn = false;
bool leftServe = false;

state_t current_state = STATE_INIT;


void pong_FSM(bool *button1, bool *button2){ //taking pointer to buttons for the latches
    uint32_t current_time = timer_read(); 
    switch(current_state) {
        case STATE_INIT:
            *button1 = false; // Reset latch
            *button2 = false; // Reset latch
            winner = 0;
            flashCount = 0;
            ballMoveDelay = 300;
            flashOn = false;
            leftServe = !leftServe; // Alternate serve between left and right
            if(leftServe){
                ballPosition = 0;
                current_state = SERVE_LEFT;
                printf("Left player serves\n");
            } else {
                ballPosition = 7;
                current_state = SERVE_RIGHT;
                printf("Right player serves\n");
            }
            break;
        case SERVE_LEFT:
            if(*button1){
                *button1 = false; // Reset latch
                current_state  = BALL_MOVING_RIGHT;
                last_move_time = current_time;
            } else if(*button2){
                *button2 = false; // Reset latch
                current_state  = FLASH_WINNER; // Right player pressed too early
                last_flash_time = current_time;
                winner = 1; // Left player wins
                printf("Right Player Loses\n");
            }
            break;
        case SERVE_RIGHT:
            if(*button2){
                *button2 = false; // Reset latch
                current_state  = BALL_MOVING_LEFT;
                last_move_time = current_time;
            } else if(*button1){
                *button1 = false; // Reset latch
                current_state  = FLASH_WINNER; // Left player pressed too early
                last_flash_time = current_time;
                winner = 2; // Right player wins
                printf("Left Player Loses\n");
            }
            break;
        case BALL_MOVING_LEFT:
            if (*button1) {
                *button1 = false; // Reset latch
                if(ballPosition == 0){ //HIT
                    current_state = BALL_MOVING_RIGHT; // ball reached the left edge
                    if (ballMoveDelay > 100) {
                        ballMoveDelay -= 25;
                    }
                    last_move_time = current_time;
                } else {
                    current_state = FLASH_WINNER; // Left player pressed too early
                    last_flash_time = current_time;
                    winner = 2; // Right player wins
                    printf("Left Player Loses\n");
                }
            } else if (timer_elapsed_ms(last_move_time, current_time) >= ballMoveDelay) {
                last_move_time = current_time;
                if(ballPosition > 0){
                    ballPosition--; // move the ball to the left
                } else {
                    winner = 2; // Right player wins
                    current_state = FLASH_WINNER; // ball reached the left edge
                    last_flash_time = current_time;
                    printf("Left player loses\n");
                }
            }
            break;
        case BALL_MOVING_RIGHT:
            if (*button2) {
                *button2 = false; // Reset latch
                if(ballPosition == 7){ //HIT
                    current_state = BALL_MOVING_LEFT; // ball reached the right edge
                    if (ballMoveDelay > 100) {
                        ballMoveDelay -= 25;
                    }
                    last_move_time = current_time;
                } else {
                    winner = 1; // Left player wins
                    printf("Right player loses\n");
                    current_state = FLASH_WINNER; // Right player pressed too early
                    last_flash_time = current_time;
                }
            } else if (timer_elapsed_ms(last_move_time, current_time) >= ballMoveDelay) {
                last_move_time = current_time;
                if(ballPosition < 7){
                    ballPosition++; // move the ball to the right
                } else {
                    winner = 1; // Left player wins
                    printf("Right player loses\n");
                    current_state = FLASH_WINNER; // ball reached the right edge
                    last_flash_time = current_time;
                }
            }
            break;
        case FLASH_WINNER:
            if (flashCount < 3){
                if (timer_elapsed_ms(last_flash_time, current_time) >= 200) {
                    last_flash_time = current_time;
                    flashOn = !flashOn;
                    if (!flashOn) {
                        flashCount++;
                    }
                }
            } else {
                flashOn = false;
                current_state = STATE_INIT; // Reset the game after flashing
            }

            if(flashOn){
                if(winner == 1){
                    led_out_write(0x01); // Left player wins
                } else {
                    led_out_write(0x80); // Right player wins
                }
            } else {
                led_out_write(0x00); // Turn off all LEDs when not flashing
            }

            break;
        default:
            break;
    } //end of switch

    if(current_state != FLASH_WINNER){ // normal 
        led_out_write(1 << ballPosition);
    }
}//end of void pong FSM