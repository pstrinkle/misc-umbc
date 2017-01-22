#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libfft.h"

#define NROWS 64
#define NCOLS 64

int main(int argc, char **argv) {

   /* Allocate and align memory */
   volatile unsigned int ptr;
   posix_memalign((void**)&ptr, 128, 
      sizeof(float)*2*NCOLS*NROWS);
   float **in_data = (float **)ptr;
   posix_memalign((void**)&ptr, 128, 
      sizeof(float)*2*NCOLS*NROWS);
   float **out_data = (float **)ptr;
   
   /* Initialize the input data */
   int i, j;
   float *in_array = (float*)in_data;
   for(i=0; i<NROWS; i++)
      for(j=0; j<NCOLS; j+=2) {
         if((i-NROWS/2)*(i-NROWS/2) + 
            (j-NCOLS/2)*(j-NCOLS/2) 
            < (NROWS/4)*(NCOLS/4))
            in_array[i*NROWS+j] = 1.0;
         else
            in_array[i*NROWS+j+1] = 0.0;
      }
   
   /* Perform the transform with six SPUs */
   fft_2d_handle_t handle;
   fft_2d_initialize(&handle, 6, FFT_TYPE_C2R);
   fft_2d_perform(handle, (void**)in_data, 
      (void**)out_data, NROWS, NCOLS, 0);
   fft_2d_terminate(handle);
   
   /* De-allocate memory */
   free(in_data);
   free(out_data);
   return 0;
}
