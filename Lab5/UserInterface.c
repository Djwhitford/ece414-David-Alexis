/*
* C file for the user interface of the calculator. This file contains the functions for getting button presses and updating the display.
* David and Alexis
*/
#include <stdio.h>
#include <stdint.h>
#include "TFTMaster.h"
#include "userInterface.h"
#include "TouchScreen.h"

// toushcreen calibration, to be changed later
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 850
#define TS_MAXY 910

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

//button struct, that containts a vuttons location, size, and value
typedef struct {
   int x;
   int y;
   int w;
   int h;
   int label;
} Button;

//button array
static const Button buttons[16] = {
    // Row 1
    {10,  45, 60, 40, '7'},
    {80,  45, 60, 40, '8'},
    {150, 45, 60, 40, '9'},
    {220, 45, 60, 40, '+'},

    // Row 2
    {10,  95, 60, 40, '4'},
    {80,  95, 60, 40, '5'},
    {150, 95, 60, 40, '6'},
    {220, 95, 60, 40, '-'},

    // Row 3
    {10,  145, 60, 40, '1'},
    {80,  145, 60, 40, '2'},
    {150, 145, 60, 40, '3'},
    {220, 145, 60, 40, '*'},

    // Row 4
    {10,  195, 60, 40, '0'},
    {80,  195, 60, 40, 'C'},
    {150, 195, 60, 40, '='},
    {220, 195, 60, 40, '/'}
};

//Returns which button (if any) was pressed.
int getButton(){
   struct TSPoint p;
   getPoint(&p);

   if (p.z > 0) {
      int pixelX = (p.x - TS_MINX) * SCREEN_WIDTH / (TS_MAXX - TS_MINX);
      int pixelY = (p.y - TS_MINY) * SCREEN_HEIGHT / (TS_MAXY - TS_MINY);

      // Check which button area was touched
      for (int i = 0; i < 16; i++) {
         if (pixelX >= buttons[i].x && pixelX <= (buttons[i].x + buttons[i].w) &&
               pixelY >= buttons[i].y && pixelY <= (buttons[i].y + buttons[i].h)) {
               return buttons[i].label; // Return character value ('0'-'9', '+', '-', '*', '/', '=', 'C')
         }
      }
   }

    return -1;
}

//Updates the top display screen
void displayResult(int32_t value){
   tft_fillRect(10, 5, 300, 35, ILI9340_BLACK);
   
   char buffer[16];
   snprintf(buffer, sizeof(buffer), "%ld", (long)value);
   
   tft_setTextColor(ILI9340_WHITE);
   tft_setTextSize(3);
   tft_setCursor(20, 10);
   tft_writeString(buffer);
}

//Updates the bottom display screen
void displayButtons(){
   tft_fillScreen(ILI9340_BLACK); //Calculator background color

   tft_fillRect(10, 45, 60, 40, ILI9340_WHITE); //7
    tft_fillRect(80, 45, 60, 40, ILI9340_WHITE); //8
    tft_fillRect(150, 45, 60, 40, ILI9340_WHITE); //9
    tft_fillRect(220, 45, 60, 40, ILI9340_GREEN); //+
   
    tft_fillRect(10, 95, 60, 40, ILI9340_WHITE); //4
    tft_fillRect(80, 95, 60, 40, ILI9340_WHITE); //5
    tft_fillRect(150, 95, 60, 40, ILI9340_WHITE); //6
    tft_fillRect(220, 95, 60, 40, ILI9340_GREEN);  //-

    tft_fillRect(10, 145, 60, 40, ILI9340_WHITE);   //1
    tft_fillRect(80, 145, 60, 40, ILI9340_WHITE);   //2
    tft_fillRect(150, 145, 60, 40, ILI9340_WHITE);  //3
    tft_fillRect(220, 145, 60, 40, ILI9340_GREEN);  //*

    tft_fillRect(10, 195, 60, 40, ILI9340_WHITE); //0
    tft_fillRect(150, 195, 60, 40, ILI9340_RED); //C
    tft_fillRect(80, 195, 60, 40, ILI9340_BLUE); //=
    tft_fillRect(220, 195, 60, 40, ILI9340_GREEN); // /

   tft_setTextSize(3);
   tft_setTextColor(ILI9340_BLACK);

   //first row labels
   tft_setCursor(32, 55);  tft_writeString("7");
   tft_setCursor(102, 55); tft_writeString("8");
   tft_setCursor(172, 55); tft_writeString("9");
   tft_setCursor(242, 55); tft_writeString("+");
   //second row labels
   tft_setCursor(32, 105);  tft_writeString("4");
   tft_setCursor(102, 105); tft_writeString("5");
   tft_setCursor(172, 105); tft_writeString("6");
   tft_setCursor(242, 105); tft_writeString("-"); 
   //third row labels
   tft_setCursor(32, 155);  tft_writeString("1");
   tft_setCursor(102, 155); tft_writeString("2");
   tft_setCursor(172, 155); tft_writeString("3");
   tft_setCursor(242, 155); tft_writeString("x");
   // row four labels
   tft_setCursor(32, 205);  tft_writeString("0");
   tft_setCursor(242, 205); tft_writeString("/");
   tft_setTextColor(ILI9340_WHITE);
   tft_setCursor(102, 205); tft_writeString("C");
   tft_setCursor(172, 205); tft_writeString("=");

   
   
}

//Updates the top display screen with an error message
void displayError(void){
   tft_fillRect(10, 5, 300, 35, ILI9340_BLACK);

   tft_setTextColor(ILI9340_RED);
   tft_setTextSize(3);
   tft_setCursor(20, 10);
   tft_writeString("ERROR");
}

