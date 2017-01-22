#include <math.h>
#include <stdio.h>
#include "libfft_example.h"

#define N 64
#define log2_size 6

int main(int argc, char **argv) {

   int i, j;
   vector float a_real[N*N/4], a_imag[N*N/4];
   vector float b_real[N*N/4], b_imag[N*N/4];
   vector float buffer_real[N], buffer_imag[N];
   
   /* Create a cylindrical wave in the a matrix */
   for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
         ((float*)a_imag)[i*N+j] = 0.0;        
         if((i-N/2)*(i-N/2) + (j-N/2)*(j-N/2) 
            < (N/4)*(N/4))
            ((float*)a_real)[i*N+j] = 1.0;
         else
            ((float*)a_real)[i*N+j] = 0.0;
      }
   }
   
   /* Initialize the transform */
   init_fft_2d(log2_size);
   
   /* Convert data from the time domain 
      to the frequency domain */
   for (i=0; i<N/4; i++) {
      fft_2d(&a_real[N*i], &a_imag[N*i], 
         buffer_real, buffer_imag, 1);
      for (j=0; j<N; j++) {
         b_real[i+N/4*j] = buffer_real[j];
         b_imag[i+N/4*j] = buffer_imag[j];
      }
   }

   for (i=0; i<N/4; i++) {
      fft_2d(&b_real[N*i], &b_imag[N*i], 
         buffer_real, buffer_imag, 1);
      for (j=0; j<N; j++) {
         a_real[i+N/4*j] = buffer_real[j];
         a_imag[i+N/4*j] = buffer_imag[j];
      }
   }
   
   /* Display the results */
   for(i=0; i<N*N; i++) {
      printf("%f + %fi\n", ((float*)a_real)[i],
         ((float*)a_imag)[i]);
   }
   return 0;
}
