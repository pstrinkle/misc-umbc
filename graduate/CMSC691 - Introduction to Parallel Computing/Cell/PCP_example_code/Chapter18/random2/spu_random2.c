#include <stdio.h>
#include <stdlib.h>
#include <spu_intrinsics.h>
#include <sys/time.h>
#include <mc_rand.h>
#include <simdmath.h>

int main() {

   int i, j;

   /* The input and output arrays */
   vector float uniform_vec[4];
   vector float normal_vec[4];
   
   /* Generate a seed */
   struct timeval time;
   gettimeofday(&time, NULL);

   /* Generate the random numbers */
   mc_rand_mt_init(time.tv_sec);
   mc_rand_mt_0_to_1_array_f4(4, uniform_vec);
   
   /* Transform the array */
   mc_transform_po_array_f4(4, uniform_vec, normal_vec,
      &mc_rand_mt_0_to_1_f4);

   /* Display the results */
   printf("Uniform Distribution: \n");
   for(i=0; i<4; i++) 
      for(j=0; j<4; j++)
         printf("%f ",spu_extract(uniform_vec[i], j));
   
   printf("\n\nNormal Distribution: \n");
   for(i=0; i<4; i++) 
      for(j=0; j<4; j++)
         printf("%f ",spu_extract(normal_vec[i], j));
   printf("\n");
   return 0;
}

