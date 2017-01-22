#define MCONFIG_SPU          1
#define MCONFIG_STI_EMITTER  1

#include "common/mambo.h"
#include "emitter/emit_collector.h"
#include "trans_id.h"
#include <memory.h>

EMITTER_CONTROLS eControl;

int main (int argc, char **argv) {

   int        pid   = 0;
   EMIT_DATA  *ePtr = NULL;
   FILE       *fp   = NULL;

   /* Obtain the process id */
   pid = atoi(argv[1]);

   /* Open the output file */
   if ((fp = fopen("emit.dat", "w")) == NULL) {
      fprintf(stderr, "Cannot open emit.dat\n");
      exit(-1);
   }
   
   /* Attach to the simulator and wait */
   int rdr = EMIT_AttachReader(pid, &eControl, 0, TRUE);
   if (rdr == -1) {
      fprintf(stderr, "ERROR: Failed to attach reader\n");
      return(0);
   }
   
   EMIT_ReadyWait(&eControl, rdr, TRUE);
   
   /* Cycle through EMIT_DATA objects */
   do {
      EMIT_AdvanceCurrent(&eControl, rdr);
      ePtr = EMIT_CurrentEntry(&eControl, rdr);
            
      switch (ePtr->header.head.tag) {
        
         /* Respond to SPU memory access */
         case TAG_APU_MEMREAD:
            fprintf(fp, "SPU memory read value: %lld\n",
               ePtr->apu_mem.value);
            break;

         default:
            break;
      }
   } while (ePtr->header.head.tag != TAG_FOOTER);

   /* Detach the reader and terminate operation */
   EMIT_Quit(&eControl, rdr, TRUE);
   fclose(fp);
   return(1);
}
