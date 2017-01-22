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



unsigned char parameter_area[128] __attribute__ ((aligned (128)));

int main(unsigned long long speid, addr64 argp, addr64 envp) 
{

  /* Here is the actual DMA call */
  /* the first parameter is the address in local store to place the data */
  /* the second parameter holds the main memory address                  */
  /* the third parameter holds the number of bytes to DMA                */
  /* the fourth parameter identifies a "tag" to associate with this DMA  */
  /* (this should be a number between 0 and 31, inclusive)               */
  /* the last two parameters are only useful if you've implemented your  */
  /* own cache replacement management policy.  Otherwise set them to 0.  */

  mfc_get(parameter_area, argp.ull, 128, 31, 0, 0);

  /* Now, we set the "tag bit" into the correct channel on the hardware  */
  /* this is always 1 left-shifted by the tag specified with the DMA     */
  /* for whose completion you wish to wait.                              */
  mfc_write_tag_mask(1<<31);

  /* Wait for the data array DMA to complete. */
  mfc_read_tag_status_all();


  printf("SPE: Data received is: %s", parameter_area );

  return 0;
}
