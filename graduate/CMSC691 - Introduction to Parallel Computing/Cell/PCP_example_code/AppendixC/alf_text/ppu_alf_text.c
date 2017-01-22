#include <stdio.h>
#include <string.h>
#include "alf.h"

#define NUM_ACCEL 2

int main(int argc, char **argv) {
   
   /* ALF data structures */
   alf_handle_t alf_handle;
   alf_task_handle_t task_handle;
   alf_task_desc_handle_t td_handle;
   alf_wb_handle_t wb_handle;
   
   /* Names of SPU objects and functions */
   char library_name[] = "spu_alf_text.so";   
   char spu_image_name[] = "spu_alf_text";
   char kernel_name[] = "kernel";
   char ctx_setup_name[] = "context_setup";
   char ctx_merge_name[] = "context_merge";
   
   /* Create messages to send to accelerator */
   char task_msg[] = "This is the task context";
   char param_msg[32];
   
   /* Initialize the alf handle and set number of accelerators */
   alf_init(NULL, &alf_handle);
   alf_num_instances_set(alf_handle, NUM_ACCEL);
   
   /* Create and configure the task descriptor */
   alf_task_desc_create(alf_handle, 0, &td_handle);
   alf_task_desc_set_int64(td_handle, 
      ALF_TASK_DESC_ACCEL_IMAGE_REF_L, 
      (unsigned long long)spu_image_name);
   alf_task_desc_set_int64(td_handle, 
      ALF_TASK_DESC_ACCEL_LIBRARY_REF_L, 
      (unsigned long long)library_name);
   alf_task_desc_set_int64(td_handle, 
      ALF_TASK_DESC_ACCEL_KERNEL_REF_L, 
      (unsigned long long)kernel_name);
   alf_task_desc_set_int64(td_handle, 
      ALF_TASK_DESC_ACCEL_CTX_SETUP_REF_L, 
      (unsigned long long)ctx_setup_name);
   alf_task_desc_set_int64(td_handle, 
      ALF_TASK_DESC_ACCEL_CTX_MERGE_REF_L, 
      (unsigned long long)ctx_merge_name);
   
   /* Configure the memory requirements and add the task context */
   alf_task_desc_set_int32(td_handle, 
      ALF_TASK_DESC_MAX_STACK_SIZE, 4096);
   alf_task_desc_set_int32(td_handle, 
      ALF_TASK_DESC_TSK_CTX_SIZE, sizeof(task_msg));
   alf_task_desc_set_int32(td_handle, 
      ALF_TASK_DESC_WB_PARM_CTX_BUF_SIZE, sizeof(param_msg));   
   alf_task_desc_ctx_entry_add(td_handle, ALF_DATA_BYTE,
      sizeof(task_msg));
   
   /* Create the task for cyclic work block distribution */
   int ret;
   if ((ret = alf_task_create(td_handle, (void*)task_msg, 
      NUM_ACCEL, ALF_TASK_ATTR_SCHED_FIXED | 
      ALF_TASK_ATTR_WB_CYCLIC, 1, &task_handle)) < 0) {
      fprintf(stderr, "alf_task_create failed, ret=%d\n", ret);
      return 1;
   }

   /* Create work blocks and add the parameter context */
   int i;
   for (i=0; i<NUM_ACCEL*2; i++) {
      sprintf(param_msg, "This is parameter context %d", i);
      alf_wb_create(task_handle, ALF_WB_SINGLE, 1, &wb_handle);
      alf_wb_parm_add(wb_handle, (void*)param_msg, 
         sizeof(param_msg), ALF_DATA_BYTE, 3);
      alf_wb_enqueue(wb_handle);
   }
   
   /* Finalize the task, wait for it to finish, and exit */
   alf_task_finalize(task_handle);
   alf_task_wait(task_handle, -1);
   alf_task_desc_destroy(td_handle);
   alf_task_destroy(task_handle);
   alf_exit(alf_handle, ALF_EXIT_POLICY_FORCE, 0);
   
   /* Display the changed task context */
   printf("Host: %s\n",task_msg);
   return 0;
}
