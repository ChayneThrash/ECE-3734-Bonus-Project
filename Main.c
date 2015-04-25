#include <pic24_all.h>
#include <stdio.h>
#include <stdlib.h>
#include "FFT.h"
#include "adc_impl.h"
#include "leds.h"
#include "timers.h"
#include "MicSamplesManager.h"

void inline config_All()
{
    configBasic(HELLO_MSG);
    configLeds();
    configTimer2();
    configADC1();
    samples_manager.num_samples = 0;
}

float detectTuningNote(float freq){
    if(freq > 148 && freq < 157){return 154.0;}   //D_STRING
    if(freq > 185 && freq < 216){return 190.0;}   //G_STRING
    if(freq > 226 && freq < 257){return 249.0;}   //B_STRING
    if(freq > 310 && freq < 345){return 333.0;}   //E_STRING
    if(freq > 1000 && freq < 1400){return 1200.0;}//WHISTLE
    else{return 0.0;}                             //SILENT
}

void inline processSamples(float* new_note, float* tuned_note, float* Xmag)
{
    fft(samples_manager.re_time_samples, samples_manager.im_time_samples, samples_manager.re_freq_samples, samples_manager.im_freq_samples);
    Amag(FFT_SIZE,samples_manager.re_freq_samples,samples_manager.im_freq_samples,Xmag);
    *new_note = getPeak(Xmag);
    *tuned_note = detectTuningNote(*new_note);
    printf("frequency: %d\n",(int) *new_note);
    if ((*new_note) > 1.8 * (*tuned_note))
    {
        *new_note /= 2;
    }
}

void beginTuning()
{
    initializeImaginary(samples_manager.im_time_samples);

    float  Xmag[FFT_SIZE];
    float tuned_note = 0.0;
    float  new_note = 0.0;
    while(1)
    {
        if (samples_manager.num_samples == FFT_SIZE)
        {
            timer2Off();
            samples_manager.num_samples = 0;
            if (SPL(FFT_SIZE, samples_manager.re_time_samples))
            {
                processSamples(&new_note, &tuned_note, Xmag);
                setLeds(tuned_note, new_note);
            } 
            else
            {
                ledsOff();
            }
            timer2On();
        }
        doHeartbeat();
    }
}

int main()
{
    config_All();
    
    float  temp1[FFT_SIZE], temp2[FFT_SIZE], temp3[FFT_SIZE], temp4[FFT_SIZE];

    samples_manager.re_time_samples = temp1;
    samples_manager.im_time_samples = temp2;
    samples_manager.re_freq_samples = temp3;
    samples_manager.im_freq_samples = temp4;

    beginTuning();
    return 0;
}

