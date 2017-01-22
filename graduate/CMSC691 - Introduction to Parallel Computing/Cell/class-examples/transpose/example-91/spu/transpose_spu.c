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


vector float iM0 [vsize] [4] [vsize] __attribute__ ((aligned (128)));
vector float fM0 [vsize] [4] [vsize] __attribute__ ((aligned (128)));

vector float iM1 [vsize] [4] [vsize] __attribute__ ((aligned (128)));
vector float fM1 [vsize] [4] [vsize] __attribute__ ((aligned (128)));

float (*pi_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));
float (*pf_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));

/*  DMA I/O list  */
mfc_list_element_t iolst_g0[stsize] __attribute__ ((aligned (16)));
mfc_list_element_t iolst_g1[stsize] __attribute__ ((aligned (16)));
mfc_list_element_t iolst_p0[stsize] __attribute__ ((aligned (16)));
mfc_list_element_t iolst_p1[stsize] __attribute__ ((aligned (16)));


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

void get_matrix_segment0 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		iolst_g0[j].eal  = (unsigned long )&((*pi_matrix)[i][seg_j]) ;
		iolst_g0[j].size = stsize*sizeof(float);
		j++;
	}
	spu_mfcdma32((void*)&(iM0), (unsigned int)iolst_g0, stsize*sizeof(mfc_list_element_t), tag, MFC_GETL_CMD);
}

void put_matrix_segment0 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		iolst_p0[j].eal  = (unsigned long )&((*pf_matrix)[i][seg_j]) ;
		iolst_p0[j].size = stsize*sizeof(float);
		j++;
	}
	spu_mfcdma32((void*)&(fM0), (unsigned int)iolst_p0, stsize*sizeof(mfc_list_element_t), tag, MFC_PUTL_CMD);
}

void get_matrix_segment1 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		iolst_g1[j].eal  = (unsigned long )&((*pi_matrix)[i][seg_j]) ;
		iolst_g1[j].size = stsize*sizeof(float);
		j++;
	}
	spu_mfcdma32((void*)&(iM1), (unsigned int)iolst_g1, stsize*sizeof(mfc_list_element_t), tag, MFC_GETL_CMD);
}

void put_matrix_segment1 ( int tag, int seg_i, int seg_j ) {
	int i, j;
	j=0;
	for(i=seg_i; i<(seg_i+stsize); i++ ) {
		iolst_p1[j].eal  = (unsigned long )&((*pf_matrix)[i][seg_j]) ;
		iolst_p1[j].size = stsize*sizeof(float);
		j++;
	}
	spu_mfcdma32((void*)&(fM1), (unsigned int)iolst_p1, stsize*sizeof(mfc_list_element_t), tag, MFC_PUTL_CMD);
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
	int i, j, k;

	register vector float a0, a1, a2, a3;
	register vector float b0, b1, b2, b3;
	register vector float c0, c1, c2, c3;

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

//printf("SPE(%lld): Data received is: %x %x %d %d\n", speid, (int)pi_matrix, (int)pf_matrix, (int)i_initial, (int)i_final );
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
	
				put_matrix_segment0 ( 30, bj, bi );
				if ( (bj+2*stsize)<tsize ) get_matrix_segment0 ( 31, bi, bj+2*stsize );
	
				waitfor_matrix_io( 29 ) ;
				if (!first1) waitfor_matrix_io( 28 ) ; first1=0;
	
				// Transpose segment 1
				for (i=0;i<vsize;i++) {
					for (j=0;j<vsize;j++) {
						a0 = iM1[i][0][j] ;
						a1 = iM1[i][1][j] ;
						a2 = iM1[i][2][j] ;
						a3 = iM1[i][3][j] ;
						b0 = spu_shuffle( a0, a2, s410 );
						b1 = spu_shuffle( a1, a3, s410 );
						b2 = spu_shuffle( a0, a2, s411 );
						b3 = spu_shuffle( a1, a3, s411 );
						c0 = spu_shuffle( b0, b1, s400 );
						c1 = spu_shuffle( b0, b1, s401 );
						c2 = spu_shuffle( b2, b3, s400 );
						c3 = spu_shuffle( b2, b3, s401 );
						fM1[j][0][i] = c0 ;
						fM1[j][1][i] = c1 ;
						fM1[j][2][i] = c2 ;
						fM1[j][3][i] = c3 ;
					}
				}
	
				put_matrix_segment1 ( 28, bj+stsize, bi );
			}
	
		}
	}


	return 0;
}


# ifdef NEVER
	{ int i, j, m ,n;
	union { vector float v; float a[4] ; } A ;
	for (i=0;i<vsize;i++) { for (m=0;m<4;m++) {
		for (j=0;j<3;j++) { for (n=0;n<4;n++) {
			A.v = iM0[i][m][j];
			printf(" %7.2f",A.a[n]);
		}}
		printf("\n");
	}}
		printf("\n\n");
	}
# endif

