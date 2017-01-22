#include <alf_accel.h>
#include <spu_intrinsics.h>

/* Add/subtract floats in buffers */
int kernel(void *task_ctx,
           void *param_ctx __attribute__ ((unused)),
           void *input_buffer,
           void *output_buffer,
           void *inout_buffer,
           unsigned int current_count __attribute__ ((unused)),
           unsigned int total_count __attribute__ ((unused))) 
{
   /* Find number of vector additions/subtractions */
   int num = *((int*)task_ctx);
   num = num/4;
   
   /* Access matrices in buffers */
   vector float *mat_one, *mat_two, *mat_three;
   mat_one = (vector float*) input_buffer;
   mat_two = (vector float*) inout_buffer;
   mat_three = (vector float*) output_buffer;
   
   /* Add/subtract vectors in processing loop */
   int i;
   for(i=0; i<num; i++) {
      mat_three[i] = spu_add(mat_one[i], mat_two[i]);
      mat_two[i] = spu_sub(mat_one[i], mat_two[i]);
   }
   return 0;
}

/* Use macros to export function names */
ALF_ACCEL_EXPORT_API_LIST_BEGIN
   ALF_ACCEL_EXPORT_API("", kernel);
ALF_ACCEL_EXPORT_API_LIST_END
