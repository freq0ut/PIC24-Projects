/* 
 * File:   Lab3_LCD_NameScroll.c
 * Author: Zachary
 * Lab 3:  LCD Scrolling Name Display
 * Created on September 10, 2015, 12:58 PM
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include "config.h"
#include "LCD.h"

/*DEFINITIONS*/

/*------------------GLOBAL VARIABLES------------------*/

/*------------------FUNCTION PROTOTYPES------------------*/

/*------------------INTERRUPT SERVICE ROUTINES------------------*/

/*------------------MAIN FUNCTION------------------*/
int main(void)
{  
    TRISBbits.TRISB2 = 0; // Used as Register Select for LCD
    initPMP();
    initLCD();
    
    setLCDG(0);
    putLCD(0b00000);
    putLCD(0b00000);
    putLCD(0b00000);
    putLCD(0b10001);
    putLCD(0b00100);
    putLCD(0b10001);
    putLCD(0b01110);
    putLCD(0);
    int i;
    int speed = 250;
    /*------------------INFINITE LOOP------------------*/
    while(1)
    {
        for(i=19;i>=0;i--)
        {
            setCursor(1,i);
            putLCD('Z');
            putLCD('a');
            putLCD('c');
            putLCD('k');
            putLCD(' ');
            delay_ms(speed);
        }
        
        for(i=19;i>=0;i--)
        {
            setCursor(2,i);
            putLCD('G');
            putLCD('o');
            putLCD('y');
            putLCD('e');
            putLCD('t');
            putLCD('c');
            putLCD('h');
            putLCD('e');
            putLCD(' ');
            putLCD(0);
            putLCD(' ');
            delay_ms(speed);
        }  
        
        delay_ms(3000);
        clearLCD();
    }
    return (EXIT_SUCCESS);
}
