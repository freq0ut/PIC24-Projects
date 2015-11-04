/* 
 * File:   Lab5_SPI.c
 * Author: Zachary
 *
 * Created on October 30, 2015, 2:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <math.h>
#include "config.h"
#include "SPI.h"
#include "SevenSeg.h"

int main(void) 
{
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock registers to configure PPS
    RPOR3bits.RP6R = 8;     // configure RP6 as SCK1
    RPINR20bits.SDI1R = 7;  // configure RP7 as SDI1
    RPOR4bits.RP8R = 7;     // configure RP8 as SDO1
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock registers
    
    initSPI();
    delay_ms(500);
    
    writeSPI(clrDisplay);
    while(1)
    {
        writeSPI('1');
        writeSPI('2');
        writeSPI('3');
        writeSPI('4');
        delay_ms(500);
        writeSPI('a');
        writeSPI('d');
        writeSPI('5');
        writeSPI('b');
        delay_ms(500);
    }
    return (EXIT_SUCCESS);
}