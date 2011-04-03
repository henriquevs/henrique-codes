#include <stdio.h>
#include <stdlib.h>
   
struct item{
       int info;
       struct item *prox;
};
   
struct item *insereDepoisLista(struct item **p0, struct item *pd, int x){
       struct item *p;
       p = (struct item *)malloc(sizeof(struct item));
       p->info = x;
       p->prox = NULL;
       if (pd == NULL) *p0 = p;
       else pd->prox = p;
       return p;
}
   
void leiaLista(struct item **p0){
       int i, n, val;
       struct item *pUltimo = NULL;
       scanf("%d", &n);
       for (i = 1; i <= n; i = i + 1){
           scanf("%d", &val);
           pUltimo = insereDepoisLista(p0, pUltimo, val);
       }
}
   
void imprimaLista(struct item *p0){
       struct item *p = p0;
       while (p != NULL){
           printf("%d ", p->info);
           p = p->prox;
       }
       putchar('\n');
}
   
struct item *concatenaLista(struct item **p0, struct item **p1){
       struct item *p01 = NULL;
       struct item *p;
       if (*p0 == NULL) p01 = *p1;
       else{
           p01 = *p0;
           if (*p1 != NULL){
               p = *p0;
               while (p->prox != NULL) p = p->prox;
               p->prox = *p1;
           }
       }
       *p0 = NULL;
       *p1 = NULL;
       return p01;
}
   
int main(void){
       struct item *listaA = NULL, *listaB = NULL, *listaC;
       leiaLista(&listaA);
       imprimaLista(listaA);
       leiaLista(&listaB);
       imprimaLista(listaB);
       listaC = concatenaLista(&listaA, &listaB);
       imprimaLista(listaC);
       return 0;
}
