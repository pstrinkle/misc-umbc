/* --------------------------------------------------------------  */
/* (C)Copyright 2001,2006,                                         */
/* International Business Machines Corporation,                    */
/* Sony Computer Entertainment, Incorporated,                      */
/* Toshiba Corporation,                                            */
/*                                                                 */
/* All Rights Reserved.                                            */
/* --------------------------------------------------------------  */
/* PROLOG END TAG zYx                                              */
#include "../common.h"
#include <spu_mfcio.h>
#include <stdio.h>



//unsigned char parameter_area[128] __attribute__ ((aligned (128)));
struct arguments args __attribute__ ((aligned (128)));
struct arguments args2 __attribute__ ((aligned (128)));

# ifdef _use_register_
vector float iM0 [vsize] [4] [vsize] __attribute__ ((aligned (128)));
vector float fM0 [vsize] [4] [vsize] __attribute__ ((aligned (128)));
# else
float iM0 [stsize] [stsize] __attribute__ ((aligned (128)));
float fM0 [stsize] [stsize] __attribute__ ((aligned (128)));
# endif

# ifdef _use_register_
//	vector unsigned char noshuffle = { 
//		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F  };
	vector unsigned char s410 = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17  };
	vector unsigned char s411 = { 
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F  };
	vector unsigned char s400 = {
		0x00, 0x01, 0x02, 0x03, 0x10, 0x11, 0x12, 0x13,
		0x08, 0x09, 0x0A, 0x0B, 0x18, 0x19, 0x1A, 0x1B  };
	vector unsigned char s401 = { 
		0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17,
		0x0C, 0x0D, 0x0E, 0x0F, 0x1C, 0x1D, 0x1E, 0x1F  };
# endif

int main(unsigned long long speid, addr64 argp, addr64 envp) 
{
	unsigned long long dummy;
	int i, j;
# ifdef _use_register_
	register vector float a0, a1, a2, a3;
	register vector float b0, b1, b2, b3;
	register vector float c0, c1, c2, c3;
# endif
	
	/* Here is the actual DMA call */
	/* the first parameter is the address in local store to place the data */
	/* the second parameter holds the main memory address                  */
	/* the third parameter holds the number of bytes to DMA                */
	/* the fourth parameter identifies a "tag" to associate with this DMA  */
	/* (this should be a number between 0 and 31, inclusive)               */
	/* the last two parameters are only useful if you've implemented your  */
	/* own cache replacement management policy.  Otherwise set them to 0.  */
	dummy = envp.ull ;
	
	mfc_get((void*)&args, argp.ull, 128, 31, 0, 0);
	
	/* Now, we set the "tag bit" into the correct channel on the hardware  */
	/* this is always 1 left-shifted by the tag specified with the DMA     */
	/* for whose completion you wish to wait.                              */
	mfc_write_tag_mask(1<<31);

	/* Wait for the data array DMA to complete. */
	mfc_read_tag_status_all();


	printf("SPE(%lld): Data received is: %d %d %d\n", speid, (int)args.initial, (int)args.final, (int)args.i_initial );
	printf("SPE(%lld): Data received is: %x %x %d\n", speid, (int)args.initial, (int)args.final, (int)args.i_initial );
	printf("SPE(%lld): size= %d \n", speid, (int)args.final-(int)args.initial );

	mfc_get((void*)iM0, (unsigned long)args.initial, stsize*stsize*sizeof(float), 31, 0, 0);
	mfc_read_tag_status_all(); // Wait for the data array DMA to complete.

# ifdef _use_register_
	for (i=0;i<vsize;i++) {
		for (j=0;j<vsize;j++) {
			a0 = iM0[i][0][j] ;
			a1 = iM0[i][1][j] ;
			a2 = iM0[i][2][j] ;
			a3 = iM0[i][3][j] ;
			b0 = spu_shuffle( a0, a2, s410 );
			b1 = spu_shuffle( a1, a3, s410 );
			b2 = spu_shuffle( a0, a2, s411 );
			b3 = spu_shuffle( a1, a3, s411 );
			c0 = spu_shuffle( b0, b1, s400 );
			c1 = spu_shuffle( b0, b1, s401 );
			c2 = spu_shuffle( b2, b3, s400 );
			c3 = spu_shuffle( b2, b3, s401 );
			fM0[j][0][i] = c0 ;
			fM0[j][1][i] = c1 ;
			fM0[j][2][i] = c2 ;
			fM0[j][3][i] = c3 ;
		}
	}
# else
	for (i=0;i<stsize;i++) {
		for (j=0;j<stsize;j++) {
			fM0[j][i] = iM0[i][j] ;
		}
	}
# endif

	mfc_put((void*)fM0, (unsigned long)args.final, stsize*stsize*sizeof(float), 30, 0, 0);
	mfc_read_tag_status_all(); // Wait for the data array DMA to complete.

	return 0;
}


# ifdef NEVER
	{ int i, j;
	for (i=0;i<10;i++) {
		for (j=0;j<32;j++) {
			printf(" %7.2f",iM0[i][j]);
		}
		printf("\n");
	}
		printf("\n\n");
	}
# endif

# ifdef NEVER
	{ int i, j;
	for (i=0;i<10;i++) {
		for (j=0;j<32;j++) {
			printf(" %7.2f",fM0[i][j]);
		}
		printf("\n");
	}
		printf("\n\n");
	}
# endif

