#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <asm/ps3fb.h>
#include <sys/mman.h>

#define BYTES_PER_PIXEL 4
#define RADIUS 20

void draw(int fd, void *fb_addr, int num_frames, 
   struct ps3fb_ioctl_res *info) {

   int i, x, y, x_size, y_size;
   unsigned int red, green, blue, frame;
   unsigned int *pix_addr;
   void *frame_addr;
   
   y_size = info->yres - 2 * info->yoff;
   x_size = info->xres - 2 * info->xoff;
   
   /* Repeat drawing process 128 times */
   for (i=0; i<128; i++) {
   
      /* Wait for vertical sync signal */
      ioctl(fd, FBIO_WAITFORVSYNC, 0);
      
      /* Set the frame number */
      frame = i % num_frames;
      
      /* Determine the address of the current frame */
      frame_addr = fb_addr + 
         (info->xres * info->yres * BYTES_PER_PIXEL) * frame;
	  
      /* Iterate for each row */
      for (y=0; y<y_size; y++) {
	  
         /* Set pixel address to start of row */
         pix_addr = (unsigned int*)
	         (frame_addr + y * info->xres * BYTES_PER_PIXEL);
         for (x=0; x<x_size; x++) {
            if (sqrt(pow(x-x_size/2,2)+pow(y-y_size/2,2)) < RADIUS+i) {
               red = 0xff;
               green = 0xa5;
               blue = i*2;
            } else {
               red = green = blue = 0;
            }
            *pix_addr = (red << 16  | green << 8 | blue);
            pix_addr++;
         }
      }
	  
      /* Identify buffer for the next flip */
      ioctl(fd, PS3FB_IOCTL_FSEL, (unsigned long)&frame);
   }
}

int main() {

   void *addr;
   struct ps3fb_ioctl_res info;
   struct fb_vblank vblank;
   int fd, disp_size, margin_size, fb_size;
   
   /* Open the file */
   if ((fd = open("/dev/fb0", O_RDWR)) < 0) {
      fprintf(stderr, "error open:%d\n", fd);
      return -1;
   }

   /* Make sure the vsync signal is accessible */
   ioctl(fd, FBIOGET_VBLANK, (unsigned long)&vblank);
   if (!(vblank.flags & FB_VBLANK_HAVE_VSYNC)) {
      fprintf(stderr, "Error accessing vertical sync\n");
      close(fd);
      return -1;
   }
   
   /* Acquire information about display/framebuffer */
   if (ioctl(fd, PS3FB_IOCTL_SCREENINFO, 
         (unsigned long)&info) < 0) {
      fprintf(stderr, "Error accessing screen info\n");
      close(fd);
      return -1;
   }
   
   /* Determine buffer size and memory map buffer to addr */
   disp_size = info.xres * info.yres * info.num_frames * BYTES_PER_PIXEL;
   margin_size = info.xres * info.yoff * 2 * BYTES_PER_PIXEL;
   fb_size = disp_size - margin_size;
   addr = mmap(NULL, fb_size, PROT_WRITE, MAP_SHARED, fd, 0);
   if (addr == MAP_FAILED) {
      fprintf(stderr, "Error mapping framebuffer to memory\n");
      close(fd);
      return -1;
   }
   
   /* Turn on fb access, draw pixels, turn off */
   ioctl(fd, PS3FB_IOCTL_ON, 0);
   memset(addr, 0, fb_size);
   draw(fd, addr, info.num_frames, &info);
   ioctl(fd, PS3FB_IOCTL_OFF, 0);
   munmap(NULL, fb_size);
   close(fd);
   
   return 0;
}
