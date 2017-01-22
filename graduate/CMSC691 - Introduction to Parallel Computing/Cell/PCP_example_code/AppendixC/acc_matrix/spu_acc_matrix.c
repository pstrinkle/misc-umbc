#include <alf_accel.h>
#include <spu_intrinsics.h>
#include "acc_matrix.h"

/* Add/subtract floats in buffers */
int kernel(void *task_ctx __attribute__ ((unused)),
           void *param_ctx,
           void *input_buffer,
           void *output_buffer,
           void *inout_buffer,
           unsigned int current_count __attribute__ ((unused)),
           unsigned int total_count __attribute__ ((unused)))
{
   /* Find number of vector additions/subtractions */
   ctx_struct* ctx = (ctx_struct*)param_ctx;
   int num = ctx->num_floats/4;

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

int create_in_dtl(void *task_ctx __attribute__ ((unused)),
                  void *param_ctx,
                  void *dtl,
                  unsigned int current_count __attribute__ ((unused)),
                  unsigned int total_count __attribute__ ((unused))) 
{
   /* Access the parameter context */
   ctx_struct* ctx = (ctx_struct *) param_ctx;

   /* Create input DTL for matrix_one */
   ALF_ACCEL_DTL_BEGIN(dtl, ALF_BUF_IN, 0);
   ALF_ACCEL_DTL_ENTRY_ADD(dtl, ctx->num_floats, ALF_DATA_FLOAT, ctx->matrix_one);
   ALF_ACCEL_DTL_END(dtl);

   /* Create inout DTL for matrix_two */
   ALF_ACCEL_DTL_BEGIN(dtl, ALF_BUF_OVL_INOUT, 0);
   ALF_ACCEL_DTL_ENTRY_ADD(dtl, ctx->num_floats, ALF_DATA_FLOAT, ctx->matrix_two);
   ALF_ACCEL_DTL_END(dtl);   

   return 0;
}

int create_out_dtl(void *task_ctx __attribute__ ((unused)),
                   void *param_ctx,
                   void *dtl,
                   unsigned int current_count __attribute__ ((unused)),
                   unsigned int total_count __attribute__ ((unused)))
{
   /* Access the parameter context */
   ctx_struct* ctx = (ctx_struct *) param_ctx;

   /* Create output DTL for matrix_three */
   ALF_ACCEL_DTL_BEGIN(dtl, ALF_BUF_OUT, 0);
   ALF_ACCEL_DTL_ENTRY_ADD(dtl, ctx->num_floats, ALF_DATA_FLOAT, ctx->matrix_three);
   ALF_ACCEL_DTL_END(dtl);

   return 0;
}

ALF_ACCEL_EXPORT_API_LIST_BEGIN
   ALF_ACCEL_EXPORT_API("", kernel);
   ALF_ACCEL_EXPORT_API("", create_in_dtl);
   ALF_ACCEL_EXPORT_API("", create_out_dtl);
ALF_ACCEL_EXPORT_API_LIST_END

