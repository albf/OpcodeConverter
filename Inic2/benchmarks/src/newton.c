#include <stdio.h>

// Number of iterations
#define N 100

#ifdef X86
#else
#include "stdthing.h"
#endif

/* function */
float func(float x) {
  return ((x-3.2)*(x-6.2)*(x-16.4));
}

/* derivative*/
float deriv(float x)
{
  return (3 * (58- (17.2*x) + x*x));
}

int main(int argc,char *argv[])
{
  float x = 0;
  int i;
  
  for(i=0; i<N; i++) {
    x = x - (func(x)/deriv(x));
  }
  
  //printf("%f\n", x);
  //printf("%f\n", func(x));
  return (int) x;
}