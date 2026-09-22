#include <stdio.h>
#include "pico/stdlib.h"
#include "led_out.h"
#include "sw_in.h"
#include "pong_FSM.h"
#include "debounce_sw1.h"
#include "debounce_sw2.h"
#include "timer.h"


int main() {
    bool sw1, sw2;
    uint32_t last_debounce_time = 0;
    bool sw1_latched = false;
    bool sw2_latched = false;

    stdio_init_all();
    led_out_init();
    sw_in_init();
    debounce_sw1_init();
    debounce_sw2_init();

    while (true){
        uint32_t current_time = timer_read();
        if (timer_elapsed_ms(last_debounce_time, current_time) >= DEBOUNCE_PD_MS) {
            debounce_sw1_tick();
            debounce_sw2_tick();
            last_debounce_time = current_time;
            
        }   

        if(debounce_sw1_pressed()) {
            sw1_latched = true;
        }
        if(debounce_sw2_pressed()) {
            sw2_latched = true;
        }


        pong_FSM(&sw1_latched, &sw2_latched); //location of button in mem for latching

    }
}