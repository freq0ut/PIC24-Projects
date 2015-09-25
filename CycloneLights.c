/* 
 * File:   main.c
 * Author: Zachary
 * Cyclone
 * Created on September 8, 2015, 8:21 PM
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xc.h>
#include <libpic30.h>
#include "config.h"

/*DEFINITIONS*/
#define readPin1 PORTBbits.RB7
#define readPin2 PORTBbits.RB6

/*FUNCTION PROTOTYPES*/
void LEDcyclone(void);
void LEDticToc(void);

/*MAIN FUNCTION*/
int main(void)
{  
    /*SETUP*/
    TRISB = 0xC0;
    
    /*INFINITE LOOP*/
    while(1)
    {
        LEDcyclone();
        //LEDticToc();
    }
    return (EXIT_SUCCESS);
}

/*FUNCTIONS*/
void LEDcyclone(void)
{
    int i;
    int count;
    for(i=8;i<=15;i++)
    {
        count = pow(2,i);
        LATB = count;
        delay_ms(25);
    }
    for(i=14;i>8;i--)
    {
        count = pow(2,i);
        LATB = count;
        delay_ms(25);
    } 
}

void LEDticToc(void)
{
    LATB = 0xAA00;
    delay_ms(500);
    LATB = 0x5500;
    delay_ms(500);
}