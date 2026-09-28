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

/**sort samples, for oversampling */
#if (NUMSAMPLES > 2)
static void insert_sort(int array[], uint8_t size)
{
  uint8_t j;
  int s; // was save

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
bool get_ts_lcd(unit16_t * px, uint16_t * py)
{
    int x = 0;
    int y = 0;
    int z = 0;

    int samples[NUMSAMPLES];

    uint8_t i;
    unit8_t valid = 1;

    /**reads X position 
    *Y- is an input
    *Y+ is the ADC input
    *XP is drien HIGH
    *XM is driven LOW
    */
    gpio_init(YMbit);
    gpio_set_dir(YMbit, false);

    adc_dpio_init(YPbit);
    adc_select_input(YPchan);

    gpio_init(XPbit);
    gpio_set_dir(XPbit, true);
    gpio_put(XPbit, 1);

    gpio_init(XMbit);
    gpio_set_dir(XMbit, true);
    gpio_put(XPbit, 0);

    for(i = 0; i < NUMSAMPLES; i++){
        samples[i] = adc_read();
    }

    #if NUMSAMPLES > 2
        insert_sort(samples, NUMSAMPLES)
    #endif

    #if NUMSAMPLES == 2
    

}