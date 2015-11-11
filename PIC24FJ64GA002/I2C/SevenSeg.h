/* 
 * File:   SevenSeg.h
 * Author: Zachary
 *
 * Created on October 30, 2015, 2:34 PM
 */

#ifndef SEVENSEG_H
#define	SEVENSEG_H

#define baudConfig      0x7F    // set to 0-11, see baud config
#define clrDisplay      0x76    // clears the display
#define decimalCtrl     0x77    // (0-63) 1 bit per decimal
#define brightCtrl      0x7A    // 0-255, 0 dimmest - 255 brightest
#define cursorCtrl      0x79    // 0-3, 0 is left most - 3 is right most
#define digit1Ctrl      0x7B    // 0-127, 1 bit per segment
#define digit2Ctrl      0x7C    // 0-127, 1 bit per segment
#define digit3Ctrl      0x7D    // 0-127, 1 bit per segment
#define digit4Ctrl      0x7E    // 0-127, 1 bit per segment
#define factoryReset    0x81    // reset to factory defaults
#define i2cAddress      0x80    // set the i2c address (0-126)
#define colonON         0b00010000 // turn on colon
#define colonOFF        0b00000000 // turn on colon
#define AMPM            0b00001000 // am/pm indicator

#define I2Caddr         0x71       // i2c address (default)

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* SEVENSEG_H */

