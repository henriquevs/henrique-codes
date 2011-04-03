#include <stdio.h>
#define TAMANHO 10

int separa (int v[], int p, int r) {

  int c = v[p]; /*Pivo*/
  int i = p+1;
  int j = r;
  int t;

  while (i <= j) {
    if (v[i] <= c) ++i;
    else if (c < v[j]) --j; 
    else {
      t = v[i]; 
      v[i] = v[j]; 
      v[j] = t;
      ++i; --j;
      }
  }

  t = v[p]; 
  v[p] = v[j]; 
  v[j] = t;
  return j; 
}

void quicksort (int v[], int p, int r) {
  int j;
  if (p < r) {
    j = separa (v, p, r); 
    quicksort (v, p, j-1); 
    quicksort (v, j+1, r);
  }
}


int main () {


  int vetor[TAMANHO] = {37,54,21,68,91,2,51,64,34,25};
  int i;

  quicksort (vetor, 0, TAMANHO - 1);
  
  printf ("{%d", vetor[0]);
  
  for (i = 1; i < TAMANHO; i++) {
    printf (", %d", vetor[i]);
  }

  printf ("}\n");
  
  system("pause");
  
  return 0;
}
