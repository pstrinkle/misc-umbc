#include <math.h>
#include <stdio.h>
#include "libfft_example.h"

#define N 64
#define log2_size 6

int main(int argc, char **argv) {

   int i;
   float in[2*N], out[2*N], W[N/2] __attribute__ ((aligned (16))); 
   
   /* Initialize the input vector: square wave */
   for(i=0; i<N/2; i+=2) {
      in[i] = 1.0;
      in[i+1] = 0.0;
   }
   
   for(i=N/2; i<2*N; i+=2) {
      in[i] = 0.0;
      in[i+1] = 0.0;
   }
   
   /* Initialize the W vector */
   for (i=0; i<N/2; i+=2) {	    
      W[i] =  cos(((double)i * M_PI)/N);
      W[i+1] = -sin(((double)i * M_PI)/N);
   }
   
   /* Compute the FFT and display the results */
   fft_1d_r2((vector float*)out, (vector float*)in, 
      (vector float*)W, log2_size);
   for (i=0; i<2*N; i+=2) {	    
      printf("%f + %fi\n", out[i], out[i+1]);
   }
   return 0;
}
