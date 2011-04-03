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

void insere_comeco(No** ap_l, int v) {
  No* n;
  n = (No*) malloc(sizeof(No));
  n->v = v;
  n->prox = *ap_l;
  *ap_l = n;
}

/* Retorna o valor do elemento removido ou -1 caso
   a lista esteja vazia. */
int remove_comeco(No** ap_l) {
  No* n;
  int v;

  if (*ap_l == NULL)
    return -1;
  n = *ap_l;
  *ap_l = n->prox;  
  v = n->v;
  free(n);
  return v;
}

int main() {
  No* l; 

  l = NULL;

  insere_comeco(&l, 5);
  insere_comeco(&l, 3);
  insere_comeco(&l, 1);
  imprime_lista(l);

  while (remove_comeco(&l) != -1)
    imprime_lista(l);

  system("pause");
  
  return 0;
  
}
