#include "stdio.h"
#include "pico/stdlib.h"
#include "ts_lcd.h"
#include "ts_lcd.h"


int main()
{
    uint16_t x = 0;
    uint16_t y = 0;

    // Initialize the LCD
    tft_init_hw();
    tft_begin();

    // Set LCD to 320 x 240
    tft_gfx_setRotation(1);

    // Initialize touchscreen
    ts_lcd_init();

    // Clear the screen
    tft_fillScreen(ILI9340_BLACK);

    // Set text settings
    tft_setTextSize(2);
    tft_setTextColor2(ILI9340_WHITE, ILI9340_BLACK);
    tft_setTextWrap(1);

    while (true)
    {
        // Check if the touchscreen is being pressed
        if (get_ts_lcd(&x, &y))
        {
            // Display the coordinates
            tft_setCursor(10, 10);
            printf("X: %d  Y: %d\n", x, y);

            // Draw the 10 x 10 crosshair
            tft_fillRect(
                x - CROSSHAIR_SIZE / 2,
                y - CROSSHAIR_SIZE / 2,
                CROSSHAIR_SIZE,
                CROSSHAIR_SIZE,
                ILI9340_RED
            );
        }

        sleep_ms(50);
    }

    return 0;
}