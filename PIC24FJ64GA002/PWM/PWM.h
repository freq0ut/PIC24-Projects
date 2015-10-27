/* 
 * File:   PWM.h
 * Author: Zachary
 *
 * Created on October 27, 2015, 12:14 PM
 */

#ifndef PWM_H
#define	PWM_H

void initPWM(int period, int duty);

void initPWM(int period, int duty)
{
    T3CON = 0x8000;     // enable timer 3
    PR3 = period-1;     // set the period for the given bit rate
    _T3IF = 0;          // set T3 interrupt flag low
    _T3IE = 1;          // enable the T3 interrupt
    
    OC1R = OC1RS = duty;  // set initial duty cycle to 50%
    
    OC1CON = 0x000E;    // activate PWM module (T3 is clock source, PWM mode on;
                        // Fault pin, OCFx disabled.)
    TMR3 = 0;
}

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

