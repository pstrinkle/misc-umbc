#include <spu_mfcio.h>
#include <stdint.h>
#include <spu_intrinsics.h>

int main(vector unsigned long long arg1, 
         vector unsigned long long arg2, 
         vector unsigned long long arg3) {
 
   printf("High: %llu\n",spu_extract(arg1,0));
   printf("Low: %llu\n",spu_extract(arg1,1));
   return 0;
}
