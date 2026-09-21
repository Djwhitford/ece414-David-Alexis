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

        sw1 = debounce_sw1_pressed();
        sw2 = debounce_sw2_pressed();

       // printf("RAW: SW1=%d SW2=%d\n", sw_in_read1(), sw_in_read2());
        //sleep_ms(500);

        pong_FSM(sw1, sw2);
    }
}