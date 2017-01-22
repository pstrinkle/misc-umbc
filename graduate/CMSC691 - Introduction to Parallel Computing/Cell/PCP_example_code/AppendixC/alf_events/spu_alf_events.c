#include <stdio.h>
#include <spu_mfcio.h>
#include <alf_accel.h>

/* Stage 3: Display the task and parameter contexts */
int kernel(void* task_context, void* param_context,
   void* in_buffer, void* out_buffer, void* inout_buffer,
   unsigned int current_count, unsigned int total_count) {

   /* Prove that the kernel function has executed */
   printf("Kernel.\n");
   return 0;
}
/* Use macros to export function names */
ALF_ACCEL_EXPORT_API_LIST_BEGIN
   ALF_ACCEL_EXPORT_API("", kernel);
ALF_ACCEL_EXPORT_API_LIST_END
