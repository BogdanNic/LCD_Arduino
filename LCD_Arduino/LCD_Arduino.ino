///////////////
// Sketch: Calibrate - Calibrate TFT SPFD5408 Touch
// Author: Joao Lopes F. - joaolopesf@gmail.com
//
// Versions:
//    - 0.9.0  First beta - July 2015
//    - 0.9.1  Rotation for Mega 
// Comments: 
//    Show the calibration parameters to put in your code
//    Please use a small like the eraser on a pencil for best results
//
//    Code for buttons, based on Adafruit arduin_o_phone example
///////////////

// library SPFD5408 

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>     // Touch library

// Calibrates value
#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// MCUFRIEND UNO shield shares pins with the TFT.
//#define YP A1   //A3 for ILI9320
//#define YM 7    //9
//#define XM A2
//#define XP 6    //8 
#define YP A2 // must be an analog pin, use "An" notation!
#define XM A1 // must be an analog pin, use "An" notation!
#define YM 6 // can be a digital pin
#define XP 7 // can be a digital pin
/*
//Macros replaced by variables
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
*/
short TS_MINX=194;
short TS_MINY=99;

short TS_MAXX=173;
short TS_MAXY=858;

// Init TouchScreen:

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// LCD Pin

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4 // Optional : otherwise connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Init LCD

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;
// Dimensions

uint16_t width = 0;
uint16_t height = 0;

// Buttons

#define BUTTONS 3
#define BUTTON_CLEAR 0
#define BUTTON_SHOW 1
#define BUTTON_RESET 2

//Adafruit_GFX_Button buttons[BUTTONS];
Adafruit_GFX_Button on_btn, off_btn;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate

//240x320 ID=0x5408
void setup(void) {
  Serial.begin(9600);
  tft.begin(0x9325);
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.print("Temp");
  tft.drawRect(2,2,236,316,GREEN);

  //Print "Hello" Text
  tft.setCursor(100,30);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("Hello");
  
  //buttons
   on_btn.initButton(&tft,  60, 290, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
   off_btn.initButton(&tft, 180, 290, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
   on_btn.drawButton(false);
   off_btn.drawButton(false);
}



void loop(void) {
  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
     Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z);
  }
}
