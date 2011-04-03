#include <stdio.h>

/* Retorna o índice no vetor onde está o valor ou -1,
   caso o valor não esteja no vetor */

int busca(int vet[], int i, int f, int v) {
  int k;

  if (i > f)
    return -1;
  else {
    k = (i+f)/2;
    if (vet[k] == v)
      return k;
    else
      if (vet[k] < v)
	return busca(vet,k+1, f, v);
      else
	return busca(vet,i,k-1 , v);
  }
}

int main() {
  int k, v;
  int vet[10] = {3, 5, 7, 9, 12, 15, 16, 22, 26, 32};

  printf ("v: ");
  scanf("%d", &v);
  
  k = busca(vet, 0, 9, v); 
  
  if (k == -1)
    printf("O valor %d não está no vetor.\n", v);
  else
    printf("O valor %d está na posição %d.\n", v, k);

  return 0;
}
