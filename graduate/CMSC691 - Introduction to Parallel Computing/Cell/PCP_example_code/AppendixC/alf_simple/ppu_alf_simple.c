#include <stdio.h>
#include "alf.h"

int main(int argc, char **argv) {
   
   /* Declare variables - info vars must be unsigned int */
   alf_handle_t alf_handle;
   unsigned int num_accel, host_mem, accel_align;
   
   /* Initialize the alf handle and access system info */
   alf_init(NULL, &alf_handle);
   alf_query_system_info(alf_handle, ALF_QUERY_NUM_ACCEL, 
      ALF_ACCEL_TYPE_SPE, &num_accel); 
   alf_query_system_info(alf_handle, ALF_QUERY_HOST_MEM_SIZE, 
      ALF_ACCEL_TYPE_SPE, &host_mem); 
   alf_query_system_info(alf_handle, ALF_QUERY_ACCEL_ADDR_ALIGN, 
      ALF_ACCEL_TYPE_SPE, &accel_align); 
   
   /* Display the results */
   printf("Number of accelerators: %d\n", num_accel);
   printf("Host memory: %d\n", host_mem);
   printf("Accelerator memory alignment: %d\n", accel_align);
   return 0;
}
