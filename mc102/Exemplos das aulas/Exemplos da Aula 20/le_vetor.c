/*
 * Le um vetor de um arquivo. O primeiro inteiro lido eh
 * a dimensao do vetor.
 *
 * Escreve o vetor em um arquivo de saida.
 */
#include<stdio.h>
#include<stdlib.h>

int *le_vetor(int *n) {
  FILE *fr;
  int *v;
  int i;

  fr = fopen ("v-in.txt", "r");

  if (fr == NULL) {
    perror("v-in.txt");
    exit(-1);  /* Abandona o programa */  
  }
  
  fscanf(fr, "%d", n);
  v = (int *) malloc (*n * sizeof(int));
  
  for (i = 0; i < *n; i++)
    fscanf(fr, "%d", &v[i]);

  fclose(fr);
  
  return v;
}

void escreve_vetor(int *v, int n) {
  FILE  *fw;
  int i;

  fw = fopen ("v-out.txt", "w");

  if (fw == NULL) {
    perror("v-out.txt");
    exit(-1);  /* Abandona o programa */  
  }
  
  fprintf(fw, "%d\n", n); /* Dimensao do vetor */
  
  for (i = 0; i < n; i++)
    fprintf(fw, "%d\n", v[i]);

  fclose(fw);  
}

int main() {
  int *v;
  int n;
  
  v = le_vetor(&n);
  escreve_vetor(v, n);
  free(v);
  
  return 0;
}
