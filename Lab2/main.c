#include <stdio.h>
#include "pico/stdlib.h"
#include "led_out.h"
#include "sw_in.h"

int main() {
    bool sw1, sw2;

   stdio_init_all();
    led_out_init();
    sw_in_init();

    while (true) {
        s1 = sw_in_read1();
        sw2 = sw_in_read2();

        if(s1 && s2) {
            led_out_write(0xFF);
        } else if(s1&& !s2) {
            led_out_write(0x01);
        } else if(!s1 && s2) {
            led_out_write(0x80);
        } else {
            led_out_write(0x00);
        }
        sleep_ms(10);
    }
}