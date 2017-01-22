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

float AM0 [stsize] [stsize] __attribute__ ((aligned (128)));
float BM0 [stsize] [stsize] __attribute__ ((aligned (128)));

float AM1 [stsize] [stsize] __attribute__ ((aligned (128)));
float BM1 [stsize] [stsize] __attribute__ ((aligned (128)));

float CM  [stsize] [stsize] __attribute__ ((aligned (128)));

float (*pA_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));
float (*pB_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));
float (*pC_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));


void get_Amatrix_segment0 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_get((void*)&(AM0[j][0]), (unsigned long )&((*pA_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
}

void get_Bmatrix_segment0 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_get((void*)&(BM0[j][0]), (unsigned long )&((*pB_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
}


void get_Amatrix_segment1 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_get((void*)&(AM1[j][0]), (unsigned long )&((*pA_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
}

void get_Bmatrix_segment1 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_get((void*)&(BM1[j][0]), (unsigned long )&((*pB_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
}


void get_Cmatrix_segment ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_get((void*)&(CM[j][0]), (unsigned long )&((*pC_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
		j++;
	}
	j=0;
}

void put_Cmatrix_segment ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		mfc_put((void*)&(CM[j][0]), (unsigned long )&((*pC_matrix)[i][seg_j]), stsize*sizeof(float), tag, 0, 0);
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
	int bi, bj, bk ;
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

	pA_matrix = args.Amat ;
	pB_matrix = args.Bmat ;
	pC_matrix = args.Cmat ;
	i_initial = args.i_initial ;
	i_final   = args.i_final ;

//printf("SPE(%lld): Data received is: %x %x %x %d %d\n", speid, 
//(int)pA_matrix, (int)pB_matrix, (int)pC_matrix, (int)i_initial, (int)i_final );
//printf("SPE(%lld): size= %d \n", speid, (int)args.Bmat-(int)args.Amat );



	for( k=0; k<loops; k++ ) {

		first0=1; first1=1; 
		for( bi=i_initial; bi<i_final; bi+=stsize ) {
			for( bj=0; bj<tsize; bj+=stsize ) {
				get_Amatrix_segment0 ( 31, bi,  0 );
				get_Bmatrix_segment0 ( 31,  0, bj );
				if (!first0) { waitfor_matrix_io  ( 30 ); } first0=0;
				get_Cmatrix_segment  ( 30, bi, bj );
				for(bk=0; bk<tsize; bk+=2*stsize) {
		
					get_Amatrix_segment1 ( 29, bi, bk+stsize );
					get_Bmatrix_segment1 ( 29, bk+stsize, bj );
	
					waitfor_matrix_io  ( 31 );
					waitfor_matrix_io  ( 30 );

					// Multiply segment 0
					{ int i, j;
					for (i=0;i<stsize;i++) {
						for (j=0;j<stsize;j++) {
							for (k=0;k<stsize;k++) {
								CM[i][j] += AM0[i][k] * BM0[k][j] ;
							}
						}
					}
					}
	
					if ( (bk+2*stsize)<tsize ) {
						get_Amatrix_segment0 ( 31, bi, bk+2*stsize );
						get_Bmatrix_segment0 ( 31, bk+2*stsize, bj );
					} 
	
					waitfor_matrix_io( 29 ) ;
	
					// Multiply segment 1
					{ int i, j;
					for (i=0;i<stsize;i++) {
						for (j=0;j<stsize;j++) {
							for (k=0;k<stsize;k++) {
								CM[i][j] += AM1[i][k] * BM1[k][j] ;
							}
						}
					}
					}
	
				}
				put_Cmatrix_segment ( 30, bi, bj );
			}
	
		}
	}
	waitfor_matrix_io  ( 30 );


	return 0;
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
	for (i=0;i<tsize;i++) {
		for (j=0;j<10;j++) {
			printf(" %7.2f",fM0[i][j]);
		}
		printf("\n");
	}
		printf("\n\n");
	}
# endif
