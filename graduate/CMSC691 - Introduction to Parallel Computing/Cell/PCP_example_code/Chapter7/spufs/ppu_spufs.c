#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>

extern spe_program_handle_t spu_spufs;  /* SPU program handle */

int main(int argc, char **argv) {

   spe_context_ptr_t ctx;               /* Context */
   unsigned int entry_point;            /* Start address */
   int retval;                          /* Return value */
   spe_stop_info_t stop_info;           /* Stop info */
   char temp[128];                      /* Char buffer */     
   struct dirent **spu_files;           /* Array of file names */
   FILE *file;                          /* File in SPUFS */

   /* Create the SPE context */
   ctx = spe_context_create(0, NULL);
   if (!ctx) {
      perror("spe_context_create");
      exit(1);
   }
   
   /* Load the program handle into the context */
   retval = spe_program_load(ctx, &spu_spufs);
   if(retval) {
      perror("spe_program_load");
      exit(1);
   }   
   
   /* Execute the program inside the context */
   entry_point = SPE_DEFAULT_ENTRY;
   retval = spe_context_run(ctx, &entry_point, 0, 
                         NULL, NULL, &stop_info);
   if (retval < 0) {
      perror("spe_context_run");
      exit(1);
   }
   
   /* Find the context's ID */
   int n = scandir("/spu", &spu_files, NULL, alphasort);
   while(n--)
      if(!strncmp(spu_files[n]->d_name, "spethread", 9)) {
         sprintf(temp, "/spu/%s/phys-id", spu_files[n]->d_name);
         file = fopen(temp, "r");
         fgets(temp, 128, file);
         printf("context = %s, physid = %s\n", spu_files[n]->d_name, temp);
         fclose(file);
      }
   free(spu_files);
   
   /* Destroy the context */
   retval = spe_context_destroy(ctx);
   if (retval) {
      perror("spe_context_destroy");
      exit(1);
   }
   return 0;
}
