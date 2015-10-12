/* 
 * File:   main.c
 * Author: Zachary
 * Lab 2: INTERRUPT on TIMER
 * Created on September 10, 2015, 12:58 PM
 */


// GOAL:
// After a button press, all LEDs will stay lit for a 5 second cool time period
// and then turn off.

// Use Timer1 as an interrupt source and use its ISR to toggle a global
// variable to track whether or not 5 seconds are up.

// In the main function, use an endless loop to read from the button and to
// control the LEDs. Reset the timer every time you push the button.

// If the same button is pushed within the cool down period, all LEDs will be
// shut off.

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <libpic30.h>
#include "config.h"

/*DEFINITIONS*/
#define readPin1 PORTBbits.RB7 // this is the interrupt pin (INT0)
#define readPin2 PORTBbits.RB6

/*------------------GLOBAL VARIABLES------------------*/

typedef unsigned char BOOL; // typedef unsigned char to BOOL
#define TRUE    1           // define a true value of 1
#define FALSE   0           // define a false value of 0

typedef struct my_booleans  // create a structure of booleans
{
  BOOL timer_flag:1;
  BOOL leds_flag:1;
}
my_booleans_t;

my_booleans_t myBOOLs;

/*------------------FUNCTION PROTOTYPES------------------*/
void LATBlow(void);
void LATBhigh(void);

/*------------------INTERRUPT SERVICE ROUTINES------------------*/
//ISR for Timer 1
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    if(myBOOLs.leds_flag == TRUE) //if leds are on, then do something
    {
        myBOOLs.timer_flag = TRUE;
    }
    IFS0bits.T1IF = 0;  //set T1 flag back to zero 
}

//ISR for external interrupt INT0
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    if(myBOOLs.leds_flag == TRUE)
    {  
        myBOOLs.leds_flag = FALSE;
        myBOOLs.timer_flag = TRUE;
    }
    IFS0bits.INT0IF = 0; //set INT0 flag back to zero
}

/*------------------MAIN FUNCTION------------------*/
int main(void)
{  
    /*------------------CONFIGURE TIMER------------------*/
    T1CON = 0x8012;     // Enable T1 from external oscillator (SOSC), pre-scaler of 8)
    PR1 = 20480;        // this value generates an interrupt every 5 seconds
    

    // Fosc = 32768, Fcyc = Fosc/2
    // Fcyc = 16384, Tcyc = 61.0352 uS
    // Prescaler = 8. This means that the counter increments every 8 cycles.
    // 5 seconds will have passed after 81920 clock cycles
    // If the timer is only incrementing once every 8 cycles, then
    // it will take 10240 counts to equal 5 seconds of delay time.
    // Therefore, PR1 should be set to 10240.

    /*------------------CONFIGURE INTERRUPTS------------------*/

    INTCON2bits.INT0EP = 0; // interrupt on positive edge
    INTCON2bits.ALTIVT = 0; // use primary IVT

    // INT 0 INTERRPUT PRIORITY
    IPC0bits.IC1IP2 = 1;
    IPC0bits.IC1IP1 = 0;
    IPC0bits.IC1IP0 = 0;    // set priority level to 4 (100)

    // T1 INTERRPUT PRIORITY
    IPC0bits.T1IP2 = 1;
    IPC0bits.T1IP1 = 0;
    IPC0bits.T1IP0 = 0;     // set priority level to 3 (011)

    IFS0bits.T1IF = 0;      // initialize T1 flag to zero
    IFS0bits.INT0IF = 0;    // initialize INT0 flag to zero
    IEC0bits.INT0IE = 1;    // enable the INT0 external interrupt source
    IEC0bits.T1IE = 1;      // enable the T1 timer interrupt source
    
    /*------------------SETUP------------------*/
    TRISB = 0b0000000011000000; 
    myBOOLs.timer_flag = FALSE;
    myBOOLs.leds_flag = FALSE;
    TMR1 = 0;
    LATBlow();

    /*------------------INFINITE LOOP------------------*/
    while(1)
    {
        if(readPin2 && myBOOLs.leds_flag == FALSE)
        {
            TMR1 = 0;
            LATBhigh();
            myBOOLs.leds_flag = TRUE; 
        }

        if(myBOOLs.timer_flag == TRUE)
        {
            LATBlow();
            myBOOLs.timer_flag = FALSE;
            myBOOLs.leds_flag = FALSE;
        }
    }
    return (EXIT_SUCCESS);
}

/*------------------FUNCTIONS------------------*/
void LATBlow(void)
{
    LATB &= ~0xFF00;
}

void LATBhigh(void)
{
    LATB |= 0xFF00;
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