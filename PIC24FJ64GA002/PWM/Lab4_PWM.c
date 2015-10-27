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

void _ISRFAST _T3Interrupt(void)
{
    _T3IF = 0;  //set T3 flag back to zero 
}

int main(void) 
{  
    /** configure RP9 as output compare pin (PWM) **/
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock registers to configure PPS
    RPOR4bits.RP8R = 18;    // configure RP9 as OC1
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock registers
    
    /** configure PWM (initPWM) -- enable timer 3, set period, duty, activate PWM **/
    int period = 400;       // calculate for desired period based on timer 3 freq
    int duty = period/2;    // duty cycle of 50%
    initPWM(period, duty);  // PWM initialization function
    
    int i;
    while(1)
    {
        for(i = 0; i <= (period-1)/2; i++)
        {
            OC1RS = i;
            delay_ms(6);
        }
        for(i = (period-1)/2; i >= 0; i--)
        {
            OC1RS = i;
            delay_ms(6);
        }
    }
    
    return (EXIT_SUCCESS);
}

