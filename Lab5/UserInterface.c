/*
* C file for the user interface of the calculator. This file contains the functions for getting button presses and updating the display.
* David and Alexis
*/

//Returns which button (if any) was pressed.
int getButton(){

}

//Updates the top display screen
void displayResult(int32_t value){

}

//Updates the bottom display screen
void displayButtons(){
   tft_fillScreen(ILI9340_BLACK); //Calculator background color

   tft_fillRect(10, 45, 60, 40, WHITE); //7
    tft_fillRect(80, 45, 60, 40, WHITE); //8
    tft_fillRect(150, 45, 60, 40, WHITE); //9
    tft_fillRect(220, 45, 60, 40, GREEN); //+
   
    tft_fillRect(10, 95, 60, 40, WHITE); //4
    tft_fillRect(80, 95, 60, 40, WHITE); //5
    tft_fillRect(150, 95, 60, 40, WHITE); //6
    tft_fillRect(220, 95, 60, 40, GREEN);  //-

    tft_fillRect(10, 145, 60, 40, WHITE);   //1
    tft_fillRect(80, 145, 60, 40, WHITE);   //2
    tft_fillRect(150, 145, 60, 40, WHITE);  //3
    tft_fillRect(220, 145, 60, 40, GREEN);  //*

    tft_fillRect(10, 210, 60, 40, WHITE); //0
    tft_fillRect(150, 210, 60, 40, RED); //C
    tft_fillRect(80, 210, 60, 40, BLUE); //=
    tft_fillRect(220, 210, 60, 40, GREEN); // /
}

//Updates the top display screen with an error message
void displayError(){

}

