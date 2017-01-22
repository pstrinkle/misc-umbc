#include <math.h>
#include <stdio.h>
#include "libfft_spu.h"

#define N 64

int main(int argc, char **argv) {

   int i;
   float in[2*N], out[N];
   
   /* Initialize the input vector 
      with a square wave */
   for(i=0; i<N/2; i+=2) {
      in[i] = 1.0;
      in[i+1] = 0.0;
   }
   
   for(i=N/2; i<2*N; i+=2) {
      in[i] = 0.0;
      in[i+1] = 0.0;
   }
   
   /* Perform the transform */
   fft_1d_c2r_spu(N, (vector float*)in, 
      (vector float*)out);
   return 0;
}
