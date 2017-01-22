#include <stdio.h>
#include <libmatrix.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv) {

   int i, j;
   vector float scale = (vector float){1.0, 2.0, 3.0, 4.0};
   
   /* Declare 4x4 matrices, initialize input matrix */
   vector float in[4], out[4];
   in[0] = (vector float){11.0, 12.0, 13.0, 14.0};
   in[1] = (vector float){21.0, 22.0, 23.0, 24.0};
   in[2] = (vector float){31.0, 32.0, 33.0, 34.0};
   in[3] = (vector float){41.0, 42.0, 43.0, 44.0};

   /* Scale matrix by vector */
   scale_matrix4x4(out, in, scale);
   printf("Scaled Matrix:\n");
   for(i=0; i<4; i++) {
      for(j=0; j<4; j++)
         printf("%f ", spu_extract(out[i], j));
      printf("\n");
   }
   
   /* Multiply matrix by itself */
   mult_matrix4x4(out, in, in);
   printf("\nMatrix Product:\n");
   for(i=0; i<4; i++) {
      for(j=0; j<4; j++)
         printf("%f ", spu_extract(out[i], j));
      printf("\n");
   }
   return 0;
}
