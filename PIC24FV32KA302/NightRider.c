/* 
 * File:    main.c
 * Author:  Zachary
 * Lab 1:   Night Rider
 * Created on September 10, 2015, 12:58 PM
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
#define readPin3 PORTBbits.RB5
#define readPin4 PORTBbits.RB3

/*FUNCTION PROTOTYPES*/
void LATBlow(void);
void nightRiderLR(void);
void nightRiderRL(void);

/*MAIN FUNCTION*/
int main(void)
{  
    /*SETUP*/
    TRISB = 0xE8;
    ANSBbits.ANSB3=0; // Digital input buffer is active
    
    /*INFINITE LOOP*/
    while(1)
    {
        if(readPin1 || readPin2)
            nightRiderRL();
        else if(readPin3 || readPin4)
            nightRiderLR();
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

void nightRiderRL(void)
{
    int i;
    int count;
    for(i=8;i<=15;i++)
    {
        count = pow(2,i);
        LATB = count;
        delay_ms(50);
    }
}

void nightRiderLR(void)
{
    int i;
    int count;
    for(i=15;i>=8;i--)
    {
        count = pow(2,i);
        LATB = count;
        delay_ms(50);
    }
}