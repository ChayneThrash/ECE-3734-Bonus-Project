#include <pic24_all.h>
#include "FFT.h"
#include "MicSamplesManager.h"
#include "adc_impl.h"

void configTimer2(void)
{
    // T2CON is set like this for documentation purposes.
    // It could be replaced by T2CON = 0x0020.
    T2CON = T2_OFF | T2_IDLE_CON | T2_GATE_OFF
          | T2_32BIT_MODE_OFF
          | T2_SOURCE_INT
          | T2_PS_1_64;
    // Subtract 1 from ticks value assigned to PR2 because period is PRx + 1.
    PR2 = usToU16Ticks(SAMPLING_TIME_US, getTimerPrescale(T2CONbits)) - 1;
    // Start with a cleared timer2 value.
    TMR2  = 0;
    // Enable Timer2 interrupts.
    _T2IF = 0;
    _T2IP = 1;
    _T2IE = 1;
    // Start the timer only after all timer-related configuration is complete.
    T2CONbits.TON = 1;
}

void _ISR _T2Interrupt(void) {
  //Sample from the ADC
    append_sample(get_sample());
  // Clear the timer interrupt bit
  _T2IF = 0;
}