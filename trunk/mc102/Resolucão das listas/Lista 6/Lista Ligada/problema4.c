/* Lista de Exercicios 6 - Lista Ligada - Problema 4 */
#include <stdio.h>
#include <stdlib.h>

/* Assumimos que cada no da lista eh formado por dois campos: um que contem um inteiro e outro que aponta para o proximo no da lista */
typedef struct lista{
   int numero;
   struct lista* prox;
}No;

/* Funcao que cria um no */
No* criaNo(int numero, No* prox){
   No* p1;
   p1 = (No*)malloc(sizeof(No));
   p1->numero = numero;
   p1->prox = prox;

   return p1;
}

/* Funcao que cria uma lista com n nos, n eh passado na entrada */
No* criaLista(int n_nos, No* p){
   int contador = 0;
   int preenche = 0;
   while(contador < n_nos){
      p = criaNo(preenche, p);
      preenche++;
      contador++;
   }
   return p;
}

/* Funcao que divide a lista ligada em duas sub-listas */
No* divide(int n_nos, No* p1, No* p2){
   No* ant;
   int meio = (n_nos)/2;
   int contador = 0;
   p2 = p1;
   while(contador <= meio){
      ant = p2;
      p2 = p2->prox;
      contador++;
   }
   
   (*ant).prox = NULL;
   return p1, p2;
}

void imprime(No* p){
   while(p != NULL){
      printf("%d ", p->numero);
      p = p->prox;
   }
   printf("\n\n");   
}

int main(){
   int n_nos;
   No* p1, *p2;
   p1 = NULL;
   p2 = NULL;
   
   printf("Entre com o tamanho da lista: ");
   scanf("%d", &n_nos);

   criaLista(n_nos, p1);
   divide(n_nos, p1, p2);
   imprime(p1);
   imprime(p2);
   
   system("pause");

   return 0;
}
