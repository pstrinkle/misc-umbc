#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <asm/ps3fb.h>

int main() {

   int fd;
   struct ps3fb_ioctl_res info;
   
   /* Open the framebuffer device file */
   if ((fd = open("/dev/fb0", O_RDWR)) < 0) {
      fprintf(stderr, "error open:%d\n", fd);
      return -1;
   }
   
   /* Acquire screen information */
   if (ioctl(fd, PS3FB_IOCTL_SCREENINFO, 
         (unsigned long)&info) < 0) {
      fprintf(stderr, "PS3FB_IOCTL_SCREENINFO failed\n");
      return -1;
   }
   
   /* Display the results */
   printf("The total x dimension is %d\n", info.xres);
   printf("The total y dimension is %d\n", info.yres);
   printf("The x margin is %d\n", info.xoff);
   printf("The y margin is %d\n", info.yoff);
   printf("The number of framebuffers is %d\n", info.num_frames);     
   return 0;
}
