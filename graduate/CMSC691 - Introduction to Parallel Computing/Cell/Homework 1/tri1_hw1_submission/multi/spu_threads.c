
/****************************
 * Patrick Trinkle
 * tri1@umbc.edu
 * Spring 2009
 * CMSC691 - Cell
 * Project 1 - Multi SPU Ver.
 * 
 * Notes: Similarly to the 
 * single SPU version; all 
 * data is read and written 
 * via double buffering,
 * using 16KB blocks.
 * And the tranpose is done
 * via vectors
 ****************************/

#include "pu_threads.h"
#include "spu_intrinsics.h"

#include <stdio.h>
#include <spu_mfcio.h>

#define BLOCK 64
#define TAG 3
/* make this a value in the structure to make generic */

int main (unsigned long long spe_id, 
          unsigned long long argp, 
          unsigned long long envp)
{
   unsigned int id;
   int i, j, bufindex;
   vector float temp[4];

   /* this is a set of 2 16K buffers */
   vector float buf[2][BLOCK][BLOCK/4] __attribute__ ((aligned(128)));
   vector float out[2][BLOCK][BLOCK/4] __attribute__ ((aligned(128)));

   vector unsigned char maskLeft = (vector unsigned char){0x00, 0x01, 0x02, 0x03,
                                                          0x10, 0x11, 0x12, 0x13,
                                                          0x04, 0x05, 0x06, 0x07,
                                                          0x14, 0x15, 0x16, 0x17};

   vector unsigned char maskRight = (vector unsigned char){0x08, 0x09, 0x0a, 0x0b,
                                                           0x18, 0x19, 0x1a, 0x1b,
                                                           0x0c, 0x0d, 0x0e, 0x0f,
                                                           0x1c, 0x1d, 0x1e, 0x1f};

   transpose_package_t package;

   /* location markers */
   unsigned long long dataaddr = 0;
   int rowid, blockid, blockaddr, blockstart, row;
   int opporowid, oppoblockaddr;

   /* read in package */
   mfc_get(&package, argp, sizeof(transpose_package_t), TAG, 0, 0);
   mfc_write_tag_mask(1<<TAG);
   mfc_read_tag_status_all();

   id = package.id;

   blockstart = id * (N / THREADCNT / BLOCK) * BLOCK * sizeof(float);

   /* For each Row set (64 rows in a row set)
    *     for each block
    *         for each row in a block
    *              read
    */
   for (rowid = 0; rowid < N; rowid += BLOCK)
   {
      /* read in prebuf */
      blockid = 0;

      blockaddr = blockstart + (blockid * sizeof(buf[0][0]));

      /* each rowset is 64 rows */
      for (row = rowid; row < rowid + BLOCK; row++)
      {
	 dataaddr = package.srcbuf + (row * N * sizeof(float)) + blockaddr;

	 mfc_get(
	    buf[blockid & 1][row % BLOCK],
	    dataaddr,
	    sizeof(buf[0][0]),
	    0,
	    0,
	    0);
      }

      /* each spu must walk 8 blocks per rowset */
      for (blockid = 1; blockid < (N / THREADCNT / BLOCK); blockid++)
      {
	 blockaddr = blockstart + (blockid * sizeof(buf[0][0]));

	 /* each rowset is 64 rows */
	 for (row = rowid; row < rowid + BLOCK; row++)
	 {
	    dataaddr = package.srcbuf + (row * N * sizeof(float)) + blockaddr;

	    mfc_get(
	       buf[blockid & 1][row % BLOCK],
	       dataaddr,
	       sizeof(buf[0][0]),
	       blockid & 1,
	       0,
	       0);
	 }

	 mfc_write_tag_mask(1 << (1 - (blockid & 1)));
	 mfc_read_tag_status_all();

	 bufindex = (blockid & 1) ? 0 : 1;

	 /* transpose the previous block */
         for (i = 0; i < BLOCK; i+= 4)
         {
            for (j = 0; j < BLOCK / 4; j++)
            {
               /* first phase */
               temp[0] = spu_shuffle(
                  buf[bufindex][i][j],
                  buf[bufindex][i+2][j],
                  maskLeft);
               temp[1] = spu_shuffle(
                  buf[bufindex][i][j],
                  buf[bufindex][i+2][j],
                  maskRight);
               temp[2] = spu_shuffle(
                  buf[bufindex][i+1][j],
                  buf[bufindex][i+3][j],
                  maskLeft);
               temp[3] = spu_shuffle(
                  buf[bufindex][i+1][j],
                  buf[bufindex][i+3][j],
                  maskRight);

               /* second phase */
               out[bufindex][j*4][i/4] =
                  spu_shuffle(temp[0], temp[2], maskLeft);
               out[bufindex][(j*4)+1][i/4] =
                  spu_shuffle(temp[0], temp[2], maskRight);
               out[bufindex][(j*4)+2][i/4] =
                  spu_shuffle(temp[1], temp[3], maskLeft);
               out[bufindex][(j*4)+3][i/4] =
                  spu_shuffle(temp[1], temp[3], maskRight);
            }
         }

	 /* calculating opposite location! */
	 oppoblockaddr = rowid * sizeof(float);

	 blockaddr = blockstart + ((blockid - 1) * sizeof(buf[0][0]));
	 opporowid = blockaddr / sizeof(float);
	 
	 /* write the block back out -> to the opposite location! */
	 for (row = opporowid; row < opporowid + BLOCK; row++)
	 {
	    dataaddr = package.destbuf + (row * N * sizeof(float)) + oppoblockaddr;
	    
	    mfc_put(
	       out[1 - (blockid & 1)][row % BLOCK],
	       dataaddr,
	       sizeof(buf[0][0]),
	       1 - (blockid & 1),
	       0,
	       0);
	 }
      }

      /* handle final block in row */

      mfc_write_tag_mask(2);
      mfc_read_tag_status_all();

      /* process remaining block */
      bufindex = (blockid == 1) ? 0 : 1;

      /* transpose the previous block */
      /* i indexes the row */
      for (i = 0; i < BLOCK; i+=4)
      {
         /* j indexes the column */
         for (j = 0; j < BLOCK / 4; j++)
         {
            /* first phase */
            temp[0] = spu_shuffle(
               buf[bufindex][i][j],
               buf[bufindex][i+2][j],
               maskLeft);
            temp[1] = spu_shuffle(
               buf[bufindex][i][j],
               buf[bufindex][i+2][j],
               maskRight);
            temp[2] = spu_shuffle(
               buf[bufindex][i+1][j],
               buf[bufindex][i+3][j],
               maskLeft);
            temp[3] = spu_shuffle(
               buf[bufindex][i+1][j],
               buf[bufindex][i+3][j],
               maskRight);

            /* second phase */
            out[bufindex][j*4][i/4] = spu_shuffle(temp[0], temp[2], maskLeft);
            out[bufindex][(j*4)+1][i/4] = spu_shuffle(temp[0], temp[2], maskRight);
            out[bufindex][(j*4)+2][i/4] = spu_shuffle(temp[1], temp[3], maskLeft);
            out[bufindex][(j*4)+3][i/4] = spu_shuffle(temp[1], temp[3], maskRight);
         }
      }

      /* calculating opposite for the previous block */
      blockaddr = blockstart + ((blockid - 1) * sizeof(buf[0][0]));

      oppoblockaddr = rowid * sizeof(float);
      opporowid = blockaddr / sizeof(float);

      /* write the block back out -> to the opposite location! */
      for (row = opporowid; row < opporowid + BLOCK; row++)
      {
         dataaddr = package.destbuf + (row * N * sizeof(float)) + oppoblockaddr;

         mfc_put(
            out[bufindex][row % BLOCK],
            dataaddr,
            sizeof(buf[0][0]),
            1,
            0,
            0);
      }

      mfc_read_tag_status_all();
   }

   return 0;
}
