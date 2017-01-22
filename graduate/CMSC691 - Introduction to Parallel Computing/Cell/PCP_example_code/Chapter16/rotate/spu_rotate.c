#include <stdio.h>
#include <libmatrix.h>
#include <libvector.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv) {

   int i;
   vector float rot_matrix[4], quat, quat_conj;
   vector float axis = (vector float){.7071, .5, .5, 0};
   vector float point = (vector float){2.0, 2.0, 2.0, 0};
   float angle = 1.0472; /* 30 deg in radians */
   
   /* Declare output vectors */
   vector float matrix_out, quat_out;
   
   /* Create the rotation matrix */
   rotate_matrix4x4(rot_matrix, axis, angle);
   
   /* Rotate point using the matrix */
   float temp;
   temp = dot_product3(rot_matrix[0], point);
   matrix_out = spu_insert(temp, matrix_out, 0);
   
   temp = dot_product3(rot_matrix[1], point);
   matrix_out = spu_insert(temp, matrix_out, 1);
   
   temp = dot_product3(rot_matrix[2], point);
   matrix_out = spu_insert(temp, matrix_out, 2);
   
   temp = dot_product3(rot_matrix[3], point);
   matrix_out = spu_insert(temp, matrix_out, 3);
   
   printf("Rotation by matrix:\n ");
   for (i=0; i<4; i++)
      printf("%f ",(float)spu_extract(matrix_out, i));

   /* Convert the rotation matrix into a quaternion */
   quat = rot_matrix4x4_to_quat(rot_matrix); 
   
   /* Rotate point using quaternion */
   vector float conv = (vector float){-1, -1, -1, 1};
   quat_conj = spu_mul(quat, conv);
   quat_out = mult_quat(mult_quat(quat, point), quat_conj);
   
   printf("\n\nRotation by quaternion:\n ");
   for (i=0; i<4; i++)
      printf("%f ",(float)spu_extract(quat_out, i));
   printf("\n");
   return 0;
}
