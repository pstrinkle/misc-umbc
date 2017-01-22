#include <stdio.h>
#include <stdlib.h>
#include <alf.h>
#include "acc_matrix.h"

#define N 512
#define NUM_ACCEL 4
#define NUM_BLOCKS 64

int main() {

   /* Name of SPU objects and functions */
   char library_name[] = "spu_acc_matrix.so";
   char spu_image_name[] = "spu_acc_matrix";
   char kernel_func[] = "kernel";
   char in_dtl_func[] = "create_in_dtl";
   char out_dtl_func[] = "create_out_dtl";

   /* Create matrices of float values */
   float matrix_one[N][N] __attribute__ ((__aligned__(128)));
   float matrix_two[N][N] __attribute__ ((__aligned__(128)));
   float matrix_three[N][N] __attribute__ ((__aligned__(128)));

   /* ALF data structures */
   alf_handle_t alf_handle;
   alf_task_desc_handle_t td_handle;
   alf_task_handle_t task_handle;
   alf_wb_handle_t wb_handle;
   
   /* Parameter context to hold data */
   ctx_struct param_ctx __attribute__ ((aligned(128)));
   
   /* Set number of floats in each buffer */
   int num_floats = N*N/NUM_BLOCKS;
   int i, j, ret;

   /* Initialize matrices */
   for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
         matrix_one[i][j] = (float) (j+i*N);
         matrix_two[i][j] = (float) (j+i*N);
         matrix_three[i][j] = 0.0f;
      }
   }
  
   /* Initialize the alf handle and set number of accelerators */
   alf_init(NULL, &alf_handle);
   alf_num_instances_set(alf_handle, NUM_ACCEL);

   /* Create the task descriptor */
   alf_task_desc_create(alf_handle, 0, &td_handle);

   /* Identify image, library, and functions */
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_IMAGE_REF_L, (unsigned long long)spu_image_name);
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_LIBRARY_REF_L, (unsigned long long)library_name);
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_KERNEL_REF_L, (unsigned long long)kernel_func);
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_INPUT_DTL_REF_L, (unsigned long long)in_dtl_func);
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_OUTPUT_DTL_REF_L, (unsigned long long)out_dtl_func);

   /* Perform partitioning on the accelerator */
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_PARTITION_ON_ACCEL, 1);
   
   /* Configure memory */
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_MAX_STACK_SIZE, 4096);
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_WB_PARM_CTX_BUF_SIZE, sizeof(ctx_struct));
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_WB_IN_BUF_SIZE, num_floats*sizeof(float));  
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_WB_OUT_BUF_SIZE, num_floats*sizeof (float));    
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_WB_INOUT_BUF_SIZE, num_floats*sizeof (float));     

   /* Create the task */
   if ((ret = alf_task_create(td_handle, NULL, 1, 0, 0, &task_handle)) < 0) {
      fprintf(stderr, "alf_task_create failed, ret=%d\n", ret);
      return 1;
   }

   param_ctx.num_floats = num_floats;
   for (i=0; i<N; i+=N/NUM_BLOCKS) {

      /* Create the work block */
      alf_wb_create(task_handle, ALF_WB_SINGLE, 0, &wb_handle);

      /* Configure and add parameter to the work block */
      param_ctx.matrix_one = (unsigned long long)&matrix_one[i][0];
      param_ctx.matrix_two = (unsigned long long)&matrix_two[i][0];
      param_ctx.matrix_three = (unsigned long long)&matrix_three[i][0];
      alf_wb_parm_add(wb_handle, (void *)(&param_ctx), sizeof(param_ctx), ALF_DATA_BYTE, 0);

      /* Enqueue the work block in the task */
      alf_wb_enqueue(wb_handle);
   }

   /* Finalize the task, wait for it to finish, and exit */
   alf_task_finalize(task_handle);
   alf_task_wait(task_handle, -1);
   alf_task_desc_destroy(td_handle);
   alf_task_destroy(task_handle);   
   alf_exit(alf_handle, ALF_EXIT_POLICY_WAIT, 0);

   /* Test content of matrix_two and matrix_three */
   for(i=0; i<N; i++)
      for(j=0; j<N; j++) {
         if(matrix_two[i][j] != 0.0) {
            printf("Subtraction failed at index %d, %d\n", i, j);
            printf("Result equals %f, %d\n", matrix_two[i][j], j+i*N);
            return -1; 
         }
         
         if(matrix_three[i][j] != (float)2*(j+i*N)) {
            printf("Addition failed at index %d, %d\n", i, j);
            return -1;
         }
      }

   printf("Matrix addition and subtraction performed successfully.\n");
   return 0;
}
