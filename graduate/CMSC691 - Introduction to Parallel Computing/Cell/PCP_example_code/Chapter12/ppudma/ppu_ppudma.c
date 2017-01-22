#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <pthread.h>

#define TAG 2

/* Program handle representing the SPU object */
extern spe_program_handle_t spu_ppudma;

/* The data sent to the pthread */
typedef struct ppu_pthread_data {
    spe_context_ptr_t speid;
    pthread_t pthread;
} ppu_pthread_data_t;

/* The function executed in the pthread */
void *ppu_pthread_function(void *arg) {
   ppu_pthread_data_t *data = (ppu_pthread_data_t *)arg;
   int retval;
   unsigned int entry = SPE_DEFAULT_ENTRY;
   if ((retval = spe_context_run(data->speid, 
      &entry, 0, NULL, NULL, NULL)) < 0) {
      perror("spe_context_run");
      exit (1);
   }
   pthread_exit(NULL);
}

ppu_pthread_data_t data;

int main() {
   int retval;
   
	/* The value to be transfered into the SPU's LS */
   unsigned int check_value[4] __attribute__ ((aligned (16)));
  
   /* The arbitrary LS address to hold the data */
   unsigned int ls_addr = 0x10000;
   
   /* Holds the result of the tag status read */
   unsigned int *tag_status;
   
   /* Create the SPE Context */
   data.speid = spe_context_create(0, NULL);
   if (!data.speid) {
      perror("spe_context_create");
      exit(1);
   }
     
   /* Load the program into the context */
   retval = spe_program_load(data.speid, &spu_ppudma);
   if (retval) {
      perror("spe_program_load");
      exit(1);
   }

   /* Create thread */
   if ((retval = pthread_create(&data.pthread, 
      NULL, &ppu_pthread_function, &data)) != 0) {
      perror("pthread_create");
      exit (1);
   }
   
   /* Initialize the data */
   int i;
   for(i=0; i<4; i++)
      check_value[i] = 42;

   /* Send check_value to the SPU */
   spe_mfcio_get(data.speid, ls_addr, check_value, sizeof(check_value), TAG, 0, 0);

   /* Wait for the data transfer to finish */
   spe_mfcio_tag_status_read(data.speid, 1<<TAG, SPE_TAG_ANY, tag_status);
   
   if ((retval = pthread_join(data.pthread, NULL)) != 0) {
      perror("pthread_join");
      exit (1);
   }
   
   if ((retval = spe_context_destroy(data.speid)) != 0) {
      perror("spe_context_destroy");
      exit (1);
   }

   return 0;
}
