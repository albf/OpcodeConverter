/*
 * Computation of the n'th decimal digit of \pi with very little memory.
 * Written by Fabrice Bellard on January 8, 1997.
 * 
 * We use a slightly modified version of the method described by Simon
 * Plouffe in "On the Computation of the n'th decimal digit of various
 * transcendental numbers" (November 1996). We have modified the algorithm
 * to get a running time of O(n^2) instead of O(n^3log(n)^3).
 * 
 * This program uses mostly integer arithmetic. It may be slow on some
 * hardwares where integer multiplications and divisons must be done
 * by software. We have supposed that 'int' has a size of 32 bits. If
 * your compiler supports 'long long' integers of 64 bits, you may use
 * the integer version of 'mul_mod' (see HAS_LONG_LONG).  
 */

#include <stdlib.h>
#include <stdio.h>

#define X86 1

float sqrt2(const float m);
double mod (double x);
double fmod( double x, double y );
/*float logn(const float x);

float logn(const float x) {
  float y;
  
  y = x-1; 
  y = y - ((x-1)*(x-1))/2;
  y = y + ((x-1)*(x-1)*(x-1))/3;
  y = y - ((x-1)*(x-1)*(x-1)*(x-1))/4;
  
  return y;
}*/

float sqrt2(const float m)
{
   float i=0, j;
   float x1,x2;
   while( (i*i) <= m )
          i+=0.1f;
   x1=i;
   for(j=0;j<10;j++)
   {
       x2=m;
      x2/=x1;
      x2+=x1;
      x2/=2;
      x1=x2;
   }
   return x2;
}   

double mod (double x) {
  if (x < 0)
    return -x;
  else
    return x;
}

double fmod( double x, double y ) {
  if((x*y) > 0) {
    while(mod(x)>=mod(y))
      x = x - y;
    return x;
  }
  else {
    while(mod(x)>=mod(y))
      x = x + y;
    return x;
  }
}

/* uncomment the following line to use 'long long' integers */
/* #define HAS_LONG_LONG */

#ifdef HAS_LONG_LONG
#define mul_mod(a,b,m) (( (long long) (a) * (long long) (b) ) % (m))
#else
#define mul_mod(a,b,m) fmod( (double) a * (double) b, m)
#endif

#ifdef X86
#else
#include "stdthing.h"
#endif

#define NTH_VALUE 10

/* return the inverse of x mod y */
int inv_mod(int x,int y) {
  int q,u,v,a,c,t;

  u=x;
  v=y;
  c=1;
  a=0;
  do {
    q=v/u;
    
    t=c;
    c=a-q*c;
    a=t;
    
    t=u;
    u=v-q*u;
    v=t;
  } while (u!=0);
  a=a%y;
  if (a<0) a=y+a;
  return a;
}

/* return (a^b) mod m */
int pow_mod(int a,int b,int m)
{
  int r,aa;
   
  r=1;
  aa=a;
  while (1) {
    if (b&1) r=mul_mod(r,aa,m);
    b=b>>1;
    if (b == 0) break;
    aa=mul_mod(aa,aa,m);
  }
  return r;
}
      
/* return true if n is prime */
int is_prime(int n)
{
   int r,i;
   if ((n % 2) == 0) return 0;

   r=(int)(sqrt2(n));
   for(i=3;i<=r;i+=2) if ((n % i) == 0) return 0;
   return 1;
}

/* return the prime number immediatly after n */
int next_prime(int n)
{
   do {
      n++;
   } while (!is_prime(n));
   return n;
}

int main(int argc,char *argv[])
{
  int av,a,vmax,N,n,num,den,k,kq,kq2,t,v,s,i;
  double sum;
  
  n=NTH_VALUE;
  
  N=(int)((n+20)*log(10)/log(2));

  sum=0;

  for(a=3;a<=(2*N);a=next_prime(a)) {

    vmax=(int)(log(2*N)/log(a));
    av=1;
    for(i=0;i<vmax;i++) av=av*a;

    s=0;
    num=1;
    den=1;
    v=0;
    kq=1;
    kq2=1;

    for(k=1;k<=N;k++) {

      t=k;
      if (kq >= a) {
	 do {
	    t=t/a;
	    v--;
	 } while ((t % a) == 0);
	 kq=0;
      }
      kq++;
      num=mul_mod(num,t,av);

      t=(2*k-1);
      if (kq2 >= a) {
	 if (kq2 == a) {
	    do {
	       t=t/a;
	       v++;
	    } while ((t % a) == 0);
	 }
	 kq2-=a;
      }
      den=mul_mod(den,t,av);
      kq2+=2;
      
      if (v > 0) {
	t=inv_mod(den,av);
	t=mul_mod(t,num,av);
	t=mul_mod(t,k,av);
	for(i=v;i<vmax;i++) t=mul_mod(t,a,av);
	s+=t;
	if (s>=av) s-=av;
      }
      
    }

    t=pow_mod(10,n-1,av);
    s=mul_mod(s,t,av);
    sum=fmod(sum+(double) s/ (double) av,1.0);
  }
  printf("Decimal digits of pi at position %d: %09d\n",n,(int)(sum*1e9));
  return sum;
}