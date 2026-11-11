/*
* C file for the user interface of the calculator. This file contains the functions for getting button presses and updating the display.
* David and Alexis
*/
#include <stdio.h>
#include <stdbool.h>
#include "ts_lcd.h"
#include <stdint.h>
#include "TFTMaster.h"
#include "userInterface.h"
#include "TouchScreen.h"
#include "timer.h"
#include "Display_FSM.h" 



// toushcreen calibration, to be changed later
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 850
#define TS_MAXY 910

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

//Updates the bottom display screen
void displayStartingScreen(){
   tft_fillScreen(ILI9340_YELLOW); //Starting screen background color
   tft_setTextSize(5);
   tft_setTextColor(ILI9340_WHITE);
   tft_setCursor(40, 100); tft_writeString("00:00.00");
} //end of displayStartingScreen

void displayRunningScreen(void) {
   tft_fillScreen(ILI9340_GREEN); //Running screen background color
   tft_setTextSize(5);
   tft_setTextColor2(ILI9340_WHITE, ILI9340_GREEN);
}

void displayRunningTime(uint32_t elapsedTime) {
   char timeText[16];
   timer_format_time(elapsedTime, timeText, sizeof(timeText));
   tft_setTextSize(5);
   tft_setTextColor2(ILI9340_WHITE, ILI9340_GREEN);
   tft_setCursor(40, 100);
   tft_writeString(timeText);
}//end of displayRunningScreen

void displayStoppedScreen(){ //needs stopped timer
   tft_fillScreen(ILI9340_RED); //Stopped screen background color
   tft_setTextSize(5);
   tft_setTextColor(ILI9340_WHITE);
   tft_setCursor(40, 100); tft_writeString("00:00.10");
}//end of displayStoppedScreen

void displayResultsScreen(){ //needs stopped timer and calculations
   tft_fillScreen(ILI9340_RED); //Results screen background color
   tft_setTextSize(5);
   tft_setTextColor(ILI9340_WHITE);
   tft_setCursor(40, 20); tft_writeString("00:00.10");

   tft_setTextSize(2);
   tft_setCursor(10, 100); tft_writeString("Average Speed: 00.00 m/s");
   tft_setCursor(10, 140); tft_writeString("Distance: 00.00 m");
}//end of displayResultsScreen

int getTouch() {
    static bool ready = false;
    static bool wasPressed = false;

    uint16_t x = 0;
    uint16_t y = 0;

    bool touching = get_ts_lcd(&x, &y);

    // Wait for touchscreen to be released
    if (!touching) {
        wasPressed = false;
        ready = true;
        return -1;
    }

    // Ignore startup touches and repeated presses
    if (!ready || wasPressed) {
        return -1;
    }

    wasPressed = true;

    return -1;
}



