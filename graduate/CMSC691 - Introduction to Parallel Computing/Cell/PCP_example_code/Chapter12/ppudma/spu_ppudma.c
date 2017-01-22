#include <spu_mfcio.h>

int main(unsigned long long speid, 
         unsigned long long argp, 
         unsigned long long envp) {
 
   /* Read the value at the arbitrary LS address */
   int *result = (int*)0x10000;
   
   /* Wait until the value changes */
   while(*result != 42);
   printf("SPE Received the message.\n");
   return 0;
}
