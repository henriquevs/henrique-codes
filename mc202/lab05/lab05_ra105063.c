// Laborat�rio 05 - Opcoes de 1 a 5 funcionam corretamente

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
void testa_memoria1(BTLista *p){
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

// Teste de memoria para a pilha
void testa_memoria3(Pilha *topo){
   if(topo == NULL){
      fprintf(stderr, "Erro no malloc da pilha\n");
      exit(1);
   }
}

// Insere uma ABB (Arvore Binaria de Busca) na lista ligada ("floresta")
BTLista *cria_arvore(BTLista *lista){
   BTLista *ant, *q = lista;
   int flag = -1;
   
   if(q == NULL){ // "Floresta" vazia; insercao no inicio da lista de arvores
      q = (BTLista*)malloc(sizeof(BTLista));

      testa_memoria1(q);
      
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

      testa_memoria1(q);
      
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
   while(r!=NULL){ // Se entrar no while � porque existe pelo menos uma arvore
      if(r->id == identificador){
         printf("Achou a arvore\n");
         return r; // Retorna um no da lista que contem a arvore
      }
      r=r->prox;
   }
   // Se sair do while, n�o existe a arvore procurada ou nao existe nenhuma arvore
   printf("Nao existe arvore.\n");
   return NULL;
}

// Adiciona um novo no na ABB
No *adiciona_no(No* arvore, int val){
   No* novo=cria_no(val);
   if(arvore == NULL)
      arvore=novo;
   
   else {
      if(arvore->elem > novo->elem) // Insere na esquerda
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

// Calcula o numero de nos-folha de uma ABB
int folhas_arvore(No* arvore){
   if(arvore == NULL)
      return 0;
   if(arvore->esq == NULL && arvore->dir == NULL)
      return 1;
   else
      return folhas_arvore(arvore->esq) + folhas_arvore(arvore->dir);
}

// Imprime a ABB em ordem pre-fixa
int imprime_pre_fixa(No* arvore){
   if(arvore==NULL) return 0;
   if(arvore!=NULL){
   printf("%d ", arvore->elem);
   imprime_pre_fixa(arvore->esq);
   imprime_pre_fixa(arvore->dir);
   }
   return 1;
}

// Imprime a ABB em ordem in-fixa
int imprime_in_fixa(No* arvore){
   //if(arvore==NULL) return 0;
   if(arvore!=NULL){
   imprime_in_fixa(arvore->esq);
   printf("%d ", arvore->elem);
   imprime_in_fixa(arvore->dir);
   }
   return 1;
}

// Imprime a ABB em ordem pos-fixa
int imprime_pos_fixa(No* arvore){
   if(arvore==NULL) return 0;
   if(arvore!=NULL){
   imprime_pos_fixa(arvore->esq);
   imprime_pos_fixa(arvore->dir);
   printf("%d ", arvore->elem);
   }
   return 1;
}

// Inicializa��o da pilha
Pilha* inicializa(Pilha *topo){
   topo = NULL;
   return topo;
}

typedef enum{FALSE, TRUE} booleano;

// Verifica se a pilha esta vazia; retorna 0 caso seja falso e 1 caso verdadeiro
booleano vazia(Pilha *topo){
   return topo==NULL;
}

// Empilha os valores na pilha
Pilha *empilhar(Pilha *topo, int val){
   Pilha *p=(Pilha*)malloc(sizeof(Pilha));
   
   testa_memoria3(p);
   
   p->num = val;
   p->prox = NULL;
   topo = p;
   return topo;
}

// Desempilha os valores da pilha e libera a memoria alocada
int desempilhar(Pilha *topo){
   int tmp;
   Pilha *q=topo;
   if(vazia(q)==1){
      fprintf(stderr, "Pilha vazia\n");
      exit(1);
   }
   tmp=q->num;
   topo=topo->prox;
   free(q);
   return tmp;
}

// Capta os valores da arvore em ordem infixa e armazena numa pilha
Pilha *empilhando_infixa(No *arvore, Pilha *topo){
   if(arvore!=NULL){
      topo = empilhando_infixa(arvore->esq, topo);
      topo = empilhar(topo, arvore->elem);
      topo = empilhando_infixa(arvore->dir, topo);
   }
   return topo;
}

// Realiza a opera��o de Uniao entre duas arvores
//No *uniao(

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
   BTLista *lista=NULL, *aux, *tmp;
   //No* p;
   char string[15];
   int q, indice, val, altura_abb, folhas_abb, indice_arv1, indice_arv2;
   
   while(scanf("%s", string)!= EOF){
      q=converte(string);
   
      switch(q){
         case 1: // Criacao de uma ABB
            lista=cria_arvore(lista);
            break;
      
         case 2: // Insercao de no numa ABB
            scanf(" %d %d", &indice, &val);
            aux=procura_arvore(lista, indice);
            if(aux!=NULL) // So insere um no numa arvore existente
               aux->abb = adiciona_no(aux->abb, val);
            break;
         
         case 3: // Calcula a altura de uma ABB 
            scanf(" %d", &indice);
            printf("indice capturado: %d\n", indice);
            aux=procura_arvore(lista, indice);
            if(aux!=NULL){ // Soh calcula a altura de uma ABB existente
               altura_abb=altura_arvore(aux->abb);
               printf("Altura da arvore %d: %d.\n", indice, altura_abb);
            }
            break;
            
         case 4: // Soh calcula o numero de folhas de uma ABB existente
            scanf(" %d", &indice);
            aux=procura_arvore(lista, indice);
            if(aux!=NULL){
               folhas_abb=folhas_arvore(aux->abb);
               printf("Numero de folhas da arvore %d: %d.\n", indice, folhas_abb);
            }
            break;
            
         case 5: //Imprime a ABB (em nota��es prefixa, infixa e posfixa)
            scanf(" %d", &indice);
            aux=procura_arvore(lista, indice);
            // Em todos os casos, imprime somente quando a arvore existe e ela nao eh vazia
            if(aux!=NULL){
               
               printf("Pre-ordem:\t");
               val=imprime_pre_fixa(aux->abb);
               if(val==1)
                  ungetc(' ',stdin);
               printf("\n");
               
               printf("In-ordem:\t");
               val=imprime_in_fixa(aux->abb);
               if(val==1)
                  ungetc(' ',stdin);
               printf("\n");
               
               printf("Pos-ordem:\t");
               val=imprime_pos_fixa(aux->abb);
               if(val==1)
                  ungetc(' ',stdin);
               printf("\n");
            }
            break;
            
            default:
               //printf("string capturada: %s\n", string);
               //printf("primeiro char:%c; segundo char:%c; terceiro char:%c\n", string[0], string[1], string[2]);
               if(string[2] != 'U' && string[2] != 'I')
                  printf("Operacao invalida no default\n");
               else{
                  //printf("Primeiro  -  indices:\narvore1:%c\tarvore2:%c\n\n", string[0], string[1]);
                  indice_arv1=(int)(string[0]) - 48;
                  indice_arv2=(int)(string[1]) - 48;
                  aux=procura_arvore(lista, indice_arv1);
                  tmp=procura_arvore(lista, indice_arv2);
                  if(aux!=NULL && tmp!=NULL)
                     printf("Indices:\narvore1:%d\tarvore2:%d\n", indice_arv1, indice_arv2);
               }
               break;
      }
   
   
   
   }
   return 0;
}