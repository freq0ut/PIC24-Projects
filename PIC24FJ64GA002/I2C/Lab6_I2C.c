/* 
 * File:   Lab6_I2C.c
 * Author: Zachary
 *
 * Created on November 11, 2015, 2:29 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <math.h>
#include "config.h"
#include "I2C_z.h"
#include "SevenSeg.h"

int main(void) 
{   
    // (Using SDA1 and SCL1
    // Configure I2C Port
    i2cInit(1,157);
    delay_ms(500);
    while(1)
    {
        // Start bit + Address + read or write bit
        i2c1StartAddress(I2Caddr, 0); //(7-seg address, write (0))
        // Data + Ack
        i2c1WriteByte(clrDisplay);
        i2c1WriteByte('1');
        i2c1WriteByte('2');
        i2c1WriteByte('3');
        i2c1WriteByte('4');
        // Stop Bit
        i2c1Stop();
        delay_ms(1000);
        
        // Start bit + Address + read or write bit
        i2c1StartAddress(I2Caddr, 0); //(7-seg address, write (0))
        // Data + Ack
        i2c1WriteByte(clrDisplay);
        i2c1WriteByte('a');
        i2c1WriteByte('5');
        i2c1WriteByte('d');
        i2c1WriteByte('b');
        // Stop Bit
        i2c1Stop();
        delay_ms(1000);
    }
    return (EXIT_SUCCESS);
}