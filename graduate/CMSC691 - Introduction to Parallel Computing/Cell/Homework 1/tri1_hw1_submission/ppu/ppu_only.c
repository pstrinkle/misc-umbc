
#include <stdio.h>
#include <stdlib.h>
#include <ppu_intrinsics.h>

#define N 2048

float srcbuf[N][N] __attribute__ ((aligned(128)));
float destbuf[N][N] __attribute__ ((aligned(128)));

int main(int argc, char **argv)
{
   int i, j, test;
   unsigned long long startTime, stopTime;
   float temp = 0;

   /* initialize whole thing to 1.1 */
   for (i = 0; i < N; ++i)
      for (j = 0; j < N; ++j)
	 srcbuf[i][j] = 1.1;

   /* set first row of first block to sig */
   for (i = 0; i < N; ++i)
      srcbuf[0][i] = i + 0.1;

   startTime = __mftb();
   for (i = 0; i < N; ++i)
   {
      for (j = i; j < N; ++j)
      {
	 temp = srcbuf[i][j];
	 destbuf[i][j] = srcbuf[j][i];
	 destbuf[j][i] = temp;
      }
   }
   stopTime = __mftb();

   printf("Time Calculating: %fs\n", (stopTime - startTime) / (double)14318000.0);
   
   test = 1;

   for (i = 0; i < N; ++i)
   {
      for (j = 0; j < N; ++j)
      {
	 if (srcbuf[i][j] != destbuf[j][i])
	 {
	    test = 0;
	    break;
	 }
	 
      }
   }

   if (test)
      printf("DMA Passed\n");
   else
      printf("DMA Failed\n");

   return 0;
}
