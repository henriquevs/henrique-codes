#include <stdio.h>
#include <stdlib.h>

struct no {
  int v;
  struct no* prox;
};

typedef struct no No;

void imprime_lista(No* l) {
  printf("(");
  if (l != NULL) {
    printf("%d", l->v);
    l = l->prox;
  }
  while (l != NULL) {
    printf(", %d", l->v);
    l = l->prox;
  }
  printf(")\n");
}

void libera(No* l) {
  No* f;
  
  while (l != NULL) {
    f = l;
    l = l->prox;
    free(f);
  }
}



int main() {
  No *l, *n; 

  l = NULL;

  imprime_lista(l);
  
  //insere no comeco da lista
  n = (No*) malloc(sizeof(No));
  n->v = 3;
  n->prox = l;
  l = n;
  
  imprime_lista(l);
  
  //insere no comeco da lista
  n = (No*) malloc(sizeof(No));
  n->v = 5;
  n->prox = l;
  l = n;
 
  imprime_lista(l);

  //insere no comeco da lista
  n = (No*) malloc(sizeof(No));
  n->v = 7;
  n->prox = l;
  l = n;

  imprime_lista(l);
  
  libera(l);

  system("pause");

  return 0;
  
}
