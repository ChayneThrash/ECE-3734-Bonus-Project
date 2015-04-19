/* 
 * File:   FFT.h
 * Author: Spencer
 *
 * Created on April 16, 2015, 2:23 PM
 */

#ifndef FFT_H
#define	FFT_H

/* macros */
#define FFT_size (256) // must also be set in Main.c
#define fs (8000)      // sampling frequency
#define SAMPLING_TIME_US (125)
#define TWO_PI (6.283185)

/* function prototypes */
void fft(float* Rex,float* Imx, float* ReX, float* ImX);
void fft_rec(int N, int offset, int delta,
        float* Rex,float* Imx,
        float* ReX, float* ImX,
        float* ReXX, float* ImXX);
float mag(float x, float y);
void Amag(int size, float* x, float* y, float* z);
float getPeak(float* Xmag);


#endif	/* FFT_H */

