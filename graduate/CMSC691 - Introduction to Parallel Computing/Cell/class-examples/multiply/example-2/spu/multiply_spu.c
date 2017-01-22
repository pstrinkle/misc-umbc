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
struct arguments args  __attribute__ ((aligned (128)));
struct arguments args2 __attribute__ ((aligned (128)));

float AM0 [stsize] [stsize] __attribute__ ((aligned (128)));
float BM0 [stsize] [stsize] __attribute__ ((aligned (128)));
float CM0 [stsize] [stsize] __attribute__ ((aligned (128)));

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


	printf("SPE(%lld): Data received is: %x %x %x %d\n", speid, (int)args.Amat, (int)args.Bmat, (int)args.Cmat, (int)args.i_initial );
	printf("SPE(%lld): size= %d \n", speid, (int)args.Bmat-(int)args.Amat );

	mfc_get ((void*)AM0, (unsigned long)args.Amat, stsize*stsize*sizeof(float), 31, 0, 0);
	mfc_get ((void*)BM0, (unsigned long)args.Bmat, stsize*stsize*sizeof(float), 31, 0, 0);
	mfc_get ((void*)CM0, (unsigned long)args.Cmat, stsize*stsize*sizeof(float), 31, 0, 0);
	mfc_write_tag_mask(1<<31);
	mfc_read_tag_status_all(); // Wait for the data array DMA to complete.

	{ int i, j, k;
	for (i=0;i<stsize;i++) {
		for (j=0;j<stsize;j++) {
			for (k=0;k<stsize;k++) {
				CM0[i][j] += AM0[i][k] * BM0[k][j] ;
			}
		}
	}
	}


# ifdef NEVER
	{ int i, j;
	for (i=0;i<32;i++) {
		for (j=0;j<10;j++) {
			printf(" %7.2f",AM0[i][j]);
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

	mfc_put ((void*)CM0, (unsigned long)args.Cmat, stsize*stsize*sizeof(float), 31, 0, 0);
	mfc_read_tag_status_all(); // Wait for the data array DMA to complete.

	return 0;
}
