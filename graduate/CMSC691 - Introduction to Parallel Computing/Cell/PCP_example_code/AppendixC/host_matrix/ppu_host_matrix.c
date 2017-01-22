#include <stdio.h>
#include <string.h>
#include "alf.h"

#define N 512 
#define NUM_BLOCKS 16
#define NUM_ACCEL 4

int main(int argc, char **argv) {
   
   /* ALF data structures */
   alf_handle_t alf_handle;
   alf_task_handle_t task_handle;
   alf_task_desc_handle_t td_handle;
   alf_wb_handle_t wb_handle;
   
   /* Names of SPU objects and functions */
   char library_name[] = "spu_host_matrix.so";   
   char spu_image_name[] = "spu_host_matrix";
   char kernel_name[] = "kernel";

   /* Create matrices */
   float matrix_one[N][N] __attribute__ ((__aligned__(128)));
   float matrix_two[N][N] __attribute__ ((__aligned__(128)));
   float matrix_three[N][N] __attribute__ ((__aligned__(128)));
   
   /* Task context: number of floats in each buffer */
   int num_floats = N*N/NUM_BLOCKS;
   int i, j;
   
   /* Initialize the matrices */
   for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
         matrix_one[i][j] = (float)(j+i*N);
         matrix_two[i][j] = (float)(j+i*N);
         matrix_three[i][j] = (float)(j+i*N);
      }
   }
  
   /* Initialize the alf handle and set number of accelerators */
   alf_init(NULL, &alf_handle);
   alf_num_instances_set(alf_handle, NUM_ACCEL);
   
   /* Create and configure the task descriptor */
   alf_task_desc_create(alf_handle, 0, &td_handle);

   /* Identify the name of the object library */
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_LIBRARY_REF_L, 
      (unsigned long long)library_name);
      
   /* Identify the name of the SPU image */
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_IMAGE_REF_L, 
      (unsigned long long)spu_image_name);
   
   /* Identify the name of the kernel */
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_KERNEL_REF_L, 
      (unsigned long long)kernel_name);
   
   /* Configure the memory requirements and add the task context */
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_MAX_STACK_SIZE, 4096);
      
   /* Allocate memory for the input buffer (matrix_one) */
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_WB_IN_BUF_SIZE, 
      N*N*sizeof(float)/NUM_BLOCKS);

   /* Allocate memory for the inout buffer (matrix_two) */
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_WB_INOUT_BUF_SIZE, 
      N*N*sizeof(float)/NUM_BLOCKS);

   /* Allocate memory for the output buffer (matrix_three) */
  alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_WB_OUT_BUF_SIZE, 
      N*N*sizeof(float)/NUM_BLOCKS);    
 
   /* Allocate memory for the task context */
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_TSK_CTX_SIZE, 
      sizeof(num_floats));
   alf_task_desc_ctx_entry_add(td_handle, ALF_DATA_INT32, 1);
      
   /* Create the task for cyclic work block distribution */
   int ret;
   if ((ret = alf_task_create(td_handle, (void*)&num_floats, 
         0, 0, 0, &task_handle)) < 0) {
      fprintf(stderr, "alf_task_create failed, ret=%d\n", ret);
      return 1;
   }

   for (i=0; i<NUM_BLOCKS; i++) {

      /* Create the work block */
      alf_wb_create(task_handle, ALF_WB_SINGLE, 0, &wb_handle);

      /* DTL: store matrix_one in an input buffer */
      alf_wb_dtl_begin(wb_handle, ALF_BUF_IN, 0);
      alf_wb_dtl_entry_add(wb_handle, &matrix_one[i*N/NUM_BLOCKS][0], 
         N*N/NUM_BLOCKS, ALF_DATA_FLOAT);
      alf_wb_dtl_end(wb_handle);

      /* DTL: store matrix_two in an inout buffer */
      alf_wb_dtl_begin(wb_handle, ALF_BUF_OVL_INOUT, 0);
      alf_wb_dtl_entry_add(wb_handle, &matrix_two[i*N/NUM_BLOCKS][0], 
         N*N/NUM_BLOCKS, ALF_DATA_FLOAT);
      alf_wb_dtl_end(wb_handle);

      /* DTL: store matrix_three in an output buffer */
      alf_wb_dtl_begin(wb_handle, ALF_BUF_OUT, 0);
      alf_wb_dtl_entry_add(wb_handle, &matrix_three[i*N/NUM_BLOCKS][0], 
         N*N/NUM_BLOCKS, ALF_DATA_FLOAT);
      alf_wb_dtl_end(wb_handle);

      /* Enqueue the work block in the task */
      alf_wb_enqueue(wb_handle);
   }

   /* Finalize the task, wait for it to finish, and exit */
   alf_task_finalize(task_handle);
   alf_task_wait(task_handle, -1);
   alf_task_desc_destroy(td_handle);
   alf_task_destroy(task_handle);
   alf_exit(alf_handle, ALF_EXIT_POLICY_FORCE, 0);
   
   /* Test content of matrix_two */
   for(i=0; i<N; i++)
      for(j=0; j<N; j++) {
         if(matrix_two[i][j] > 0.00001) {
            printf("Subtraction failed at index %d, %d\n", i, j);
            return -1;
         }
         
         if(matrix_three[i][j] - 2*(j+i*N) > 0.00001) {
            printf("Addition failed at index %d, %d\n", i, j);
            return -1;
         }
      }
   
   printf("Matrix addition and subtraction performed successfully.\n");
   return 0;
}
