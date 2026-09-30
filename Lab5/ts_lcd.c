#include "stdio.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "ts_lcd.h"

/**number of samples to reduce touchscreen  */
#define NUMSAMPLES 3

/** LCD dimensions */
#define LCD_WIDTH 320
#define LCD_HEIGHT 240

#define X_MIN 200
#define X_MAX 3900
#define Y_MIN 200
#define Y_MAX 3900

/**sort samples, for oversampling */
#if (NUMSAMPLES > 2)
static void insert_sort(int array[], uint8_t size)
{
    uint8_t j;
    int s;

    int i;
    for (i = 1; i < size; i++)
    {
        s = array[i];
        for (j = i; j >= 1 && s < array[j - 1]; j--)
            array[j] = array[j - 1];

        array[j] = s;
    }
}
#endif

/*initialize the touchscreen */
void ts_lcd_init(void)
{
    adc_init();

    /*initalize the two pins used as inputs*/
    adc_gpio_init(XMbit);
    adc_gpio_init(YPbit);

    /**initalize the touchscreen pins */
    gpio_init(XPbit);
    gpio_init(XMbit);
    gpio_init(YPbit);
    gpio_init(YMbit);
}

/** reads the touchscreen */
bool get_ts_lcd(uint16_t *px, uint16_t *py)
{
    int x = 0;
    int y = 0;
    int z = 0;

    int samples[NUMSAMPLES];

    uint8_t i;
    uint8_t valid = 1;

    /**reads X position
    *Y- is an input
    *Y+ is the ADC input
    *XP is drien HIGH
    *XM is driven LOW
    */
    gpio_init(YMbit);
    gpio_set_dir(YMbit, false);

    adc_gpio_init(YPbit);
    adc_select_input(YPchan);

    gpio_init(XPbit);
    gpio_set_dir(XPbit, true);
    gpio_put(XPbit, 1);

    gpio_init(XMbit);
    gpio_set_dir(XMbit, true);
    gpio_put(XMbit, 0);

    for (i = 0; i < NUMSAMPLES; i++)
    {
        samples[i] = adc_read();
    }

#if NUMSAMPLES > 2
    insert_sort(samples, NUMSAMPLES);
#endif

#if NUMSAMPLES == 2
    x = (samples[0] + samples[1]) / 2;
#else
    x = samples[NUMSAMPLES / 2];
#endif

    /**reads Y position */
    gpio_init(XPbit);
    gpio_set_dir(XPbit, false);

    adc_gpio_init(XMbit);
    adc_select_input(XMchan);

    gpio_init(YPbit);
    gpio_set_dir(YPbit, true);
    gpio_put(YPbit, 1);

    gpio_init(YMbit);
    gpio_set_dir(YMbit, true);
    gpio_put(YMbit, 0);

    for (i = 0; i < NUMSAMPLES; i++)
    {
        samples[i] = adc_read();
    }

#if NUMSAMPLES > 2
    insert_sort(samples, NUMSAMPLES);
#endif

#if NUMSAMPLES == 2
    y = (samples[0] + samples[1]) / 2;
#else
    y = samples[NUMSAMPLES / 2];
#endif

    
    gpio_init(XPbit);
    gpio_set_dir(XPbit, true);
    gpio_put(XPbit, 0);

    gpio_init(YMbit);
    gpio_set_dir(YMbit, true);
    gpio_put(YMbit, 1);

    adc_gpio_init(XMbit);
    adc_select_input(XMchan);

    sleep_us(10);

    z = adc_read();

    if (z <= 50 || z >= 4050)
    {
        valid = 0;
    }

    if (!valid)
    {
        return false;
    }

    if (x < X_MIN)
        x = X_MIN;

    if (x > X_MAX)
        x = X_MAX;

    if (y < Y_MIN)
        y = Y_MIN;

    if (y > Y_MAX)
        y = Y_MAX;

    uint16_t old_px = (uint16_t)(((x - X_MIN) * (LCD_WIDTH - 1)) / (X_MAX - X_MIN));
    uint16_t old_py = (uint16_t)(((y - Y_MIN) * (LCD_HEIGHT - 1)) / (Y_MAX - Y_MIN));

    int screen_x = old_py;
    int screen_y = (LCD_HEIGHT - 1) - old_px;

    screen_x = (screen_x - 24) * 319 / (206 - 24);
    screen_y = (screen_y - 5) * 239 / (198 - 5);

    if (screen_x < 0)
        screen_x = 0;
    if (screen_x > 319)
        screen_x = 319;

    if (screen_y < 0)
        screen_y = 0;
    if (screen_y > 239)
        screen_y = 239;

    *px = (uint16_t)screen_x;
    *py = (uint16_t)screen_y;

    return true;
}