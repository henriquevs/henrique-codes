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

void insere_final(No** ap_l, int v) {
  No *n, *p;
  n = (No*) malloc(sizeof(No));
  n->v = v;
  n->prox = NULL;  /* Ultimo elemento da lista */
  if (*ap_l == NULL) 
    *ap_l = n;
  else {
    p = *ap_l;
    while (p->prox != NULL)
      p = p->prox;
    p->prox = n;
  }
}

int main() {
  No* l; 

  l = NULL;

  insere_final(&l, 1);
  imprime_lista(l);
  insere_final(&l, 3);
  imprime_lista(l);
  insere_final(&l, 5);
  imprime_lista(l);
  
  libera(l);

  return 0;
  
}
