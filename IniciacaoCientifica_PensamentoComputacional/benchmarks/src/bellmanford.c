/* bellman-ford.c57.  C57 code to run the Bellman-Ford algorithm on a
   small directed graph. */

#include <stdio.h>

/* Relax edge (u,v) with weight w. */
void relax(int u, int v, int w, int d[], int pi[]) {
  if (d[v] > d[u] + w) {
    d[v] = d[u] + w;
    pi[v] = u;
  }
}

/* Initialize a single-source shortest-paths computation. */
void initialize_single_source(int d[], int pi[], int s, int n) {
  int i;
  for (i = 1; i <= n; ++i) {
    d[i] = 1000000;
    pi[i] = 0;
  }

  d[s] = 0;
}

/* Run the Bellman-Ford algorithm from vertex s.  Fills in arrays d
   and pi. */
int bellman_ford(int first[], int node[], int next[], int w[], int d[],
		 int pi[], int s, int n) {
  int u, v, i, j;

  initialize_single_source(d, pi, s, n);

  for (i = 1; i <= n-1; ++i) {
    for (u = 1; u <= n; ++u) {
      j = first[u];

      while (j > 0) {
	v = node[j];
	relax(u, v, w[j], d, pi);
	j = next[j];
      }
    }
  }

  for (u = 1; u <= n; ++u) {
    j = first[u];

    while (j > 0) {
      v = node[j];
      if (d[v] > d[u] + w[j])
	return 0;
      j = next[j];
    }
  }

  return 1;
}

int main(void) {
  int first[11], node[26], next[26], pi[11];
  int w[26], d[11];
  int s;
  int i;
  int ok;

  /* The graph contains the following directed edges with weights:
     (1, 2), weight 6
     (1, 4), weight 7
     (2, 3), weight 5
     (2, 4), weight 8
     (2, 5), weight -4
     (3, 2), weight -2
     (4, 3), weight -3
     (4, 5), weight 9
     (5, 1), weight 2
     (5, 3), weight 7
  */

  first[1] = 1;
  first[2] = 3;
  first[3] = 6;
  first[4] = 7;
  first[5] = 9;
  first[6] = 12;
  first[7] = 14;
  first[8] = 18;
  first[9] = 20;
  first[10] = 24;

  node[1] = 2;
  node[2] = 4;
  node[3] = 3;
  node[4] = 4;
  node[5] = 5;
  node[6] = 2;
  node[7] = 3;
  node[8] = 5;
  node[9] = 1;
  node[10] = 3;
  node[11] = 6;
  node[12] = 7;
  node[13] = 8;
  node[14] = 9;
  node[15] = 10;
  node[16] = 1;
  node[17] = 2;
  node[18] = 9;
  node[19] = 4;
  node[20] = 10;
  node[21] = 2;
  node[22] = 10;
  node[23] = 5;
  node[24] = 4;
  node[25] = 3;

  w[1] = 6;
  w[2] = 7;
  w[3] = 5;
  w[4] = 8;
  w[5] = -4;
  w[6] = -2;
  w[7] = -3;
  w[8] = 9;
  w[9] = 2;
  w[10] = 7;
  w[11] = 4;
  w[12] = 2;
  w[13] = 9;
  w[14] = 1;
  w[15] = 5;
  w[16] = 3;
  w[17] = 4;
  w[18] = 9;
  w[19] = 6;
  w[20] = 12;
  w[21] = 1;
  w[22] = 9;
  w[23] = 2;
  w[24] = 1;
  w[25] = 4;

  next[1] = 2;
  next[2] = 0;
  next[3] = 4;
  next[4] = 5;
  next[5] = 0;
  next[6] = 0;
  next[7] = 8;
  next[8] = 0;
  next[9] = 10;
  next[10] = 11;
  next[11] = 0;
  next[12] = 13;
  next[13] = 0;
  next[14] = 15;
  next[15] = 16;
  next[16] = 17;
  next[17] = 0;
  next[18] = 19;
  next[19] = 0;
  next[20] = 21;
  next[21] = 22;
  next[22] = 23;
  next[23] = 0;
  next[24] = 25;
  next[25] = 0;

  //printf("Enter source node: ");
  //scanf("%d", &s);
  s = 1;

  ok = bellman_ford(first, node, next, w, d, pi, s, 10);

  //printf("bellman_ford returns ");
  //printf("%d\n\n", ok);

  int ret=0;
  
  for (i = 1; i <= 5; ++i) {
    //printf("%d: %f  %d\n", i, d[i], pi[i]);
    ret+=d[i]+pi[i];
  }

  return ret;
}
