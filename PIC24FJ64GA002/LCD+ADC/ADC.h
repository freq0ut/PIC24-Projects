/* 
 * File:   ADC.h
 * Author: Zachary
 *
 * Created on October 12, 2015, 10:45 PM
 */

#ifndef ADC_H
#define	ADC_H

int getADC(unsigned int channel)
{
    AD1CHS = channel;             // select channel
    AD1CON1bits.SAMP = 1;         // start sample
    while(AD1CON1bits.DONE == 0); // wait for conversion done
    AD1CON1bits.DONE = 0;
    return(ADC1BUF0);
}

void initADC(void)
{
    // Select port pins as analog inputs (AD1PCFG)
    TRISAbits.TRISA0 = 1;   // RA1 set as input
    AD1PCFGbits.PCFG0 = 0;  // Configure A0 as analog input
    
    // Select sample and conversion sequence (AD1CON1<7:5> & AD1CON3<12:8>)
    // Select  how  conversion  results  are presented in the buffer (AD1CON1<9:8>)
    AD1CON1 = 0x00E0;   // Turn off, auto sample , auto start , auto convert
    
    // Select the interrupt rate (AD1CON2<5:2>)
    // Select Vref source to match range of input (AD1CON2<15:13>)
    AD1CON2 = 0x0000;   // AVdd, AVss, int every conversion , MUXA only
    
    // Select A/D clock to match the conversion rate (ADCON3<7:0>)
    AD1CON3 = 0x1F05;   // auto-sample , Tad = 5 Tcyc
    AD1CSSL = 0x0000;   // ignore all on scan select
    
    // Turn on the A/D module (AD1CON1<15>) (DO THIS LAST)
    AD1CON1bits.ADON = 1; // turn on ADC
    
    // Configure the A/D interrupt (if required):
    // Clear the AD1IF bit
    // Select the A/D interrupt priority.
}

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

