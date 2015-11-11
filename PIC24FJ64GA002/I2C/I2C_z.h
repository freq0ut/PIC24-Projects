/* 
 * File:   I2C.h
 * Author: Zachary
 *
 * Created on November 10, 2015, 8:36 PM
 */

#ifndef I2C_z_H
#define	I2C_z_H

int delay = 0;

void i2cInit(int chan, int BRG);
void i2c1Start(void);
void i2c1StartAddress(unsigned char slave_address, unsigned char RW);
void i2c1WriteByte(char data);
void i2c1Stop(void);

void i2cInit(int chan, int BRG)
{
    if(chan == 1)
    {
        I2C1BRG = BRG;
        I2C1CONbits.I2CEN = 1;
    }
    if(chan == 2)
    {
        I2C2BRG = BRG;
        I2C2CONbits.I2CEN = 1;
    } 
}

void i2c1Start(void)
{
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN);
    delay_us(delay);
}

void i2c1StartAddress(unsigned char slave_address, unsigned char RW)
{
    int cmd;
    cmd = 0x00 | slave_address << 1 | (RW & 0x1);
    i2c1Start();
    i2c1WriteByte(cmd);
}

void i2c1WriteByte(char data)
{
    while(I2C1STATbits.TBF); // wait until buffer is empty
    I2C1TRN = data; // load transmit buffer with data
    delay_us(delay);
}

void i2c1Stop(void)
{
    //delay_us(delay);
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN);
    delay_us(delay);
}

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

