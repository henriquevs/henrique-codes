#include <stdio.h>
#include <limits.h>

#define TAMANHO 16

void mostra_vetor(int v[]) {
  int i, j;
  for (i = TAMANHO-1; i >=0; i--) {
    printf("|");
    for (j = 0; j < TAMANHO; j++) 
      if (v[j] == i)
	printf(" XXX");
      else
	printf("    ");	
    printf("\n");
  }
  for (j = 0; j <= 4* TAMANHO; j++) 
      printf("-");    
  printf("\n");
  printf ("{  %2d", v[0]);
  
  for (i = 1; i < TAMANHO; i++) {
    printf (", %2d", v[i]);
  }

  printf ("}\n");
  
}

/* Intercala as seqüências v[p]..v[q-1] e v[q]..v[r] */
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

int main () {
  
  int vetor[TAMANHO] = {2,4,5,7,9,11,13,15,0,1,3,6,8,10,12,14};

  mostra_vetor(vetor);
  intercala(0, TAMANHO/2, TAMANHO-1, vetor);
  mostra_vetor(vetor);
  
  
  return 0;
}
