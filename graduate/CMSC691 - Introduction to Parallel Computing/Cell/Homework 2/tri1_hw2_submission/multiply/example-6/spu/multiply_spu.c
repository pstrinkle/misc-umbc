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
#include <spu_intrinsics.h>
#include <stdio.h>

struct arguments args  __attribute__ ((aligned (128)));
struct arguments args2 __attribute__ ((aligned (128)));

vector float AM0[stsize][stsize/4] __attribute__ ((aligned (128)));
vector float BM0[stsize][stsize/4] __attribute__ ((aligned (128)));

vector float AM1[stsize][stsize/4] __attribute__ ((aligned (128)));
vector float BM1[stsize][stsize/4] __attribute__ ((aligned (128)));

vector float CM[stsize][stsize/4] __attribute__ ((aligned (128)));

float (*pA_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));
float (*pB_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));
float (*pC_matrix) [tsize] [tsize] __attribute__ ((aligned (128)));

void
get_Amatrix_segment0(int tag, int seg_i, int seg_j)
{
   int i, j;
   j = 0;

   for(i = seg_i; i < (seg_i+stsize); i++)
   {
      mfc_get(
	 (void*)&(AM0[j][0]),
	 (unsigned long )&((*pA_matrix)[i][seg_j]),
	 stsize*sizeof(float),
	 tag,
	 0,
	 0);

      j++;
   }
}

void
get_Bmatrix_segment0(int tag, int seg_i, int seg_j)
{
   int i, j;
   j = 0;

   for(i = seg_i; i < (seg_i+stsize); i++)
   {
      mfc_get(
	 (void*)&(BM0[j][0]),
	 (unsigned long )&((*pB_matrix)[i][seg_j]),
	 stsize*sizeof(float),
	 tag,
	 0,
	 0);

      j++;
   }
}

void
get_Amatrix_segment1(int tag, int seg_i, int seg_j)
{
   int i, j;
   j = 0;

   for(i = seg_i; i < (seg_i+stsize); i++)
   {
      mfc_get(
	 (void*)&(AM1[j][0]),
	 (unsigned long )&((*pA_matrix)[i][seg_j]),
	 stsize*sizeof(float),
	 tag,
	 0,
	 0);

      j++;
   }
}

void
get_Bmatrix_segment1(int tag, int seg_i, int seg_j)
{
   int i, j;
   j = 0;

   for(i = seg_i; i < (seg_i+stsize); i++)
   {
      mfc_get(
	 (void*)&(BM1[j][0]),
	 (unsigned long )&((*pB_matrix)[i][seg_j]),
	 stsize*sizeof(float),
	 tag,
	 0,
	 0);

      j++;
   }
}

void
get_Cmatrix_segment(int tag, int seg_i, int seg_j)
{
   int i, j;
   j = 0;

   for(i = seg_i; i < (seg_i+stsize); i++)
   {
      mfc_get(
	 (void*)&(CM[j][0]),
	 (unsigned long )&((*pC_matrix)[i][seg_j]),
	 stsize*sizeof(float),
	 tag,
	 0,
	 0);

      j++;
   }

   j=0;
}

void
put_Cmatrix_segment(int tag, int seg_i, int seg_j)
{
   int i, j;
   j = 0;

   for(i = seg_i; i < (seg_i+stsize); i++)
   {
      mfc_put(
	 (void*)&(CM[j][0]),
	 (unsigned long )&((*pC_matrix)[i][seg_j]),
	 stsize*sizeof(float),
	 tag,
	 0,
	 0);

      j++;
   }
}

void
waitfor_matrix_io(int tag)
{
   mfc_write_tag_mask(1 << tag);
   mfc_read_tag_status_all();   // Wait for the data array DMA to complete.
}

int main(unsigned long long speid, addr64 argp, addr64 envp) 
{
   unsigned long long dummy ;
   int bi, bj, bk ;
   int i_initial, i_final ;
   int first0, first1;
   int k;

   
   /* rotate left one byte */
   vector unsigned char leftone = (vector unsigned char){0x04,0x05,0x06,0x07,
							 0x08,0x09,0x0a,0x0b,
							 0x0c,0x0d,0x0e,0x0f,
							 0x00,0x01,0x02,0x03};
   
   /* matrix A initializers */
   vector unsigned char row2 = (vector unsigned char){0x08,0x09,0x0a,0x0b,
						      0x0c,0x0d,0x0e,0x0f,
						      0x00,0x01,0x02,0x03,
						      0x04,0x05,0x06,0x07};
   vector unsigned char row3 = (vector unsigned char){0x0c,0x0d,0x0e,0x0f,
						      0x00,0x01,0x02,0x03,
						      0x04,0x05,0x06,0x07,
						      0x08,0x09,0x0a,0x0b};
   
   /* matrix B initializers */
   vector unsigned char b1 = (vector unsigned char){0x00,0x01,0x02,0x03,
						    0x14,0x15,0x16,0x17,
						    0x08,0x09,0x0a,0x0b,
						    0x1c,0x1d,0x1e,0x1f};
   vector unsigned char b2 = (vector unsigned char){0x00,0x01,0x02,0x03,
						    0x04,0x05,0x06,0x07,
						    0x18,0x19,0x1a,0x1b,
						    0x1c,0x1d,0x1e,0x1f};

   vector float temp[4] __attribute__ ((aligned (128)));
   
   dummy = envp.ull;
   dummy = speid;

   mfc_get((void*)&args, argp.ull, 128, 31, 0, 0);
   mfc_write_tag_mask(1 << 31);
   mfc_read_tag_status_all();

   pA_matrix = args.Amat;
   pB_matrix = args.Bmat;
   pC_matrix = args.Cmat;
   i_initial = args.i_initial;
   i_final   = args.i_final;

   printf(
      "SPE(%lld): Data received is: A:0x%x B:0x%x C:0x%x StartRow:%d EndRow:%d\n",
      speid, 
      (int)pA_matrix,
      (int)pB_matrix,
      (int)pC_matrix,
      (int)i_initial,
      (int)i_final);

   first0 = 1;
   first1 = 1;
   
   for(bi = i_initial; bi < i_final; bi += stsize)
   {
      for(bj = 0; bj < tsize; bj += stsize)
      {
	 get_Amatrix_segment0(31, bi, 0);
	 get_Bmatrix_segment0(31, 0, bj);
	 
	 if (!first0)
	 {
	    waitfor_matrix_io( 30 );
	 }
	 
	 first0 = 0;
	 
	 get_Cmatrix_segment(30, bi, bj);
	 
	 for(bk = 0; bk < tsize; bk += 2*stsize)
	 {
	    get_Amatrix_segment1(29, bi, bk+stsize);
	    get_Bmatrix_segment1(29, bk+stsize, bj);
	    
	    waitfor_matrix_io( 31 );
	    waitfor_matrix_io( 30 );
	    
	    // Multiply segment 0
	    {
	       int i, j, z;
	       
	       for (i = 0; i < stsize; i+=4)
	       {
		  for (j = 0; j < stsize/4; j++)
		  {
		     for (k = 0; k < stsize/4; k++)
		     {
			z = k*4;
			
			/* CM[i][j] += AM0[i][k] * BM0[k][j] ; */
			/* operate on the subblock (4x4 floats) */
			/* init B shuffle */
			if (i == 0)
			{
			   temp[0] = spu_shuffle(BM0[z][j], BM0[z+1][j], b1);
			   temp[1] = spu_shuffle(BM0[z+1][j], BM0[z+2][j], b1);
			   temp[2] = spu_shuffle(BM0[z+2][j], BM0[z+3][j], b1);
			   temp[3] = spu_shuffle(BM0[z+3][j], BM0[z][j], b1);
			   
			   BM0[z][j]   = spu_shuffle(temp[0], temp[2], b2);
			   BM0[z+1][j] = spu_shuffle(temp[1], temp[3], b2);
			   BM0[z+2][j] = spu_shuffle(temp[2], temp[0], b2);
			   BM0[z+3][j] = spu_shuffle(temp[3], temp[1], b2);
			}
			
			/* init A shuffle */
			if (j == 0)
			{
			   /* AM0[i][k] is fine */
			   AM0[i+1][k] = spu_shuffle(AM0[i+1][k], AM0[i+1][k], leftone);
			   AM0[i+2][k] = spu_shuffle(AM0[i+2][k], AM0[i+2][k], row2);
			   AM0[i+3][k] = spu_shuffle(AM0[i+3][k], AM0[i+3][k], row3);
			}
			else
			{
			   /* rotate all rows in matrix A left one */
			   AM0[i][k]   = spu_shuffle(AM0[i][k], AM0[i][k], leftone);
			   AM0[i+1][k] = spu_shuffle(AM0[i+1][k], AM0[i][k], leftone);
			   AM0[i+2][k] = spu_shuffle(AM0[i+2][k], AM0[i][k], leftone);
			   AM0[i+3][k] = spu_shuffle(AM0[i+3][k], AM0[i][k], leftone);
			}
			
			/* based on systolic arrays, we conduct a 4x4 madd, then rotate */
			// First Row madd & shuffle
			CM[i][j] = spu_madd(AM0[i][k], BM0[z][j], CM[i][j]);
			CM[i+1][j] = spu_madd(AM0[i+1][k], BM0[z+1][j], CM[i+1][j]);
			CM[i+2][j] = spu_madd(AM0[i+2][k], BM0[z+2][j], CM[i+2][j]);
			CM[i+3][j] = spu_madd(AM0[i+3][k], BM0[z+3][j], CM[i+3][j]);
			AM0[i][k] = spu_shuffle(AM0[i][k],   AM0[i][j], leftone);
			AM0[i+1][k] = spu_shuffle(AM0[i+1][k], AM0[i][j], leftone);
			AM0[i+2][k] = spu_shuffle(AM0[i+2][k], AM0[i][j], leftone);
			AM0[i+3][k] = spu_shuffle(AM0[i+3][k], AM0[i][j], leftone);
			
			// Second Row madd & shuffle
			CM[i][j] = spu_madd(AM0[i][k], BM0[z+1][j], CM[i][j]);
			CM[i+1][j] = spu_madd(AM0[i+1][k], BM0[z+2][j], CM[i+1][j]);
			CM[i+2][j] = spu_madd(AM0[i+2][k], BM0[z+3][j], CM[i+2][j]);
			CM[i+3][j] = spu_madd(AM0[i+3][k], BM0[z][j], CM[i+3][j]);
			AM0[i][k] = spu_shuffle(AM0[i][k], AM0[i][j], leftone);
			AM0[i+1][k] = spu_shuffle(AM0[i+1][k], AM0[i][j], leftone);
			AM0[i+2][k] = spu_shuffle(AM0[i+2][k], AM0[i][j], leftone);
			AM0[i+3][k] = spu_shuffle(AM0[i+3][k], AM0[i][j], leftone);
			
			// Third Row madd & shuffle
			CM[i][j] = spu_madd(AM0[i][k], BM0[z+2][j], CM[i][j]);
			CM[i+1][j] = spu_madd(AM0[i+1][k], BM0[z+3][j], CM[i+1][j]);
			CM[i+2][j] = spu_madd(AM0[i+2][k], BM0[z][j], CM[i+2][j]);
			CM[i+3][j] = spu_madd(AM0[i+3][k], BM0[z+1][j], CM[i+3][j]);
			AM0[i][k] = spu_shuffle(AM0[i][k], AM0[i][j], leftone);
			AM0[i+1][k] = spu_shuffle(AM0[i+1][k], AM0[i][j], leftone);
			AM0[i+2][k] = spu_shuffle(AM0[i+2][k], AM0[i][j], leftone);
			AM0[i+3][k] = spu_shuffle(AM0[i+3][k], AM0[i][j], leftone);
			
			// Fourth madd & (no shuffle needed, end of loop)
			CM[i][j] = spu_madd(AM0[i][k], BM0[z+3][j], CM[i][j]);
			CM[i+1][j] = spu_madd(AM0[i+1][k], BM0[z][j], CM[i+1][j]);
			CM[i+2][j] = spu_madd(AM0[i+2][k], BM0[z+1][j], CM[i+2][j]);
			CM[i+3][j] = spu_madd(AM0[i+3][k], BM0[z+2][j], CM[i+3][j]);
			
		     }
		  }
	       }
	    }
	    
	    if ((bk+2*stsize) < tsize)
	    {
	       get_Amatrix_segment0(31, bi, bk+2*stsize);
	       get_Bmatrix_segment0(31, bk+2*stsize, bj);
	    }
	    
	    waitfor_matrix_io( 29 );
	    
	    // Multiply segment 1
	    {
	       int i, j, z;
	       
	       for (i = 0; i < stsize; i+=4)
	       {
		  for (j = 0; j < stsize/4; j++)
		  {
		     for (k = 0; k < stsize/4; k++)
		     {
			z = k*4;
			
			/* CM[i][j] += AM1[i][k] * BM1[k][j]; */
			
			/* init B shuffle */
			if (i == 0)
			{
			   temp[0] = spu_shuffle(BM1[z][j], BM1[z+1][j], b1);
			   temp[1] = spu_shuffle(BM1[z+1][j], BM1[z+2][j], b1);
			   temp[2] = spu_shuffle(BM1[z+2][j], BM1[z+3][j], b1);
			   temp[3] = spu_shuffle(BM1[z+3][j], BM1[z][j], b1);
			   
			   BM1[z][j]   = spu_shuffle(temp[0], temp[2], b2);
			   BM1[z+1][j] = spu_shuffle(temp[1], temp[3], b2);
			   BM1[z+2][j] = spu_shuffle(temp[2], temp[0], b2);
			   BM1[z+3][j] = spu_shuffle(temp[3], temp[1], b2);
			}
			
			/* init A shuffle */
			if (j == 0)
			{
			   /* AM1[i][k] is fine */
			   AM1[i+1][k] = spu_shuffle(AM1[i+1][k], AM1[i+1][k], leftone);
			   AM1[i+2][k] = spu_shuffle(AM1[i+2][k], AM1[i+2][k], row2);
			   AM1[i+3][k] = spu_shuffle(AM1[i+3][k], AM1[i+3][k], row3);
			}
			else
			{
			   /* rotate all rows in matrix A left one */
			   AM1[i][k]   = spu_shuffle(AM1[i][k], AM1[i][k], leftone);
			   AM1[i+1][k] = spu_shuffle(AM1[i+1][k], AM1[i][k], leftone);
			   AM1[i+2][k] = spu_shuffle(AM1[i+2][k], AM1[i][k], leftone);
			   AM1[i+3][k] = spu_shuffle(AM1[i+3][k], AM1[i][k], leftone);
			}
			
			/* based on systolic arrays, we conduct a 4x4 madd, then rotate */
			// First Row madd & shuffle
			CM[i][j] = spu_madd(AM1[i][k], BM1[z][j], CM[i][j]);
			CM[i+1][j] = spu_madd(AM1[i+1][k], BM1[z+1][j], CM[i+1][j]);
			CM[i+2][j] = spu_madd(AM1[i+2][k], BM1[z+2][j], CM[i+2][j]);
			CM[i+3][j] = spu_madd(AM1[i+3][k], BM1[z+3][j], CM[i+3][j]);
			AM1[i][k] = spu_shuffle(AM1[i][k],   AM1[i][j], leftone);
			AM1[i+1][k] = spu_shuffle(AM1[i+1][k], AM1[i][j], leftone);
			AM1[i+2][k] = spu_shuffle(AM1[i+2][k], AM1[i][j], leftone);
			AM1[i+3][k] = spu_shuffle(AM1[i+3][k], AM1[i][j], leftone);
			
			// Second Row madd & shuffle
			CM[i][j] = spu_madd(AM1[i][k], BM1[z+1][j], CM[i][j]);
			CM[i+1][j] = spu_madd(AM1[i+1][k], BM1[z+2][j], CM[i+1][j]);
			CM[i+2][j] = spu_madd(AM1[i+2][k], BM1[z+3][j], CM[i+2][j]);
			CM[i+3][j] = spu_madd(AM1[i+3][k], BM1[z][j], CM[i+3][j]);
			AM1[i][k] = spu_shuffle(AM1[i][k], AM1[i][j], leftone);
			AM1[i+1][k] = spu_shuffle(AM1[i+1][k], AM1[i][j], leftone);
			AM1[i+2][k] = spu_shuffle(AM1[i+2][k], AM1[i][j], leftone);
			AM1[i+3][k] = spu_shuffle(AM1[i+3][k], AM1[i][j], leftone);
			
			// Third Row madd & shuffle
			CM[i][j] = spu_madd(AM1[i][k], BM1[z+2][j], CM[i][j]);
			CM[i+1][j] = spu_madd(AM1[i+1][k], BM1[z+3][j], CM[i+1][j]);
			CM[i+2][j] = spu_madd(AM1[i+2][k], BM1[z][j], CM[i+2][j]);
			CM[i+3][j] = spu_madd(AM1[i+3][k], BM1[z+1][j], CM[i+3][j]);
			AM1[i][k] = spu_shuffle(AM1[i][k], AM1[i][j], leftone);
			AM1[i+1][k] = spu_shuffle(AM1[i+1][k], AM1[i][j], leftone);
			AM1[i+2][k] = spu_shuffle(AM1[i+2][k], AM1[i][j], leftone);
			AM1[i+3][k] = spu_shuffle(AM1[i+3][k], AM1[i][j], leftone);
			
			// Fourth madd & (no shuffle needed, end of loop)
			CM[i][j] = spu_madd(AM1[i][k], BM1[z+3][j], CM[i][j]);
			CM[i+1][j] = spu_madd(AM1[i+1][k], BM1[z][j], CM[i+1][j]);
			CM[i+2][j] = spu_madd(AM1[i+2][k], BM1[z+1][j], CM[i+2][j]);
			CM[i+3][j] = spu_madd(AM1[i+3][k], BM1[z+2][j], CM[i+3][j]);
		     }
		  }
	       }
	    } /* end mul seg 1 */
	    
	 } /* end for bk = 0; bk < tsize */
	 
	 put_Cmatrix_segment(30, bi, bj);
      }	 
   }
   
   waitfor_matrix_io( 30 );
   
   return 0;
}
