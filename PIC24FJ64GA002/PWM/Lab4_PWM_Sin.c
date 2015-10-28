/* 
 * File:   Lab4_PWM.c
 * Author: Zachary
 *
 * Created on October 27, 2015, 12:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include "config.h"
#include "PWM.h"

// Use C = 1 nF, R = 47 kOhm for LPF

// This are the values to produce a sine wave with f = 2.5 kHz
const int sinTable[80] = {40, 43, 46, 49, 52, 55, 58, 61, 64, 
                          66, 68, 70, 72, 74, 76, 77, 78, 79, 
                          80, 80, 80, 80, 80, 79, 78, 77, 76, 
                          74, 72, 70, 68, 66, 64, 61, 58, 55, 
                          52, 49, 46, 43, 40, 37, 34, 31, 28, 
                          25, 22, 19, 16, 14, 12, 10, 8, 6, 
                          4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 
                          3, 4, 6, 8, 10, 12, 14, 16, 19, 
                          22, 25, 28, 31, 34, 37, 40};
int count = 0;

void _ISRFAST _T3Interrupt(void)
{
    OC1RS = sinTable[count];
    if(++count >= 80)
        count = 0;
    _T3IF = 0;  //set T3 flag back to zero 
}

int main(void) 
{  
    /** configure RP9 as output compare pin (PWM) **/
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock registers to configure PPS
    RPOR4bits.RP8R = 18;    // configure RP9 as OC1
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock registers
    
    /** configure PWM (initPWM) -- enable timer 3, set period, duty, activate PWM **/
    int period = 80;       // calculate for desired period based on timer 3 freq
    int duty = period/2;    // duty cycle of 50%
    initPWM(period, duty);  // PWM initialization function
    
    int i;
    while(1)
    {
    }
    
    return (EXIT_SUCCESS);
}

