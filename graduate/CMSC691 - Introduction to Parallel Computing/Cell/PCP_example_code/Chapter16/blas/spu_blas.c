#import <stdio.h>
#import <blas_s.h>

#define B_ROWS 8
#define B_COLS 4

int main() {
   double a_mat[B_ROWS*B_ROWS] __attribute__((aligned(16)));
   double b_mat[B_ROWS*B_COLS] __attribute__((aligned(16)));
   
   /* Initialize the A matrix */
   int i, j;
   for(i=0; i<B_ROWS; i++) {
      for(j=0; j<i; j++) {
         a_mat[j + i*B_ROWS] = 0.5*j+0.5;
      }
      a_mat[i + i*B_ROWS] = (double)1.0;
      for(j=i+1; j<B_ROWS; j++) {
         a_mat[j + i*B_ROWS] = 0.0;
      }
   }
   
   /* Initialize the B matrix */
   for(i=0; i<B_ROWS*B_COLS; i++) {   
      b_mat[i] = B_ROWS*B_COLS-1-i;
   }

   /* Solve the equations */
   dtrsm_spu(B_COLS, B_ROWS, a_mat, b_mat);

   /* Display the contents of the B matrix */
   for(i=0; i<B_ROWS; i++) {
      for(j=0; j<B_COLS; j++) {
         printf("%e ",b_mat[i*B_COLS + j]);
      }
      printf("\n");
   }
   
   printf("\n");
   return 0;
}
