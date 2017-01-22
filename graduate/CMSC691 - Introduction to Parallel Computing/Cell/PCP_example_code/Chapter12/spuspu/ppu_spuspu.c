#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <pthread.h>

#define TAG 3

/* The data sent to the pthread */
typedef struct ppu_pthread_data {
    spe_context_ptr_t speid;
    pthread_t pthread;
    unsigned long long *argp;
} ppu_pthread_data_t;

/* The function executed in the pthread */
void *ppu_pthread_function(void *arg) {
   ppu_pthread_data_t *data = (ppu_pthread_data_t *)arg;
   int retval;
   unsigned int entry = SPE_DEFAULT_ENTRY;
   if ((retval = spe_context_run(data->speid, 
      &entry, 0, data->argp, NULL, NULL)) < 0) {
      perror("spe_context_run");
      exit (1);
   }
   pthread_exit(NULL);
}

extern spe_program_handle_t spu_spuspu;
ppu_pthread_data_t data[2];
unsigned long long control_block[2];

int main() {
   int i, retval;
   
   for (i=0; i<2; i++) {
      /* Create context */
      if ((data[i].speid = spe_context_create
         (SPE_MAP_PS, NULL)) == NULL) {
         perror("spe_context_create");
         exit(1);
      }
   }
   
   /* Set SPU init data equal to the LS addresses */
   data[0].argp = spe_ls_area_get(data[1].speid);
   data[1].argp = spe_ls_area_get(data[0].speid);
   
   /* Create contexts and threads */
   for (i=0; i<2; i++) {
   
      /* Load program into the context */
      if ((retval = spe_program_load(data[i].speid, 
         &spu_spuspu)) != 0) {
         perror("spe_program_load");
         exit(1);
      }
      
      /* Create thread */
      if ((retval = pthread_create(&data[i].pthread, 
         NULL, &ppu_pthread_function, &data[i])) != 0) {
         perror("pthread_create");
         exit(1);
      }
   }
   
   for (i=0; i<2; i++) {
   
      /* Wait for the threads */
      if ((retval = pthread_join
          (data[i].pthread, NULL)) != 0) {
          perror("pthread_join");
          exit(1);
      }
      
      /* Deallocate the contexts */
      if ((retval = spe_context_destroy 
          (data[i].speid)) != 0) {
          perror("spe_context_destroy");
          exit(1);
      }
   }
   return 0;
}
