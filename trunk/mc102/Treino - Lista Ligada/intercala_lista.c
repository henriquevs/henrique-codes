#include <stdio.h>
#include <stdlib.h>

 struct item
 {
     int info;
     struct item *prox;
};

 struct item * insereDepoisLista(struct item **p0, struct item *pd, int x)
 {
     struct item *p;
     p = (struct item *)malloc(sizeof(struct item));
     p->info = x;
     p->prox = NULL;
     if (pd == NULL) *p0 = p;
     else pd->prox = p;
     return p;
 }
 
 void leiaLista(struct item **p0)
 {
     int i, n, val;
     struct item *pUltimo = NULL;
     scanf("%d", &n);
     for (i = 1; i <= n; i = i + 1)
     {
         scanf("%d", &val);
         pUltimo = insereDepoisLista(p0, pUltimo, val);
     }
 }
 
 void imprimaLista(struct item *p0)
 {
     struct item *p = p0;
     while (p != NULL)
     {
         printf("%d ", p->info);
         p = p->prox;
     }
     putchar('\n');
 }
 
 struct item * intercaleLista(struct item **p0, struct item **p1)
 {
     struct item *p01 = NULL;
     struct item *pa, *pb, *pc;
     if (*p0 == NULL) p01 = *p1;
     else
         if (*p1 == NULL) p01 = *p0;
         else
         {
             pa = *p0;
             pb = *p1;
             if (pa->info < pb->info)
             {
                 p01 = pa;
                 pa = pa->prox;
             }
             else
             {
                 p01 = pb;
                 pb = pb->prox;
             }
             pc = p01;
             while (pa != NULL && pb != NULL)
             {
                 if (pa->info < pb->info)
                 {
                     pc->prox = pa;
                     pc = pa;
                     pa = pa->prox;
                 }
                 else
                 {
                     pc->prox = pb;
                     pc = pb;
                     pb = pb->prox;
                 }
             }
             if (pa == NULL) pc->prox = pb;
             else pc->prox = pa;
         }
     *p0 = NULL;
     *p1 = NULL;
     return p01;
 }
 
 int main(void)
 {
     struct item *listaA = NULL, *listaB = NULL, *listaC;
     leiaLista(&listaA);
     imprimaLista(listaA);
     leiaLista(&listaB);
     imprimaLista(listaB);
     listaC = intercaleLista(&listaA, &listaB);
     imprimaLista(listaC);
     return 0;
}
