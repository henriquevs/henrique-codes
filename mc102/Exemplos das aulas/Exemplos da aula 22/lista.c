#include <stdio.h>
#include <stdlib.h>

struct no {
  int v;
  struct no* prox;
};

typedef struct no No;

void imprime_lista(No* l) {
  while (l != NULL) {
    printf("%d\n", l->v);
    l = l->prox;
  }
  printf("\n");
}

int main() {
  No* n0, *n1, *n2;

  n0 = (No*) malloc(sizeof(No));
  n1 = (No*) malloc(sizeof(No));
  n2 = (No*) malloc(sizeof(No));  

  n0->v = 3;
  n0->prox = n1;

  n1->v = 5;
  n1->prox = n2;

  n2->v = 9;
  n2->prox = NULL;

  imprime_lista(n0);
  
  free(n0);
  free(n1);
  free(n2);
  
  system("pause");
  
  return 0;
  
}
