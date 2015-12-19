/* -*- mode: c -*-
 * $Id: ackermann.gcc,v 1.5 2001/05/04 01:21:38 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */

#define X86 1

int Ack(int M, int N);

//#define X86

#ifdef X86

/* #include <stdio.h>

void print(const char *str) {
  printf("%s", str);
}

void printnum(int n) {
  printf("%d", n);
} */
#else
#include "stdthing.h"
#endif

int
main(int argc, char *argv[]) {
  int n = 10;
  int res = Ack(3, n);
  return res;
}

int
Ack(int M, int N) {
  if (M == 0) return( N + 1 );
  if (N == 0) return( Ack(M - 1, 1) );
  return( Ack(M - 1, Ack(M, (N - 1))) );
}