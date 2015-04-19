/*----------------------------------------------------------------------------
   fft.c - fast Fourier transform and its inverse (both recursively)
   Copyright (C) 2004, Jerome R. Breitenbach.  All rights reserved.

   The author gives permission to anyone to freely copy, distribute, and use
   this file.
  ----------------------------------------------------------------------------*/

/******************************************************************************
 * This file defines a C function fft that, by calling another function       *
 * fft_rec (also defined), calculates an FFT recursively.  Usage:             *
 *   fft(N, x, X);                                                            *
 * Parameters:                                                                *
 *   N: number of points in FFT (must equal 2^n for some integer n >= 1)      *
 *   x: pointer to N time-domain samples given in rectangular form (Re x,     *
 *      Im x)                                                                 *
 *   X: pointer to N frequency-domain samples calculated in rectangular form  *
 *      (Re X, Im X)                                                          *
 * Similarly, a function ifft with the same parameters is defined that        *
 * calculates an inverse FFT (IFFT) recursively.  Usage:                      *
 *   ifft(N, x, X);                                                           *
 * Here, N and X are given, and x is calculated.                              *
 ******************************************************************************/

#include <stdlib.h>
#include <math.h>
#include "FFT.h"

// temp array
float ReXX[FFT_size];
float ImXX[FFT_size];

/* FFT */
void fft(float* Rex, float* Imx, float* ReX, float* ImX){
  /* Calculate FFT by a recursion. */
  fft_rec(FFT_size, 0, 1, Rex, Imx, ReX, ImX, ReXX, ImXX);
}

/* FFT recursion */
void fft_rec(int N, int offset, int delta, float* Rex, float* Imx, float* ReX, float* ImX, float* ReXX, float* ImXX)
{
  int N2 = N/2;            /* half the number of points in FFT */
  int k;                   /* generic index */
  float cs, sn;           /* cosine and sine */
  int k00, k01, k10, k11;  /* indices for butterflies */
  float tmp0, tmp1;       /* temporary storage */

  if(N != 2)  /* Perform recursive step. */
    {
      /* Calculate two (N/2)-point DFT's. */
      fft_rec(N2, offset, 2*delta, Rex, Imx, ReXX, ImXX, ReX, ImX);
      fft_rec(N2, offset+delta, 2*delta, Rex, Imx, ReXX, ImXX, ReX, ImX);

      /* Combine the two (N/2)-point DFT's into one N-point DFT. */
      for(k=0; k<N2; k++)
        {
          k00 = offset + k*delta;    k01 = k00 + N2*delta;
          k10 = offset + 2*k*delta;  k11 = k10 + delta;
          cs = cos(TWO_PI*k/(float)N); sn = sin(TWO_PI*k/(float)N);
          tmp0 = cs * ReXX[k11] + sn * ImXX[k11];
          tmp1 = cs * ImXX[k11] - sn * ReXX[k11];
          ReX[k01] = ReXX[k10] - tmp0;
          ImX[k01] = ImXX[k10] - tmp1;
          ReX[k00] = ReXX[k10] + tmp0;
          ImX[k00] = ImXX[k10] + tmp1;
        }
    }
  else  /* Perform 2-point DFT. */
    {
      k00 = offset; k01 = k00 + delta;
      ReX[k01] = Rex[k00] - Rex[k01];
      ImX[k01] = Imx[k00] - Imx[k01];
      ReX[k00] = Rex[k00] + Rex[k01];
      ImX[k00] = Imx[k00] + Imx[k01];
    }
}

// Calculates the magnitude of the real and imaginary parts of the FFT
float mag(float x, float y){
    return sqrt(x*x + y*y);
}

void Amag(int size, float* x, float* y, float* z){
    int i = 0;
    while(i<size){
       z[i] = mag(x[i],y[i]);
       i += 1;
    }
}

//Basic peak detection. returns aproximate fundamental frequency
float getPeak(float *Xmag){
    int peak_index = 0;
    float peak_amp;
    float freq;
    //interpolation variables
    float interp_factor;
    
    float alpha;   //magnitude at peak_index - 1
    float beta;    //magnitude at the peak
    float gamma;   //magnitude at peak_index + 1

    // Max detection
    int i = 1;              // skip the first bin (DC offset)
    while(i<FFT_size/2){
        if(Xmag[i] > peak_amp) {
            peak_index = i;
            peak_amp = Xmag[i];
        }
        i++;
    }
    // Peak determination
    // unwindowed: main lobe = 2 bind
    //             side lobe = -12dB = main_lobe/4
    // therefore 2 indecies from the peak will be away from the main lobe
    // the main lobe should be 2-4  times the side lobe to be concidered a peak

    if(Xmag[peak_index] < 2000 ){
        return 0;
    }

    // Interpolation
    alpha =  Xmag[peak_index-1];
    beta  = Xmag[peak_index];
    gamma =  Xmag[peak_index+1];
    interp_factor = 0.5*(alpha-gamma) / (alpha - 2*beta + gamma);
    //printf("%d\t%d\t%d\n",(int)alpha,(int)beta,(int)gamma);

//    freq = (peak_index) *  2.0 * fs / FFT_size;
    freq = (peak_index+interp_factor) * fs / FFT_size;
    return freq;
}

  ////////////////////////////////FFT TEST/////////////////////////////////////
//  //Generate a sine wave
//  int i;                    // generic index
//  for(i = 0;i<256;i++){
//      Rex[i] = sin(TWO_PI*i*10/255);
//      Imx[i] = 0;
//      printf("%d: %d",i,(int)Rex[i]);
//  }

  //* Calculate FFT.
  /*
  printf("befor FFT\n");
  fft(x, X);
  printf("after FFT\n");
  */
    //getPeak(X)


  //* Print time-domain samples and resulting frequency-domain samples.
 /*
  /change to mag(X)
  printf("\nx(n):");
  for(i=0; i<FFT_SIZE; i++) printf("\n   n=%d: %12f %12f", i, x[i][0], x[i][1]);
  printf("\nX(k):");
  for(i=0; i<FFT_SIZE; i++) printf("\n   k=%d: %12f %12f", i, X[i][0], X[i][1]);
*/

  //* Clear time-domain samples and calculate IFFT.
  //for(i=0; i<FFT_SIZE; i++) x[i][0] = x[i][1] = 0;
  //ifft(x, X);

  //* Print recovered time-domain samples.
 // printf("\nx(n):");
 // for(i=0; i<FFT_SIZE; i++) printf("\n   n=%d: %12f %12f", i, x[i][0], x[i][1]);
////////////////////////////////////////////////////////////////////////////////
 