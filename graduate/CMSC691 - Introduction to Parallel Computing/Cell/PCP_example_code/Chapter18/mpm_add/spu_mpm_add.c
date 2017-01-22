#include <stdio.h>
#include <libmpm.h>
#include <spu_intrinsics.h>

#define SIZE 2

int main(int argc, char **argv) {

   int i, j;

   /* Create multi-precision values x, y, and z */
   vector unsigned int x[SIZE], y[SIZE], z[SIZE];
   
   /* Create values to hold the carry, temp sum, and sum */
   vector unsigned int carry[SIZE], tmp_sum[SIZE], 
      sum[SIZE+1];
   
   for (i=0; i<SIZE; i++) {
      x[i] = (vector unsigned int)
         {0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA};
      y[i] = (vector unsigned int)
         {0xBBBBBBBB, 0xBBBBBBBB, 0xBBBBBBBB, 0xBBBBBBBB};
      z[i] = (vector unsigned int)
         {0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC};
      carry[i] = (vector unsigned int)
         {0x00000000, 0x00000000, 0x00000000, 0x00000000};
      tmp_sum[i] = (vector unsigned int)
         {0x00000000, 0x00000000, 0x00000000, 0x00000000};         
   }
   
   /* Perform the addition */
   mpm_add_partial(tmp_sum, x, y, carry, SIZE);
   mpm_add_partial(tmp_sum, z, tmp_sum, carry, SIZE);
   
   /* Set the first vector in sum */
   vector unsigned char sum_vec = {128, 128, 128, 128, 128, 
      128, 128, 128, 128, 128, 128, 128, 28, 29, 30, 31};
   sum[0] = spu_shuffle(carry[0], carry[0], sum_vec);
   
   /* Shift the rest of the carry values into the sum */
   sum_vec = (vector unsigned char){4, 5, 6, 7, 
      8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};   
   for (i=1; i<SIZE; i++) {
      sum[i] = spu_shuffle(carry[i-1], carry[i], sum_vec);
   }

   /* Shift the last carry value */
   sum[SIZE] = spu_slqwbyte(carry[SIZE-1], 
      sizeof(unsigned int));  
   
   /* Add the sum to the tmp_sum */
   mpm_add2(sum, tmp_sum, SIZE, sum, SIZE+1);
   
   /* Display results */
   printf("Sum:\n");
   for (i=0; i<SIZE+1; i++) {
      for (j=0; j<4; j++)
         printf("%08x ", spu_extract(sum[i], j));
      printf("\n");
   }
   return 0;
}
