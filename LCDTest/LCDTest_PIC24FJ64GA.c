/* 
 * File:   Lab2_ISR_BinaryCounter.c
 * Author: Zachary
 * Lab 2:  Timer generated interrupt binary counter
 * Created on September 10, 2015, 12:58 PM
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include "config.h"
#include "LCD.h"

/*DEFINITIONS*/



/*------------------GLOBAL VARIABLES------------------*/
//int binary_count = 0;

/*------------------FUNCTION PROTOTYPES------------------*/


/*------------------INTERRUPT SERVICE ROUTINES------------------*/
// ISR for Timer 1
//void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
//{
//    binary_count = binary_count + 1;
//    IFS0bits.T1IF = 0;
//}

/*------------------MAIN FUNCTION------------------*/
int main(void)
{  
    /*------------------CONFIGURE TIMER------------------*/
    //OSCCONbits.SOSCEN = 1;
    //__builtin_write_OSCCONL(2); // Enable secondary oscillator with unlock sequence
    //T1CON = 0x8030;           // Enable T1 from external oscillator (PRIMARY), pre-scaler of 256)
    //PR1 = 62500;              // this value generates an interrupt every 1 seconds (Primary)
    //T1CON = 0x8012;             // Enable T1 from external oscillator (SECONDARY), pre-scaler of 8)
    //PR1 = 4096;                 // this value generates an interrupt every 1 seconds (Primary)

    /*------------------CONFIGURE INTERRUPTS------------------*/
//    INTCON2bits.INT0EP = 0;     // interrupt on positive edge
//    INTCON2bits.ALTIVT = 0;     // use primary IVT
//
//    // T1 INTERRPUT PRIORITY
//    IPC0bits.T1IP = 4;          // set priority level to 4 (100)
//    IFS0bits.T1IF = 0;          // initialize T1 flag to zero
//    IEC0bits.T1IE = 1;          // enable the T1 timer interrupt source
    
    /*------------------SETUP------------------*/
    //ANSBbits.ANSB4=0; // Digital input buffer is active
    TRISBbits.TRISB2 = 0;
    initPMP();
    initLCD();
    
    setLCDC(0x00);
    putsLCD("Zack");
    setLCDC(0x40);
    putsLCD("Goyetche");
    
//    setLCDG(0);
//    putLCD(0b00010);
//    putLCD(0b00010);
//    putLCD(0b00110);
//    putLCD(0b11111);
//    putLCD(0b00110);
//    putLCD(0b00010);
//    putLCD(0b00010);
//    putLCD(0);
//    
//    putLCD(0b00000);
//    putLCD(0b00100);
//    putLCD(0b01100);
//    putLCD(0b11100);
//    putLCD(0b00000);
//    putLCD(0b00000);
//    putLCD(0b00000);
//    putLCD(0);
    
    
    
//    int i;
//    for(i=4;i>=0;i--)
//    {
//        cursorLCD(i);
//        putsLCD("Hello World!!!");
//        delay_ms(1000);
//        clearLCD();
//    }
//    clearLCD();
    //delay_ms(1000);
    //putsLCD("Zack Goyetche");
    /*------------------INFINITE LOOP------------------*/
    while(1)
    {
//        setLCDC((18));
//        putLCD(0);
//        putLCD(1);
//        delay_ms(144);
//        
//        int i;
//        for(i=17;i>=0;i--)
//        {
//            setLCDC((i));
//            putLCD(0);putLCD(1);
//            putLCD(' ');
//            delay_ms(144);
//            //clrLCD();
//        }
//        
//        setLCDC(0);
//        putLCD(1);
//        putLCD(' ');
//        delay_ms(144);
//        
//        setLCDC(0);
//        putLCD(' ');
//        delay_ms(144);
//        
//     
//        
//        setLCDC((0x40+18));
//        putLCD(0);
//        putLCD(1);
//        delay_ms(144);
//        
//        for(i=17;i>=0;i--)
//        {
//            setLCDC((0x40 + i));
//            putLCD(0);putLCD(1);
//            putLCD(' ');
//            delay_ms(144);
//            //clrLCD();
//        }
//        
//        setLCDC(0x40);
//        putLCD(1);
//        putLCD(' ');
//        delay_ms(144);
//        
//        setLCDC(0x40);
//        putLCD(' ');
//        delay_ms(144);
        
        
    }
    return (EXIT_SUCCESS);
}


/*------------------FUNCTIONS------------------*/


