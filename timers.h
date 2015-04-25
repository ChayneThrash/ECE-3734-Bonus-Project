/* 
 * File:   timers.h
 * Author: Chayne
 *
 * Created on April 19, 2015, 1:26 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

void configTimer2(void);

void inline timer2Off()
{
    _T2IE = 0;
    _T2IP = 0;
}

void inline timer2On()
{
    _T2IE = 1;
    _T2IP = 1;
}


#endif	/* TIMERS_H */

