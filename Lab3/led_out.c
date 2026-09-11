#include "led_out.h"
#include "pico/stdlib.h"

void led_out_init() {
    uint32_t mask = 0xFF << 2;

    gpio_init_mask(mask);
    gpio_set_dir_out_masked(mask);
}

void led_out_write(uint8_t val) {
    gpio_put_masked(0xFF << 2, ((uint32_t)val) << 2);
}