/* 
 * File:   SPI.h
 * Author: Zachary
 *
 * Created on October 30, 2015, 2:29 PM
 */

#ifndef SPI_H
#define	SPI_H

//header contents go here

void initSPI(void);
unsigned char writeSPI(unsigned char i);

unsigned char writeSPI(unsigned char i)
{
    //while(!SPI1STATbits.SPITBF); // wait until send buffer is ready
    SPI1BUF = i; // write 8 bits to buffer for TX
    while(!SPI1STATbits.SPIRBF); // wait until read buffer is ready
    return SPI1BUF; // fetch 8 bits back (could be nothing)
}

void initSPI(void)
{
SPI1CON1 = 0x0120; // select mode
SPI1STAT = 0x8000; // enable the peripheral
}


#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

