#include <stdio.h>
#include <stdlib.h>

struct no {
  int v;
  struct no* prox;
};

typedef struct no No;


void imprime_lista(No* l) {
  if ( l == NULL) {
    return;
  }
  else {
 	 printf(" %d", l->v);
    l = l->prox;
    imprime_lista(l);
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
  No *l, *n; 

  l = NULL;

 // imprime_lista(l);
  printf("(");
  imprime_lista(l);
  printf(" )\n");
  
  //insere no comeco da lista
  n = (No*) malloc(sizeof(No));
  n->v = 3;
  n->prox = l;
  l = n;
  
  printf("(");
  imprime_lista(l);
  printf(" )\n");
  
 // imprime_lista(l);
  //insere no comeco da lista
  n = (No*) malloc(sizeof(No));
  n->v = 5;
  n->prox = l;
  l = n;
  
  printf("(");
  imprime_lista(l);
  printf(" )\n");
  
  //insere no comeco da lista
  n = (No*) malloc(sizeof(No));
  n->v = 7;
  n->prox = l;
  l = n;
  
  printf("(");
  imprime_lista(l);
  printf(" )\n");
  
  libera(l);

  return 0;
  
}
