#include "adc_impl.h"
#include "pic24_all.h"
#define MIC_INPUT (RA0_AN)
#define ADC_12BIT_FLAG 1

void config_adc()
{
    CONFIG_RA0_AS_ANALOG();
    configADC1_ManualCH0(MIC_INPUT, 31, ADC_12BIT_FLAG );
}

float getSample(){
    return (float) convertADC1();
}