#include <stdio.h>
#include <spu_mfcio.h>

#define CESOF_TAG 27

/* The .toe symbol defined in the assembly code */
extern unsigned long long _EAR_prime;

/* The array in the SPU's Local Store */
int local_prime[16] __attribute((aligned(128)));

int main(long long spuid, char** argp, char** envp) {

   /* Display the value of _EAR_prime */
   printf("SPU Array Location: %#llx\n", _EAR_prime);

   /* Transfer the array at _EAR_prime to memory */
   mfc_get(local_prime, _EAR_prime, sizeof(local_prime), 
      CESOF_TAG, 0, 0); 
   mfc_write_tag_mask(1<<CESOF_TAG);
   mfc_read_tag_status_all();

   /* Display the array's contents */
   int i;
   for (i=0; i<16; i++)
      printf("%d ",local_prime[i]);
   printf("\n");

   return 0;
} 
