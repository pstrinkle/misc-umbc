#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <ppu_intrinsics.h>
#include <pthread.h>

/* The data sent to the pthread */
typedef struct ppu_pthread_data {
    spe_context_ptr_t speid;
    pthread_t pthread;
    void *argp;
    void *id;
} ppu_pthread_data_t;

/* The function executed in the pthread */
void *ppu_pthread_function(void *arg) {
   ppu_pthread_data_t *data = (ppu_pthread_data_t *)arg;
   int retval;
   unsigned int entry = SPE_DEFAULT_ENTRY;
   if ((retval = spe_context_run(data->speid, 
      &entry, 0, data->argp, data->id, NULL)) < 0) {
      perror("spe_context_run");
      exit (1);
   }
   pthread_exit(NULL);
}

/* SPU initialization data */
typedef struct _control_block {
   unsigned long long ea_addr[5];
   unsigned long long pad[3];
} control_block;

/* Program handle representing the SPU object */
extern spe_program_handle_t spu_sigsync;
ppu_pthread_data_t data[5];

int main() {
   int i, retval;
	spe_context_ptr_t spe;
   control_block cb __attribute__ ((aligned (128)));
   spe_sig_notify_1_area_t *sig_area;

   for (i=0; i<5; i++) {
      /* Create context */
      if ((data[i].speid = spe_context_create(SPE_CFG_SIGNOTIFY1_OR | SPE_MAP_PS, NULL)) == NULL) {
         perror("spe_context_create");
         exit(1);
      }
      
      /* Load program into the context */
      if ((retval = spe_program_load(data[i].speid, &spu_sigsync)) != 0) {
         perror("spe_program_load");
         exit (1);
      }
      
      /* Initialize control block and set parameter */
      sig_area = (spe_sig_notify_1_area_t *)spe_ps_area_get(data[i].speid, SPE_SIG_NOTIFY_1_AREA);
      cb.ea_addr[i] = (unsigned long long)&(sig_area->SPU_Sig_Notify_1);
      data[i].id = (void*)i;
      
      if (i != 0)
         data[i].argp = (void*)cb.ea_addr[0];
      else
         data[i].argp = &cb;
   }
   
   for (i=0; i<5; i++) {
      /* Create thread */
      if ((retval = pthread_create(&data[i].pthread, 
         NULL, &ppu_pthread_function, &data[i])) != 0) {
         perror("pthread_create");
         exit (1);
      }
   }

   
   for (i = 0; i<5; i++) {
   
      /* Wait for the threads to complete */
      if ((retval = pthread_join
          (data[i].pthread, NULL)) != 0) {
          perror("pthread_join");
          exit (1);
      }
      
      /* Deallocate the contexts */
      if ((retval = spe_context_destroy 
          (data[i].speid)) != 0) {
          perror("spe_context_destroy");
          exit (1);
      }
   }
}
