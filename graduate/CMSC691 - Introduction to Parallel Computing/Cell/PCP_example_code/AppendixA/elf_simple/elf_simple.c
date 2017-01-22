#include <err.h>
#include <gelf.h>
#include <fcntl.h>
#include <sysexits.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
   int fd;
   Elf *efile;
   GElf_Ehdr ehdr;
   const char filename[] = "ppu_prime";
   
   /* Open the ELF file */
   if ((fd = open(filename, O_RDWR, 0)) < 0)
      err(EX_NOINPUT, "open \%s\" failed", filename);

   /* Verify the ELF version */
   if (elf_version(EV_CURRENT) == EV_NONE)
      errx(EX_SOFTWARE, "Initialization failed: %s", 
         elf_errmsg(-1));

   /* Create the Elf structure */
   if ((efile = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
      errx(EX_SOFTWARE, "elf_begin() failed: %s.",
         elf_errmsg(-1));
   
   /* Get the ELF Header from the structure */
   if (gelf_getehdr(efile, &ehdr) == NULL)
      errx(EX_SOFTWARE, "getehdr() failed: %s.",
         elf_errmsg(-1));
   
   /* Display the file type */
   printf("%s: File type is ", filename);
   switch(ehdr.e_type) {
      case ET_NONE:
         printf("Unknown\n");
      break;
      case ET_REL:
         printf("Relocatable\n");
      break;
      case ET_EXEC:
         printf("Executable\n");
      break;
      case ET_DYN:
         printf("Dynamic Library\n");
      break;
      case ET_CORE:
         printf("Core file\n");
      break;
      default:
         printf("Other\n");
  }
  elf_end(efile);
  close(fd);
  return 0;
}
