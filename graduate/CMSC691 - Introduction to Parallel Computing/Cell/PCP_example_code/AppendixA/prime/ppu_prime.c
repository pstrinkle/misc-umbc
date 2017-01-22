#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>

/* Initializes the memory location contained in .toe */
int prime[16] __attribute((aligned(128))) 
   = {2, 3, 5, 7, 11, 13, 17, 19, 
      23, 29, 31, 37, 41, 43, 47, 53};

/* Accesses the handle in the CESOF file */
extern spe_program_handle_t spu_prime_handle;

int main(int argc, char **argv) {
   int ret;
   spe_context_ptr_t ctx;
   unsigned int entry_point;
   spe_stop_info_t stop_info;
   
   /* Display the EA of the array */
   printf("PPU array location: %#llx\n", 
      (unsigned long long)prime);
   
   /* Create the SPE Context */
   ctx = spe_context_create(0, NULL);
   if (!ctx) {
      perror("spe_context_create");
      exit(1);
   }

   /* Load the program into the context */
   ret = spe_program_load(ctx, &spu_prime_handle);
   if (ret) {
      perror("spe_program_load");
      exit(1);
   }
   
   /* Run the program */
   entry_point = SPE_DEFAULT_ENTRY;
   ret = spe_context_run(ctx, &entry_point, 0, 
      NULL, NULL, &stop_info);
   if (ret < 0) {
      perror("spe_context_run");
      exit(1);
   }
   
   /* Deallocate the context */
   ret = spe_context_destroy(ctx);
   if (ret) {
      perror("spe_context_destroy");
      exit(1);
   }
 
   return 0;
}
