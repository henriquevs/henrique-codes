/*  UNICAMP - Universidade Estadual de Campinas
    MC102 - Algoritmos e Programacao de Computadores
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratorio 08 - Agenda Telefonica 3 */
    
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 40

/* Definicao do registro Agenda */
typedef struct contato{
   int tel;
   char nome[TAM];
   struct contato *next;
} Agenda;

/* Funcao que cria um no */
Agenda criaNo(int tel, char nome[], Agenda *next){
   Agenda *lista; /* "lista" eh um apontador para minha agenda telefonica */
   lista = (Agenda*)malloc(sizeof(Agenda));
   strcpy(lista->nome,nome);
   lista->tel = tel;
   lista->next = next;
   return *lista;
}

/* Funcao que insere um contato de maneira ordenada */
void insereOrdenado(int tel_lido, char nome_lido[], Agenda **lista){
   Agenda* aux, *ant;
   
   if((*lista) == NULL){
      *lista = criaNo(tel_lido, nome_lido[], NULL);
      return;
   }
   else{
      aux = *lista;
      if(strcmp(nome_lido,(*aux).nome) < 0){
         aux = criaNo(tel_lido, nome_lido[], aux);
         *lista = aux;
      }
      else{
         while(aux != NULL && strcmp(nome_lido,(*aux).nome) > 0){
            ant = aux;
            aux = aux->next;
         }
         ant->next = criaNo(tel_lido, nome_lido, aux);
      }
   }
}

/* Funcao que busca um contato na agenda a partir de um nome passado na entrada */
Agenda busca(char nome_lido[], Agenda *lista){
   while(lista!=NULL && strcmp(nome_lido,lista->nome) == 0)
      lista = lista->next;
   if(lista!=NULL && strcmp(nome_lido,lista->nome) == 0)
      return lista;
   else
      return NULL;
}

/* Funcao que remove um contato */
Agenda removeNo(char nome_lido[], Agenda**lista){
   Agenda* aux;
   while(*lista!=NULL && strcmp(nome_lido,(*lista)->nome) >0)
      lista = &((*lista)->next);
   if(*lista!=NULL && strcmp(nome_lido,(*lista)->nome) == 0){
      aux = *lista;
      *lista = (*lista)->next;
      return aux;
   }
   else
      return NULL;
}

/* Funcao que libera o espaço alocado na memoria */
void libera(Agenda*lista){
   Agenda* aux;
   while(lista!=NULL){
      aux = lista;
      lista = lista->next;
      free(aux);
   }
}

/* Funcao que imprime os contatos da agenda em ordem alfabetica */
void imprime(Agenda*lista){
   char inicial;
   inicial = lista->nome[0];
   printf("----%c----\n", inicial);
   while(lista!=NULL){
      if(lista->nome[0] == inicial){
         printf("%-40s %d\n", lista->nome, lista->tel);
         lista = lista->next;
      }
      else{
         printf("----%c----\n", lista->nome, lista->tel);
         inicial = lista->nome[0];
         printf("%-40s %d\n", lista->nome, lista->tel);
         lista = lista->next;
      }
   }
}

/* Inicializacao do programa */
int main(){
   Agenda *lista, resp;
   lista = NULL;
   int tel_lido;
   char parametro;
   char nome_lido[TAM];
   
   do{
      parametro = getchar();
      switch(parametro){
         case('i'): /* Insere um novo contato na agenda */
            getchar();
            scanf("%d", &tel_lido));
            getchar();
            scanf("%[^\n]", nome_lido);
            getchar();
            insereOrdenado(tel_lido, nome_lido, &lista);                        
            break;
            
         case('r'): /* Faz a remocao de um contato da agenda */
            getchar();
            scanf("%[^\n]", nome_lido[]);
            getchar();
            removeNo(nome_lido[], *lista);
            break;
         
         case('n'): /* Busca um nome na agenda */
            getchar();
            scanf("%[^\n]", nome_lido);
            getchar();
            resp = busca(nome_lido, lista);
                
            if(resp == NULL)
               printf("Contato nao encontrado!\n\n");
            else
               printf("%-40s %d\n\n", resp->nome, resp->tel);
                
            break;
                
         case('p'): /* Faz a impressao de todos os contatos em ordem alfabetica */
            imprime(&lista);
            break;
      }

   } while(parametro != 'f');
   
   libera(&lista);
    
   return 0;
}
