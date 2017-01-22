#ifndef __common_h__
#define __common_h__

/* This union helps clarify calling parameters between the PPE and the SPE. */

typedef union
{
  unsigned long long ull;
  unsigned int ui[2];
  void *p;
} addr64;

// total 1000*1000 = 4,000,000 B
// total 4000*4000 = 64,000,000 B
# define ssize 2048
# define tsize 1*2048*ssize
# define loops 1

typedef struct record_struct {
	int key;
	int data;
	int data1,data3;
} record ;

#endif /* __common_h__ */
