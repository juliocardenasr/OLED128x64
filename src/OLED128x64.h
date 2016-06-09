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
#ifndef OLED128x64_h
#define OLED128x64_h

class OLED128x64 {
    public:
        //constructor
        OLED128x64(unsigned char pSDA, unsigned char pSCL, unsigned char AddressOLED);
        
        //display a character a x row an y column  
        void sendCharXY(unsigned char data, int X, int Y); 
        
        // Clear the display
        void clearDisplay(void);
        
        // turn Off the display 
        void displayOff(void);

        // turn On the display
        void displayOn(void); 

        // turn off, clear and turn On the display
        void resetDisplay(void);

        //Puts a static string to X row Y Column
        void sendStrXY( const char *string, int X, int Y);

        // Send a String  to X row Y Column
        void sendStringXY(String msg, int X, int Y);
        
        //init the chip SDD1306
        void initOLED(void);

    private:
        //Send commands to chip SDD1306
        void sendCommand(unsigned char Command);
        
        //Set the pointer in a row page and col 
        void setXY(unsigned char row, unsigned char col);

        // Send a character to the chip
        void sendChar(unsigned char character); 
        
        unsigned char pinSDA;
        unsigned char pinSCL;
        unsigned char oledAddress;
};
#endif
