/* 
 * File:   LEDs.h
 * Author: Spencer
 *
 * Created on April 16, 2015, 2:45 PM
 */

#ifndef LEDS_H
#define	LEDS_H

#define CONFIG_LEDLo() CONFIG_RB12_AS_DIG_OUTPUT()
#define LEDLo (_LATB12)     //indicates note is lower than expected frequency
#define CONFIG_LEDTn() CONFIG_RB13_AS_DIG_OUTPUT()
#define LEDTn (_LATB13)     //indicates note is in tune
#define CONFIG_LEDHi() CONFIG_RB14_AS_DIG_OUTPUT()
#define LEDHi (_LATB14)     //indicates note is higher than expected frequency


void inline configLED(){
  CONFIG_LEDLo();
  CONFIG_LEDTn();
  CONFIG_LEDHi();
}

#endif	/* LEDS_H */

