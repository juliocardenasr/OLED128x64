/*
**************************************************************************************************************
* Library : OLED128x64
* version : 1.1.0
* Objetive: Manage the display OLED 128x64
*           based on the chip SDD1306
*           Allow use any pins SDA an SCL on the interface I2C
*           Allow the use use the small font to provide a screen of 8 rows an 16 columns
* Author  : Julio Cardenas   juliocardenasr@gmail.com
* Date    : jun 9 2016 
*
* This library is free software; you can redistribute it and/or modify it under the terms of the GNU 
* Lesser General Public License as published by the Free Software Foundation; either version 2.1 of 
* the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
* the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General 
* Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License along with this library; if not, 
* write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*
*
************************************************************************************************************
*/
#include "Arduino.h"
#include "OLED128x64.h"
#include "font.h"
#include "Wire.h"
#define offset 0

//constructor
OLED128x64::OLED128x64(unsigned char pSDA, unsigned char pSCL, unsigned char oledAddress){
    this->pinSDA = pSDA;
    this->pinSCL = pSCL;
    this->oledAddress = oledAddress;
}

void OLED128x64::sendCommand(unsigned char Command){
    Wire.beginTransmission(this->oledAddress);     
    Wire.write(0x80);                         
    Wire.write(Command);
    Wire.endTransmission();                   
}

void OLED128x64::setXY(unsigned char row, unsigned char col) {
    sendCommand(0xb0 + row);                      //set page address
    sendCommand(offset + (8 * col & 0x0f));       //set low col address
    sendCommand(0x10 + ((8 * col >>4) & 0x0f));   //set high col address
}

void OLED128x64::sendChar(unsigned char character) 
{ 
    Wire.beginTransmission(this->oledAddress); 
    Wire.write(0x40);
    Wire.write(character);
    Wire.endTransmission();  
}

void OLED128x64::sendCharXY(unsigned char data, int X, int Y) {
    setXY(X, Y);
    Wire.beginTransmission(this->oledAddress); 
    Wire.write(0x40);
    for (int i = 0; i < 8; i++) Wire.write(pgm_read_byte(myFont[data-0x20] + i ));
    Wire.endTransmission(); 
}

void OLED128x64::clearDisplay(void) {
    unsigned char i, k;
    for (k = 0; k < 8; k++) {  
        setXY(k,0);    
        for (i = 0; i < (128 + 2 * offset); i++) {
            sendChar(0);
        }
    }
}

void OLED128x64::displayOff(void) {
  sendCommand(0xae);    
}

void OLED128x64::displayOn(void) {
    sendCommand(0xaf);        
}

void OLED128x64::resetDisplay(void) {
    displayOff();
    clearDisplay();
    displayOn();
}


void OLED128x64::sendStrXY( const char *string, int X, int Y) {
    unsigned char i=0;
    setXY(X,Y);
    while (*string) {
        for (i = 0; i < 8; i++) {
            sendChar(pgm_read_byte(myFont[*string-0x20]+i));
        }
        *string++;
    }
}


void OLED128x64::sendStringXY(String msg, int X, int Y){
    unsigned char i;
    char c;
    setXY(X,Y);
    for (i = 0; i < msg.length(); i++) {
        c = msg.charAt(i);
        sendCharXY(c, X, Y+i);
    }
} 


void OLED128x64::initOLED(void) {
    Wire.begin(this->pinSDA,this->pinSCL);

    sendCommand(0xae);            //display off
    sendCommand(0xa6);            //Set Normal Display (default)
    
    // Adafruit Init sequence for 128x64 OLED module
    sendCommand(0xAE);            //DISPLAYOFF
    sendCommand(0xD5);            //SETDISPLAYCLOCKDIV
    sendCommand(0x80);            // the suggested ratio 0x80
    sendCommand(0xA8);            //SSD1306_SETMULTIPLEX
    sendCommand(0x3F);
    sendCommand(0xD3);            //SETDISPLAYOFFSET
    sendCommand(0x0);             //no offset
    sendCommand(0x40 | 0x0);      //SETSTARTLINE
    sendCommand(0x8D);            //CHARGEPUMP
    sendCommand(0x14);
    sendCommand(0x20);            //MEMORYMODE
    sendCommand(0x00);            //0x0 act like ks0108
    
    //sendCommand(0xA0 | 0x1);    //SEGREMAP   //Rotate screen 180 deg
    sendCommand(0xA0);
    
    //sendCommand(0xC8);          //COMSCANDEC  Rotate screen 180 Deg
    sendCommand(0xC0);
    
    sendCommand(0xDA);            //0xDA
    sendCommand(0x12);            //COMSCANDEC
    sendCommand(0x81);            //SETCONTRAS
    sendCommand(0xCF);            //
    sendCommand(0xd9);            //SETPRECHARGE 
    sendCommand(0xF1); 
    sendCommand(0xDB);            //SETVCOMDETECT                
    sendCommand(0x40);
    sendCommand(0xA4);            //DISPLAYALLON_RESUME        
    sendCommand(0xA6);            //NORMALDISPLAY             

    clearDisplay();
    sendCommand(0x2e);            // stop scroll
    //----------------------------REVERSE comments----------------------------//
    sendCommand(0xa0);            //seg re-map 0->127(default)
    sendCommand(0xa1);            //seg re-map 127->0
    sendCommand(0xc8);
    delay(1000);
    //----------------------------REVERSE comments----------------------------//
    // sendCommand(0xa7);         //Set Inverse Display  
    // sendCommand(0xae);         //display off
    sendCommand(0x20);            //Set Memory Addressing Mode
    sendCommand(0x00);            //Set Memory Addressing Mode ab Horizontal addressing mode
    //  sendCommand(0x02);        // Set Memory Addressing Mode ab Page addressing mode(RESET)  
    resetDisplay();
}



