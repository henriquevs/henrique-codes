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

void nao_insere_comeco(No* l, int v) {
  No* n;
  n = (No*) malloc(sizeof(No));
  n->v = v;
  n->prox = l;
  l = n;
  imprime_lista(l);
}

void insere_comeco(No** ap_l, int v) {
  No* n;
  n = (No*) malloc(sizeof(No));
  n->v = v;
  n->prox = *ap_l;
  *ap_l = n;
  imprime_lista(*ap_l);
}

int main() {
  No* l; 

  l = NULL;

  nao_insere_comeco(l, 3);
  imprime_lista(l);

  insere_comeco(&l, 5);
  imprime_lista(l);
  insere_comeco(&l, 3);
  imprime_lista(l);
  insere_comeco(&l, 1);
  imprime_lista(l);
  
  libera(l);

  system("pause");

  return 0;
  
}
