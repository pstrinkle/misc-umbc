
#ifndef PU_THREADS_H
#define PU_THREADS_H

#define N 2048
#define THREADCNT 8

typedef struct transpose_package
{
      unsigned long long srcbuf;
      unsigned long long destbuf;
      unsigned int id;
} __attribute__ ((aligned(16))) transpose_package_t ;

#endif
