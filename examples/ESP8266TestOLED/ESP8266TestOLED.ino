/*
******************************************************************************** 
* Program   : ESP8266TestOLED
* Objective : Test the display OLED 128 x 64 from the ESP8266 microcontroller
* Author    : Julio Cardenas  juliocardenasr@gmail.com
* Date      : jun 9 2016
* ******************************************************************************
*/
#include <OLED128x64.h>
#define PinSDA 0
#define PinSCL 2 
#define OLED_address 0x3c

OLED128x64 Display(PinSDA, PinSCL, OLED_address);

void setup() {
    Serial.begin(115200);
    Serial.println(".");
    delay(500);
    Serial.println("..");
    delay(500);
    Serial.println("...");
    delay(500);
    Serial.println("....");
    delay(500);
    Serial.println(".....");
    delay(500);
    Serial.println("......");
    delay(500);
    Serial.println(".......");
    delay(500);
    
    Serial.println("1. Serial Port Activated ......... ok");
    delay(2000);
    Display.initOLED();
}

void loop() {
    Display.sendStrXY("Line 0 .",0,0);
    delay(500);
    Display.sendStrXY("Line 1 ..",1,0);
    delay(500);
    Display.sendStrXY("Line 2 ...",2,0);
    delay(500);
    Display.sendStrXY("Line 3 ....",3,0);
    delay(500);
    Display.sendStrXY("Line 4 .....",4,0);
    delay(500);
    Display.sendStrXY("Line 5 ......",5,0);
    delay(500);
    Display.sendStrXY("Line 6 .......",6,0);
    delay(500);
    Display.sendStrXY("Line 7 ........",7,0);
    delay(500);
    Display.clearDisplay(); 
    Serial.println("LoopCompleted"); 
}
