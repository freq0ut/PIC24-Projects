/* 
 * File:   main.c
 * Author: Zachary
 * Lab 1: Odd Lights
 * Created on September 10, 2015, 12:58 PM
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"

/*DEFINITIONS*/
#define readPin1 PORTBbits.RB7
#define readPin2 PORTBbits.RB6
#define readPin3 PORTBbits.RB5
#define readPin4 PORTBbits.RB3

/*FUNCTION PROTOTYPES*/
void LATBlow(void);
void LATBhigh(void);

/*MAIN FUNCTION*/
int main(void)
{  
    /*SETUP*/
    TRISB = 0xE8;
    ANSBbits.ANSB3=0; // Digital input buffer is active
    
    /*INFINITE LOOP*/
    while(1)
    {
        if((readPin1 + readPin2 + readPin3 + readPin4)%2 != 0)
            LATBhigh();     
        else
            LATBlow();
    }
    return (EXIT_SUCCESS);
}

/*FUNCTIONS*/
void LATBlow(void)
{
    LATB &= ~0xFF00;
}

void LATBhigh(void)
{
    LATB |= 0xFF00;
}