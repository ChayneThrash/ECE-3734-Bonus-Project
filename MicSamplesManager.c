#include "MicSamplesManager.h"
#include "adc_impl.h"
#include "pic24_unittest.h"

struct MicSamplesManager samples_manager;

void append_sample(float  sample)
{
    if (samples_manager.num_samples < FFT_SIZE)
    {
        samples_manager.re_time_samples[samples_manager.num_samples] = sample;
        ++(samples_manager.num_samples);
    }
    else
    {
        ASSERT(0);
    }
}