/*  UNICAMP - Universidade Estadual de Campinas
    MC202 - Estruturas de Dados
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratorio 05 - Árvore Binária de Busca e Pilhas  */
    
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
         //printf("Achou a arvore %d\n", r->id);
         return r; // Retorna um no da lista que contem a arvore
      }
      r=r->prox;
   }
   printf("Nao existe arvore.\n");
   return NULL;
}

// Adiciona um novo no na ABB
No *adiciona_no(No* arvore, int val){
   if(arvore == NULL)
      arvore=cria_no(val);
   else {
      if(arvore->elem > val) // Insere na esquerda
         arvore->esq = adiciona_no(arvore->esq, val);
      else if(arvore->elem < val) // Insere na direita
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
   p->prox = topo;
   topo = p;
   return topo;
}

// Desempilha os valores da pilha e libera a memoria alocada
int desempilhar(Pilha **topo){
   int tmp;
   Pilha *q=*topo;
   if(vazia(q)==1){
      fprintf(stderr, "Pilha vazia\n");
      exit(1);
   }
   tmp=q->num;
   *topo=(*topo)->prox;
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

// Realiza a uniao de duas ABB
No *uniao(Pilha **pilha1, Pilha **pilha2, No* arvore_resultante){
   int valor;
   while(*pilha1 != NULL){
      valor=desempilhar(pilha1);
      arvore_resultante = adiciona_no(arvore_resultante, valor);
   }
   while(*pilha2 != NULL){
      valor=desempilhar(pilha2);
      arvore_resultante = adiciona_no(arvore_resultante, valor);
   }
   return arvore_resultante;
}

// Realiza a interseccao de duas ABB
No *interseccao(Pilha **pilha1, Pilha **pilha2, No *arvore_resultante){
   int valor;
   while(*pilha1!=NULL && *pilha2 != NULL){ // As pilhas estao ordenadas na ordem do maior para o menor elemento, a partir do topo
      if((*pilha1)->num > (*pilha2)->num) desempilhar(pilha1);
      else if((*pilha1)->num < (*pilha2)->num) desempilhar(pilha2);
      else{
         valor=desempilhar(pilha1);
         desempilhar(pilha2);
         arvore_resultante = adiciona_no(arvore_resultante, valor);
      }
   }
   // Termina de desempilhar quando existem pilhas nao vazias
   while(*pilha1!=NULL) desempilhar(pilha1);
   while(*pilha2!=NULL) desempilhar(pilha2);
   return arvore_resultante;
}

BTLista *encontra_ultimo(BTLista *lista){
   BTLista *aux=lista;
   if(aux==NULL) return NULL;
   while(aux->prox!=NULL) aux=aux->prox;
   return aux;
}

// Libera todos os nos de uma ABB
void liberar_nos(No *arvore){
   if(arvore!=NULL){
      if(arvore->esq==NULL && arvore->dir==NULL)
         free(arvore);
      else{
         liberar_nos(arvore->esq);
         liberar_nos(arvore->dir);
         free(arvore);
      }
   }
}

// Libera todos os nos da lista ligada (floresta) que contem as arvores
void liberar_toda_memoria_alocada(BTLista **lista){
   BTLista *ant;
   while((*lista)!=NULL){
      ant=(*lista);
      (*lista)=(*lista)->prox;
      liberar_nos(ant->abb);
      free(ant);
   }
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
   BTLista *lista=NULL, *aux, *tmp, *nova_arvore;
   Pilha *pilha1=NULL, *pilha2=NULL;
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
            //printf("indice capturado: %d\n", indice);
            aux=procura_arvore(lista, indice);
            if(aux!=NULL){ // Soh calcula a altura de uma ABB existente
               altura_abb=altura_arvore(aux->abb);
               printf("Altura da arvore %d: %d.\n", indice, altura_abb);
            }
            break;
            
         case 4: // Calcula o numero de folhas de uma ABB existente
            scanf(" %d", &indice);
            aux=procura_arvore(lista, indice);
            if(aux!=NULL){
               folhas_abb=folhas_arvore(aux->abb);
               printf("Numero de folhas da arvore %d: %d.\n", indice, folhas_abb);
            }
            break;
            
         case 5: //Imprime a ABB (em notações prefixa, infixa e posfixa, respectivamente)
            scanf(" %d", &indice);
            aux=procura_arvore(lista, indice);
            // Em todos os casos, imprime somente quando a arvore existe e nao eh vazia
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
               if(string[2] == 'U' || string[2] == 'I'){ // Promove a uniao ou interseccao de duas ABB
                  indice_arv1=(int)(string[0]) - '0';
                  indice_arv2=(int)(string[1]) - '0';
                  aux=procura_arvore(lista, indice_arv1);
                  tmp=procura_arvore(lista, indice_arv2);
                  
                  if(aux!=NULL && tmp!=NULL){ // Arvores requisitadas existem
                     pilha1 = empilhando_infixa(aux->abb, pilha1);
                     pilha2 = empilhando_infixa(tmp->abb, pilha2);
                     lista=cria_arvore(lista);
                     nova_arvore=encontra_ultimo(lista);
                     
                     if(string[2] == 'U') // Uniao  
                        nova_arvore->abb = uniao(&pilha1, &pilha2, nova_arvore->abb);
                     else // Interseccao
                        nova_arvore->abb = interseccao(&pilha1, &pilha2, nova_arvore->abb);
                  }
               }
               break;
      }
   }
   liberar_toda_memoria_alocada(&lista);
   
   return 0;
}