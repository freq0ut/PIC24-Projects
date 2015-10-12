/* 
 * File:   main.c
 * Author: Zachary
 * Lab 2: Night Rider with INTERRUPT
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

/*INTERRUPT SERVICE ROUTINES*/
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    int i;
    for(i=0; i<5; i++)
    {
        LATB |= 0xFF00;
        delay_ms(50);
        LATB &= ~0xFF00;
        delay_ms(50);
    } 
    IFS0bits.INT0IF = 0; //initialize INT0 flag to zero
}

/*MAIN FUNCTION*/
int main(void)
{  
    /*SETUP*/
    TRISB = 0xE8;
    ANSBbits.ANSB3=0; // Digital input buffer is active
    
    /*CONFIGURE INTERRUPT*/
    INTCON2bits.INT0EP = 0; //interrupt on positive edge
    INTCON2bits.ALTIVT = 0; //use primary IVT
    
    IPC0bits.IC1IP2 = 1;
    IPC0bits.IC1IP1 = 0;
    IPC0bits.IC1IP0 = 0; //set priority level to 4 (100)
    
    IFS0bits.INT0IF = 0; //initialize INT0 flag to zero
    IEC0bits.INT0IE = 1; //enable the interrupt source
    
    /*INFINITE LOOP*/
    while(1)
    {
        if(readPin2 || readPin3 || readPin4)
        {
            nightRiderRL();
            nightRiderLR();
        }
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
        delay_ms(200);
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
        delay_ms(200);
    }
}