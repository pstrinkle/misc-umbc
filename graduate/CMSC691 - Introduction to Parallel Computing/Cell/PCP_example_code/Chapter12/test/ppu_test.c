#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <ppu_intrinsics.h>

extern spe_program_handle_t spu_test;  // SPU program handle

int main(int argc, char **argv) {
   spe_context_ptr_t spe;            // SPU context
   unsigned int entry_point;         // SPU start address
   int i, retval;                       // Return value 
   spe_stop_info_t stop_info;        // Stop information
   
   unsigned long long ints[6];
   for(i=0; i<6; i++)
      ints[i] = i;
   
   // Create the SPE Context
   spe = spe_context_create(0, NULL);
   if (!spe) {
      perror("spe_context_create");
      exit(1);
   }
   
   // Load the program into the context
   retval = spe_program_load(spe, &spu_test);
   if (retval) {
      perror("spe_program_load");
      exit(1);
   }
   
   unsigned long long start = __mftb();
   // Run the program inside the context
   entry_point = SPE_DEFAULT_ENTRY;
   retval = spe_context_run(spe, &entry_point, SPE_RUN_USER_REGS, 
                            ints, NULL, &stop_info);
   if (retval < 0) {
      perror("spe_context_run");
      exit(1);
   }
   unsigned long long end = __mftb();
   printf("Time: %lld\n",(end-start));
   
   // Deallocate the context
   retval = spe_context_destroy(spe);
   if (retval) {
      perror("spe_context_destroy");
      exit(1);
   }
   return 0;
}
