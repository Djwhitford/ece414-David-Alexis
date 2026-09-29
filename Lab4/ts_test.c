#include "stdio.h"
#include "pico/stdlib.h"
#include "ts_lcd.h"
#include "TFTMaster.h"

#define CROSSHAIR_SIZE 10

int main()
{
    uint16_t x = 0;
    uint16_t y = 0;

    char coord_text[40];

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
            // Clear old coordinate text
            tft_fillRect(0, 0, 320, 25, ILI9340_BLACK);

            // Display the coordinates
            snprintf(coord_text, sizeof(coord_text),
                     "X: %u  Y: %u", x, y);

            tft_setCursor(10, 5);
            tft_writeString(coord_text);

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