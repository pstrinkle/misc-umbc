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

# define stsize 32

float iM0 [stsize] [stsize] __attribute__ ((aligned (128)));
float fM0 [stsize] [stsize] __attribute__ ((aligned (128)));

float iM1 [stsize] [stsize] __attribute__ ((aligned (128)));
float fM1 [stsize] [stsize] __attribute__ ((aligned (128)));

float (*pi_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));
float (*pf_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));

void get_matrix_segment0 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_get((void*)&(iM0[j][0]), (unsigned long )&((*pi_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
}

void put_matrix_segment0 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_put((void*)&(fM0[j][0]), (unsigned long )&((*pf_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
}

void get_matrix_segment1 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_get((void*)&(iM1[j][0]), (unsigned long )&((*pi_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
}

void put_matrix_segment1 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_put((void*)&(fM1[j][0]), (unsigned long )&((*pf_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
}

void waitfor_matrix_io ( int tag ) {
	mfc_write_tag_mask(1<<tag);
	mfc_read_tag_status_all();   // Wait for the data array DMA to complete.
}

int main(unsigned long long speid, addr64 argp, addr64 envp) 
{
	unsigned long long dummy ;
	int bi, bj ;
	int i_initial, i_final ;
	int first0, first1;
	int k;

	/* Here is the actual DMA call */
	/* the first parameter is the address in local store to place the data */
	/* the second parameter holds the main memory address                  */
	/* the third parameter holds the number of bytes to DMA                */
	/* the fourth parameter identifies a "tag" to associate with this DMA  */
	/* (this should be a number between 0 and 31, inclusive)               */
	/* the last two parameters are only useful if you've implemented your  */
	/* own cache replacement management policy.  Otherwise set them to 0.  */
	dummy = envp.ull ;
	dummy = speid ;

	mfc_get((void*)&args, argp.ull, 128, 31, 0, 0);

	/* Now, we set the "tag bit" into the correct channel on the hardware  */
	/* this is always 1 left-shifted by the tag specified with the DMA     */
	/* for whose completion you wish to wait.                              */
	mfc_write_tag_mask(1<<31);

	/* Wait for the data array DMA to complete. */
	mfc_read_tag_status_all();

	pi_matrix = args.initial ;
	pf_matrix = args.final ;
	i_initial = args.i_initial ;
	i_final   = args.i_final ;

//printf("SPE(%lld): Data received is: %x %x %d %d\n", speid, 
//(int)pi_matrix, (int)pf_matrix, (int)i_initial, (int)i_final );
//printf("SPE(%lld): size= %d \n", speid, (int)args.final-(int)args.initial );



	for( k=0; k<loops; k++ ) {

		first0=1; first1=1; 
		for( bi=i_initial; bi<i_final; bi+=stsize ) {
			get_matrix_segment0 ( 31, bi, 0 );
			for( bj=0; bj<tsize; bj+=2*stsize ) {
		
				get_matrix_segment1 ( 29, bi, bj+stsize );
	
				waitfor_matrix_io  ( 31 ) ;
				if (!first0) waitfor_matrix_io  ( 30 ); first0=0;
	
				// Transpose segment 0
				{ int i, j;
				for (i=0;i<stsize;i++) {
					for (j=0;j<stsize;j++) {
						fM0[j][i] = iM0[i][j] ;
					}
				}
				}
	
				put_matrix_segment0 ( 30, bj, bi );
				if ( (bj+2*stsize)<tsize ) get_matrix_segment0 ( 31, bi, bj+2*stsize );
	
				waitfor_matrix_io( 29 ) ;
				if (!first1) waitfor_matrix_io( 28 ) ; first1=0;
	
				// Transpose segment 1
				{ int i, j;
				for (i=0;i<stsize;i++) {
					for (j=0;j<stsize;j++) {
						fM1[j][i] = iM1[i][j] ;
					}
				}
				}
	
				put_matrix_segment1 ( 28, bj+stsize, bi );
			}
	
		}
	}



# ifdef NEVER
	{ int i, j;
	for (i=0;i<32;i++) {
		for (j=0;j<10;j++) {
			printf(" %7.2f",iM0[i][j]);
		}
		printf("\n");
	}
		printf("\n\n");
	}
# endif

# ifdef NEVER
	{ int i, j;
	for (i=0;i<tsize;i++) {
		for (j=0;j<10;j++) {
			printf(" %7.2f",fM0[i][j]);
		}
		printf("\n");
	}
		printf("\n\n");
	}
# endif


	return 0;
}
