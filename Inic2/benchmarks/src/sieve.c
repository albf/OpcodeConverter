/* -*- mode: c -*-
 * $Id: sieve.gcc,v 1.7 2001/05/06 04:37:45 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */

//#define X86

#ifdef X86
#include <stdio.h>
void print(const char *str) {
  printf("%s", str);
}

void printnum(int n) {
  printf("%d", n);
}
#else
#include "stdthing.h"
void *memset(void *s, int c, unsigned int n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

#endif


int
main(int argc, char *argv[]) {
  int NUM = 150;
  char flags[768 + 1];
  long i, k;
  int count = 0;

  while (NUM--) {
    count = 0;
    for (i=2; i <= 500; i++) {
      flags[i] = 1;
    }
    for (i=2; i <= 500; i++) {
      if (flags[i]) {
        // remove all multiples of prime: i
        for (k=i+i; k <= 500; k+=i) {
          flags[k] = 0;
        }
        count++;
      }
    }
  }
  print("Count: ");
  printnum(count);
  print("\n");
  return(0);
}
