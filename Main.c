#include <pic24_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "FFT.h"
#include "adc_impl.h"
#include "leds.h"
#include "timers.h"
#include "MicSamplesManager.h"

void config_All()
{
    configBasic(HELLO_MSG);
    configLED();
    configTimer2();
    config_adc();
    samples_manager.num_samples = 0;
}

void ProcessSamples(float * new_note, float * old_note, float * Xmag)
{
    samples_manager.num_samples = 0;

    fft(samples_manager.re_time_samples, samples_manager.im_time_samples, samples_manager.re_freq_samples, samples_manager.im_freq_samples);
    Amag(FFT_SIZE,samples_manager.re_freq_samples,samples_manager.im_freq_samples,Xmag);
    *old_note = *new_note;
    *new_note = getPeak(Xmag);
    printf("frequency: %d\n",(int) *new_note);
}

int main(){
    config_All();
    float  temp1[FFT_SIZE], temp2[FFT_SIZE], temp3[FFT_SIZE], temp4[FFT_SIZE];

    samples_manager.re_time_samples = temp1;
    samples_manager.im_time_samples = temp2;
    samples_manager.re_freq_samples = temp3;
    samples_manager.im_freq_samples = temp4;



    float  Xmag[FFT_SIZE];
    float  old_note = 0;
    float  new_note = 0;

    /*
     * The commented out code below is important. If we randomly start only
     * reading -1 as the frequency, loading the code with just a sine wave input
     * somehow fixes it. 
     */

//    int i;                    // generic index
//    for(i = 0;i<256;i++){
//        samples_manager.re_time_samples[i] = 100*sin(TWO_PI*i*10/255) + 2244;
//        samples_manager.im_time_samples[i] = 0;
//        printf("%d: %d\n",i,(int)samples_manager.re_time_samples[i]);
//    }
    
    while(1)
    {
          DELAY_MS(100);
        if (samples_manager.num_samples == FFT_SIZE)
        {
            timer2_Off();
            ProcessSamples(&new_note, &old_note, Xmag);
            changeLed(new_note);
            //Re-Enable sampling after FFT
            timer2_On();
        }
        doHeartbeat();
    }
}

