#include <stdio.h>
#include <stdlib.h>
#include <spu_intrinsics.h>
#include <sys/time.h>
#include <mc_rand.h>

int main(int argc, char **argv) {

   int i, j;
   vector unsigned int int_vec;
   vector float float_vec;
   vector double double_vec[4];
   
   /* Get the current time to use as seed */
   struct timeval time;
   gettimeofday(&time, NULL);

   /* The hardware number generator */
   printf("\nHardware Generator:\n");   
   if(mc_rand_hw_init() == 0) {
      int_vec = mc_rand_hw_u4();
      for(i=0; i<4; i++)
         printf("%u ",spu_extract(int_vec, i));
      printf("\n\n");
   }
   else
      printf("Hardware RNG is not available.\n\n");
   
   /* The Kirkpatrick Stoll PRNG */
   mc_rand_ks_init(time.tv_sec);
   float_vec = mc_rand_ks_0_to_1_f4();
   printf("Kirkpatrick-Stoll:\n");
   for(i=0; i<4; i++)
      printf("%f ", spu_extract(float_vec, i));
   printf("\n\n");
   
   /* The Mersenne Twister PRNG */
   mc_rand_mt_init(time.tv_sec);
   mc_rand_mt_minus1_to_1_array_d2(4, double_vec);
   printf("Mersenne Twister:\n");
   for(i=0; i<4; i++) {
      for(j=0; j<2; j++)
         printf("%g ",spu_extract(double_vec[i], j));
      printf("\n");
   }
   
   return 0;
}
