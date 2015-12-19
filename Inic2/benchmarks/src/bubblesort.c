/* -*- mode: c -*-
 * $Id: heapsort.gcc,v 1.10 2001/05/08 02:46:59 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */

#define N 10
#define REPEAT 1
#define X86 0
#define DEBUG 0

void bubble_sort(unsigned int list[], int n);

//#define X86

#ifdef X86
/*#include <stdio.h>
void print(const char *str) {
  printf("%s", str);
}

void printnum(int n) {
  printf("%d", n);
}*/
#else
#include "stdthing.h"
#endif

int
main(int argc, char *argv[]) {
  unsigned int ary[N];
  unsigned int value;
  int i, j;
  
  value = N;
  
  for (j=0; j<REPEAT; j++) {
    for (i=0; i<N; i++) {
      ary[i] = value;
      value--;
    }
  }

  bubble_sort(ary, N);

  #if DEBUG
  for (i=0; i<N; i++) {
    printf("%d ", ary[i]);
  }
  printf("\n");
  #endif
    
  return(0);
}

void bubble_sort(unsigned int list[], int n)
{
  int c, d;
  unsigned int t;
 
  for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (list[d] > list[d+1])
      {
        /* Swapping */
        t         = list[d];
        list[d]   = list[d+1];
        list[d+1] = t;
      }
    }
  }
}