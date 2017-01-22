#include <stdio.h>
#include "alf.h"

int example_handler(alf_task_handle_t tk_handle, unsigned int event, void* data) {

   /* select event type and respond */
   switch(event) {     
      case ALF_TASK_EVENT_FINALIZED:
         printf("The task is finalized.\n"); break;
      case ALF_TASK_EVENT_READY:
         printf("The task is ready.\n"); break;
      case ALF_TASK_EVENT_FINISHED:
         printf("The task is finished.\n"); break;
      default: 
         printf("Invalid event.\n");
   }
   return 0;
}

int main(int argc, char **argv) {
   
   /* ALF data structures */
   alf_handle_t alf_handle;
   alf_task_handle_t task_handle;
   alf_task_desc_handle_t td_handle;
   alf_wb_handle_t wb_handle;
   
   /* Names of SPU objects and functions */
   char library_name[] = "spu_alf_events.so";   
   char spu_image_name[] = "spu_alf_events";
   char kernel_name[] = "kernel";
   
   /* Initialize the alf handle and set number of accelerators */
   alf_init(NULL, &alf_handle);
   alf_num_instances_set(alf_handle, 1);
   
   /* Create and configure the task descriptor */
   alf_task_desc_create(alf_handle, 0, &td_handle);
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_IMAGE_REF_L, 
      (unsigned long long)spu_image_name);
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_LIBRARY_REF_L, 
      (unsigned long long)library_name);
   alf_task_desc_set_int64(td_handle, ALF_TASK_DESC_ACCEL_KERNEL_REF_L, 
      (unsigned long long)kernel_name);
   alf_task_desc_set_int32(td_handle, ALF_TASK_DESC_MAX_STACK_SIZE, 4096);

   /* Create the task and register the event handler */
   int ret;
   if ((ret = alf_task_create(td_handle, NULL, 1, 0, 0, &task_handle)) < 0) {
      fprintf(stderr, "alf_task_create failed, ret=%d\n", ret);
      return 1;
   }
   alf_task_event_handler_register(task_handle, &example_handler, NULL, 0, 
      ALF_TASK_EVENT_FINALIZED | ALF_TASK_EVENT_READY | ALF_TASK_EVENT_FINISHED);
   
   /* Create work blocks and add the parameter context */
   alf_wb_create(task_handle, ALF_WB_SINGLE, 1, &wb_handle);
   alf_wb_enqueue(wb_handle);
   
   /* Finalize the task, wait for it to finish, and exit */
   alf_task_finalize(task_handle);
   alf_task_wait(task_handle, -1);
   alf_task_desc_destroy(td_handle);
   alf_task_destroy(task_handle);
   alf_exit(alf_handle, ALF_EXIT_POLICY_FORCE, 0);
   return 0;
}
