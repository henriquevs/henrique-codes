#include <stdio.h>
#include <limits.h>

#define TAMANHO 10

void intercala (int p, int q, int r, int v[]) {
  int i, j, k;
  int w[TAMANHO];

  i = p; 
  j = q;
  k = 0;

  while (i < q && j <= r) {
    if (v[i] <= v[j])  
      w[k++] = v[i++];
    else  
      w[k++] = v[j++];
  }
  
  while (i < q)  
    w[k++] = v[i++];

  while (j <= r)  
    w[k++] = v[j++];

  for (i = p; i <= r; i++)  
    v[i] = w[i-p];
}

void mergesort (int p, int r, int v[]) {
  if (p < r) {
    int q = (p + r)/2;
    mergesort (p, q, v);
    mergesort (q + 1, r, v);
    intercala (p, q + 1, r, v);
  }
}

int main () {
  
  int vetor[TAMANHO] = {37,54,21,68,91,2,51,64,34,25};
  int i;

  mergesort (0, TAMANHO - 1, vetor);
  
  printf ("{%d", vetor[0]);
  
  for (i = 1; i < TAMANHO; i++) {
    printf (", %d", vetor[i]);
  }

  printf ("}\n");
  
  return 0;
}
