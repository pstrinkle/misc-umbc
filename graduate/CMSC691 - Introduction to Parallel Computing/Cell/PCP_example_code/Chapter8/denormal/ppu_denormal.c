#include <stdio.h>
#include <altivec.h>

int main(int argc, char **argv) {

   vector float denormals, zeroes;	

   /* A vector containing four denormal values */
   denormals = (vector float)
      {5.9e-40, 5.9e-40, 5.9e-40, 5.9e-40};

   zeroes = (vector float){0.0, 0.0, 0.0, 0.0};

   /* Compare the denormal values to zero */
   printf("Result: %d\n", vec_all_eq(denormals, zeroes));

   return 0;
}
