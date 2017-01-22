#include <stdio.h>
#include <string.h>
#include <spu_mfcio.h>
#include <alf_accel.h>

/* Stage 1: Pre-process */
int context_setup(void *task_ctx) {
   printf("Accelerator %d of %d: Running context_setup\n",
      alf_accel_instance_id(), alf_accel_num_instances());
   return 0;
}

/* Stage 3: Display the task and parameter contexts */
int kernel(void* task_context, void* param_context,
   void* in_buffer, void* out_buffer, void* inout_buffer,
   unsigned int current_count, unsigned int total_count) {

   /* Determine the id of the accelerator and their number */
   int id = alf_accel_instance_id();
   int num_tasks = alf_accel_num_instances();
   printf("Accelerator %d of %d: %s\n", alf_accel_instance_id(), 
      alf_accel_num_instances(), (char*)task_context);
   printf("Accelerator %d of %d: %s\n", id, num_tasks, 
      (char*)param_context);
   return 0;
}

/* Stage 5: Post-process, update the task context */
int context_merge(void* source_context, void* target_context) {

   printf("Accelerator %d of %d: Running context_merge\n",
      alf_accel_instance_id(), alf_accel_num_instances());      
   strcpy(target_context, "New task context");
   return 0;
}

/* Use macros to export function names */
ALF_ACCEL_EXPORT_API_LIST_BEGIN
   ALF_ACCEL_EXPORT_API("", context_setup);
   ALF_ACCEL_EXPORT_API("", kernel);
   ALF_ACCEL_EXPORT_API("", context_merge);
ALF_ACCEL_EXPORT_API_LIST_END
