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

# define stsize 32

float iM0 [stsize] [stsize] __attribute__ ((aligned (128)));
float fM0 [stsize] [stsize] __attribute__ ((aligned (128)));

int main(unsigned long long speid, addr64 argp, addr64 envp) 
{
	unsigned long long dummy;
	
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

	{ int i, j;
	for (i=0;i<stsize;i++) {
		for (j=0;j<stsize;j++) {
			fM0[j][i] = iM0[i][j] ;
		}
	}
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

	mfc_put((void*)fM0, (unsigned long)args.final, stsize*stsize*sizeof(float), 31, 0, 0);
	mfc_read_tag_status_all(); // Wait for the data array DMA to complete.

	return 0;
}
