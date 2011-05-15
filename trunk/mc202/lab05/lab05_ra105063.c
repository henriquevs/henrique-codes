// Laboratório 05

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de cada no da arvore
typedef struct no {
	int elem;
	struct no *esq;
	struct no *dir;
} No;

// Estrutura da pilha utilizada nas operacoes de uniao e interseccao
typedef struct pilha {
	int num;
	struct pilha *prox;
} Pilha;

// Estrutura da lista ligada ("floresta") que contem o identificador e o ponteiro para cada arvore
typedef struct btlista {
	int id;
	struct no *abb;
	struct btlista *prox;
} BTLista;

// Teste de memoria para alocacao de arvores
void teste_memoria_1(BTLista *p){
   if(p == NULL){
      printf("Erro no malloc da arvore \n");
      exit(1);
   }
}

// Teste de memoria para alocacao de nos na arvore
void testa_memoria2(No *q){
   if(q == NULL){
      printf("Erro no malloc do no na arvore\n");
      exit(1);
   }
}

// Insere uma ABB (Arvore Binaria de Busca) na lista ligada ("floresta")
BTLista *cria_arvore(BTLista *lista){
   BTLista *ant, *q = lista;
   int flag = -1;
   
   if(q == NULL){ // "Floresta" vazia; insercao no inicio da lista de arvores
      q = (BTLista*)malloc(sizeof(BTLista));

      teste_memoria_1(q);
      
      q->id = flag + 1;
      q->abb = NULL;
      q->prox = NULL;
      printf("%d\n", q->id);
      lista = q;
   }
   else{
      while(q!=NULL){ // Insere no meio ou no final
         flag = q->id;
         ant=q;
         q=q->prox;
      }
      q=(BTLista*)malloc(sizeof(BTLista));

      teste_memoria_1(q);
      
      q->id = flag + 1;
      q->abb = NULL;
      q->prox = NULL;
      ant->prox = q;
      printf("%d\n", q->id);
   }
   return lista;
}

// Cria um no para a arvore e retorna um ponteiro para a raiz
No *cria_no(int elemento){
   No *novo=(No*)malloc(sizeof(No));
   
   testa_memoria2(novo);
   
   novo->elem = elemento;
   novo->esq = NULL;
   novo->dir = NULL;
   
   return novo;
}

// Procura a arvore na "floresta"
BTLista* procura_arvore(BTLista *lista, int identificador){
   BTLista *r=lista;
   while(r!=NULL){ // Se entrar no while é porque existe pelo menos uma arvore
      if(r->id == identificador){
         printf("Achou a arvore\n");
         return r; // Retorna um no da lista que contem a arvore
      }
      r=r->prox;
   }
   // Se sair do while, não existe a arvore procurada ou nao existe nenhuma arvore
   printf("Nao existe arvore.\n");
   return NULL;
}

// Adiciona um novo no na ABB
No *adiciona_no(No* arvore, int val){
   No* novo=cria_no(val);
   if(arvore == NULL)
      arvore=novo;
   
   else {
      if(arvore->elem < novo->elem) // Insere na esquerda
         arvore->esq = adiciona_no(arvore->esq, val);
      else // Insere na direita
         arvore->dir = adiciona_no(arvore->dir, val);
   }
   return arvore;
}

// Calcula a altura de uma ABB
int altura_arvore(No* arvore){
   int hesq, hdir;
   if(arvore==NULL) return 0;
      hesq = altura_arvore(arvore->esq);
      hdir = altura_arvore(arvore->dir);
   if(hesq > hdir)
      return 1+hesq;
   else
      return 1+hdir;
}

/* Converte a opcao da entrada em um inteiro a fim de poder-se utilizar "switch" na main */
int converte(char string[15]){
   int p;
   if(strcmp(string, "addABB") == 0)
      p = 1;
   
   if(strcmp(string, "addNo") == 0)
      p = 2;
   
   if(strcmp(string, "alturaABB") == 0)
      p = 3;
   
   if(strcmp(string, "folhasABB") == 0)
      p = 4;
   
   if(strcmp(string, "imprimirABB") == 0)
      p = 5;
   
   return p;
}

int main(){
   BTLista *lista=NULL, *aux;
   //No* p;
   char string[15];
   int q, indice, val, alturaabb;
   
   while(scanf("%s", string)!= EOF){
      q=converte(string);
   
      switch(q){
         case 1: // Criacao de uma arvore
            lista=cria_arvore(lista);
            break;
      
         case 2: // Insercao de no numa arvore
            scanf(" %d %d", &indice, &val);
            aux=procura_arvore(lista, indice);
            if(aux!=NULL) // So insere um no numa arvore existente
               aux->abb = adiciona_no(aux->abb, val);
            break;
         
         case 3: // Calcula a altura de uma ABB 
            scanf(" %d", &indice);
            printf("indice capturado: %d\n", indice);
            aux=procura_arvore(lista, indice);
            alturaabb=altura_arvore(aux->abb);
            printf("Altura da arvore %d: %d.\n", indice, alturaabb);
            break;
      }
   
   
   
   }
   return 0;
}