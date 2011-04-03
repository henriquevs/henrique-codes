#include <stdio.h>
#include <stdlib.h>

struct item
{
    int info;
    struct item *prox;
};

struct item *insereDepoisLista(struct item **p0, struct item *pd, int x)
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

void invertaLista(struct item **p0)
{
    struct item *pa, *p, *pd;
    if (*p0 != NULL)
    {
        pa = NULL;
        p = *p0;
        pd = p->prox;
        do
        {
            p->prox = pa;
            pa = p;
            p = pd;
            if (pd != NULL)
                pd = pd->prox;
        }
        while (p != NULL);
        *p0 = pa;
    }
}

int main(void)
{
    struct item *lista = NULL;
    leiaLista(&lista);
    imprimaLista(lista);
    invertaLista(&lista);
    imprimaLista(lista);
    
    system("pause");
    
    return 0;
}
