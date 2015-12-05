/* -*- mode: c -*-
 * $Id: heapsort.gcc,v 1.10 2001/05/08 02:46:59 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */

#define IM 139968
#define IA   3877
#define IC  29573
#include <stdio.h>

void heapsort(int n, unsigned int *ra);
void bubble_sort(unsigned int list[], int n);
void quicksort(unsigned int x[],int first,int last);

int
main(int argc, char *argv[]) {
  int N = 100;
  unsigned int ary[101];
  unsigned int ary2[101];
  int i;
    
  for (i=1; i<=N; i++) {
    ary[i] = (i%5); 
    ary2[i] = (i%5); 
  }

  heapsort(N, ary);
  bubble_sort(ary2, N+1);
  quicksort(ary2, 0, N);
  
//  for (i=1; i<=N; i++) {
//    printf("%d, %d\n", ary[i], ary2[i]);
//  }

  return(ary[1]+ary2[1]);
}

void
heapsort(int n, unsigned int *ra) {
  int i, j;
  int ir = n;
  int l = (n >> 1) + 1;
  unsigned int rra;

  for (;;) {
    if (l > 1) {
      rra = ra[--l];
    } else {
      rra = ra[ir];
      ra[ir] = ra[1];
      if (--ir == 1) {
        ra[1] = rra;
        return;
      }
    }
    i = l;
    j = l << 1;
    while (j <= ir) {
      if (j < ir && ra[j] < ra[j+1]) { ++j; }
      if (rra < ra[j]) {
        ra[i] = ra[j];
        j += (i = j);
      } else {
        j = ir + 1;
      }
    }
    ra[i] = rra;
  }
}

void bubble_sort(unsigned int list[], int n)
{
  int d, loops=0;
  int swap = 1;
  unsigned int t;
 
  while(swap)
  {
    swap = 0;
    for (d = 1 ; d < n - loops - 1; d++)
    {
      if (list[d] > list[d+1])
      {
	swap = 1;
        /* Swapping */
        t         = list[d];
        list[d]   = list[d+1];
        list[d+1] = t;
      }
    }
    loops++;
  }
}

void quicksort(unsigned int x[],int first,int last){
    int pivot,j,temp,i;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(x[i]<=x[pivot]&&i<last)
                 i++;
             while(x[j]>x[pivot])
                 j--;
             if(i<j){
                 temp=x[i];
                  x[i]=x[j];
                  x[j]=temp;
             }
         }

         temp=x[pivot];
         x[pivot]=x[j];
         x[j]=temp;
         quicksort(x,first,j-1);
         quicksort(x,j+1,last);

    }
}