/* 
 * File:   main.c
 * Author: Zachary
 * Lab 2: INTERRUPT binary counter
 * Created on September 10, 2015, 12:58 PM
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <libpic30.h>
#include "config.h"

/*DEFINITIONS*/

/*------------------GLOBAL VARIABLES------------------*/
int binary_count = 0;
/*------------------FUNCTION PROTOTYPES------------------*/
void LATB_low(void);
int bin_shift(int input);

/*------------------INTERRUPT SERVICE ROUTINES------------------*/
//ISR for Timer 1
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    binary_count = binary_count + 1;
    IFS0bits.T1IF = 0;
}

/*------------------MAIN FUNCTION------------------*/
int main(void)
{  
    /*------------------CONFIGURE TIMER------------------*/
    T1CON = 0x8012;     // Enable T1 from external oscillator (SOSC), pre-scaler of 8)
    PR1 = 4096;        // this value generates an interrupt every 1 seconds

    /*------------------CONFIGURE INTERRUPTS------------------*/

    INTCON2bits.INT0EP = 0; // interrupt on positive edge
    INTCON2bits.ALTIVT = 0; // use primary IVT

    // T1 INTERRPUT PRIORITY
    IPC0bits.T1IP2 = 1;
    IPC0bits.T1IP1 = 0;
    IPC0bits.T1IP0 = 0;     // set priority level to 4 (100)

    IFS0bits.T1IF = 0;      // initialize T1 flag to zero
    IEC0bits.T1IE = 1;      // enable the T1 timer interrupt source
    
    /*------------------SETUP------------------*/
    TRISB = 0b0000000000000000; 
    TMR1 = 0;
    LATB_low();

    /*------------------INFINITE LOOP------------------*/
    while(1)
    {
        LATB = bin_shift(binary_count);
        if(binary_count > 255)
            binary_count = 0;
    }
    return (EXIT_SUCCESS);
}

/*------------------FUNCTIONS------------------*/
void LATB_low(void)
{
    LATB &= ~0xFF00;
}

int bin_shift(int input)
{
    int output;
    output = input << 8;
    return output;
}

/*  FOR TIMER CONFIGURATIONS:
     * Bit 15: T1CONbits.TON -> 1 turns timer on, 0 turns timer off
     * Bit 14: UNIMPLEMENTED
     * Bit 13: T1CONbits.TSIDL -> 1 discontinues module operation in idle mode
     * Bit 12: UNIMPLEMENTED
     * Bit 11: UNIMPLEMENTED
     * Bit 10: UNIMPLEMENTED
     * Bit 09: T1CONbits.T1ECS1 -> 11: reserved, 10: Timer 1 uses the LPRC as source
     * Bit 08: T1CONbits.T1ECS0 -> 01: Timer 1 uses external clock from T1CK, 00: Timer 1 uses Secondary Oscillator
     * Bit 07: UNIMPLEMENTED
     * Bit 06: T1CONbits.TGATE -> When TCS is 1, this is ignored. When TCS is 0, 1 = enabled, 0 = disabled.
     * Bit 05: T1CONbits.TCKPS1 -> Prescaler value. 11 = 256, 10 = 64, 01 = 8, 00 = 1.
     * Bit 04: T1CONbits.TCKPS0 -> 11: 256, 10: 64, 01: 8, 00: 1.
     * Bit 03: UNIMPLEMENTED
     * Bit 02: T1CONbits.TSYNC -> 1: synchronizes external clock input
     * Bit 01: T1CONbits.TCS -> Clock source select bit, 1: T1ECS config, 0: internal.
     * Bit 00: UNIMPLEMENTED
    */