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

/* Retorna o valor do elemento removido ou -1 caso
   a lista esteja vazia. */
int remove_final(No** ap_l) {
  No *n, *p;
  int v;

  if (*ap_l == NULL)
    return -1;
  if ((*ap_l)->prox == NULL) {
    n = *ap_l; 
    *ap_l = NULL;
  }
  else {
    p = *ap_l; /* PÃ¡ra no penÃºltimo elemento */
    while (p->prox->prox != NULL)
      p = p->prox;
    n = p->prox;
    p->prox = NULL;
  }
  v = n->v;
  free(n);
  return v;
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
  
  while (remove_final(&l) != -1)
    imprime_lista(l);

  return 0;
  
}
