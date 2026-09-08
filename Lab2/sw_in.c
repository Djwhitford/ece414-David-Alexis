#include "sw_in.h"
#include "pico/stdlib.h"

void sw_in_init() {
    gpio_init(16);
    gpio_set_dir(16, GPIO_IN);
    gpio_pull_up(16);

    gpio_init(17);
    gpio_set_dir(17, GPIO_IN);
    gpio_pull_up(17);
}

bool sw_in_read1() {
    return !gpio_get(16);
}

bool sw_in_read2() {
    return !gpio_get(17);
}