/* 
 * File:   Lab3_AtoD_LCD.c
 * Author: Zachary
 * Lab 3:  LCD Scrolling Name Display
 * Created on September 10, 2015, 12:58 PM
 */

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include "config.h"
#include "LCD.h"
#include "ADC.h"

/*DEFINITIONS*/

/*------------------GLOBAL VARIABLES------------------*/
typedef unsigned char BOOL; // typedef unsigned char to BOOL
#define TRUE    1           // define a true value of 1
#define FALSE   0           // define a false value of 0

typedef struct my_booleans  // create a structure of booleans
{
  BOOL timer_flag:1;
}
my_booleans_t;

my_booleans_t myBOOLs;
/*------------------FUNCTION PROTOTYPES------------------*/
int getADC(unsigned int channel);
void initADC(void);

/*------------------INTERRUPT SERVICE ROUTINES------------------*/
// ISR for Timer 1
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    myBOOLs.timer_flag = TRUE;
    IFS0bits.T1IF = 0;
}

/*------------------MAIN FUNCTION------------------*/
int main(void)
{  
    __builtin_write_OSCCONL(2); // Enable secondary oscillator with unlock sequence
    T1CON = 0x8012; // Enable T1 from external oscillator (SECONDARY), pre-scaler of 8)
    T2CON = 0x8000;
    PR1 = 410;      // this value generates an interrupt every 100 milliseconds (Primary)

    /*------------------CONFIGURE INTERRUPTS------------------*/
    INTCON2bits.INT0EP = 0;     // interrupt on positive edge
    INTCON2bits.ALTIVT = 0;     // use primary IVT
    IPC0bits.T1IP = 4;          // set priority level to 4 (100)
    IFS0bits.T1IF = 0;          // initialize T1 flag to zero
    IEC0bits.T1IE = 1;          // enable the T1 timer interrupt source
    
    TRISBbits.TRISB2 = 0; // Used as Register Select for LCD
    initPMP();
    initLCD();
    
    setLCDG(0);
    putLCD(0b00000);
    putLCD(0b10001);
    putLCD(0b00000);
    putLCD(0b00100);
    putLCD(0b00000);
    putLCD(0b10001);
    putLCD(0b01110);
    putLCD(0);
    
    putLCD(0b00000);
    putLCD(0b10001);
    putLCD(0b00000);
    putLCD(0b00100);
    putLCD(0b00000);
    putLCD(0b00000);
    putLCD(0b11111);
    putLCD(0);
    
    putLCD(0b00000);
    putLCD(0b10001);
    putLCD(0b00000);
    putLCD(0b00100);
    putLCD(0b00000);
    putLCD(0b01110);
    putLCD(0b10001);
    putLCD(0);

    int Buf = 0;
    initADC();
    //TRISB = 0xFF00; // configure LED port as outputs
    char BufString[20];
    char BufString2[5];
    char BufString3[16];
    double voltage, vAvg, avgTime;
    int i, time;
    unsigned long bufAvg;
    int nAvg = 100;
    TMR1 = 0;
    /*------------------INFINITE LOOP------------------*/
    while(1)
    {
        vAvg = 0;
        voltage = 0;
        bufAvg = 0;
        time = 0;
        avgTime = 0;
        for(i=0;i<nAvg;i++)
        {
            TMR2 = 0;
            Buf = getADC(0);    // read channel 1 of ADC
            time = TMR2;
            voltage = Buf*3.3/1023;
            vAvg = vAvg + voltage;
            bufAvg = bufAvg + Buf;
            avgTime = avgTime + time;
        }
        vAvg = vAvg/nAvg;
        bufAvg = bufAvg/nAvg;
        avgTime = avgTime/nAvg/16/1000;
        if(myBOOLs.timer_flag == TRUE)
        {
            setCursor(1,0);
            putsLCD("Voltage: ");
            sprintf(BufString,"%.02f",vAvg);
            sprintf(BufString2,"%lu",bufAvg);
            sprintf(BufString3,"%.05f",avgTime);
            setCursor(1,9);
            putsLCD(BufString);
            setCursor(1,16);
            putsLCD(BufString2);
            putsLCD("   ");
            setCursor(2,0);
            putsLCD("Time: ");
            setCursor(2,6);
            putsLCD(BufString3);
            setCursor(2,14);
            putsLCD("ms");
            setCursor(2,19);
            if(bufAvg > 1023*2/3)
                putLCD(0);
            if(bufAvg < 1023*2/3 && bufAvg > 1023*1/3)
                putLCD(1);
            if(bufAvg < 1023*1/3 && bufAvg > 0)
                putLCD(2);
            myBOOLs.timer_flag = FALSE;
        }
    }
    return (EXIT_SUCCESS);
}

