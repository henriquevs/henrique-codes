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
}

/* Por que esta rotina pode nÃ£o funcionar? */
void libera_com_bug(No *l) {
  while (l!=NULL) {
    free(l);
    l = l->prox;
  }
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
  
  libera(n0);
  
  return 0;
  
}
