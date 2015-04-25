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


void inline configLeds(){
  CONFIG_LEDLo();
  CONFIG_LEDTn();
  CONFIG_LEDHi();
}

void inline ledsOff()
{
    LEDLo = 0;
    LEDHi = 0;
    LEDTn = 0;
}

void inline setLeds(float tuned_note, float new_note){
    if(new_note < 1.0 || tuned_note < 1)
    {
        ledsOff();
    }
    else
    {
            if(new_note < tuned_note*0.995)
            {
                LEDLo = 1;
                LEDHi = 0;
            } 
            else
            {
                LEDLo = 0;
            }
            if(new_note > tuned_note*1.005)
            {
                LEDLo = 0;
                LEDHi = 1;
            } 
            else
            {
                LEDHi = 0;
            }
            if(new_note < tuned_note*1.01 && new_note > tuned_note*0.99)
            {
                LEDTn = 1;
            } 
            else
            {
                LEDTn = 0;
            }
    }
}

#endif	/* LEDS_H */