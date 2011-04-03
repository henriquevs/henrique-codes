/*  UNICAMP - Universidade Estadual de Campinas
    MC102 - Algoritmos e Programacao de Computadores
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratório 07 - Agenda Telefonica 2 */
    
#include <stdio.h>
#include <string.h>

#define TAM 40

/* Criacao do registro contato */
typedef struct contato {
   char nome[TAM];
   int tel;
} contato;

/* Serao usadas comparacoes booleanas */
typedef enum {False, True} bool;

/* Funcao que separa o vetor que esta antes e depois do pivo - base para utilizacao do QUICKSORT */
int separa(contato agenda[], int p, int r){
   
   contato pivo;
   int i = p + 1;
   int j = r;
   contato troca;
   
   pivo = agenda[p];
   
   while (i <= j){
      if(strcmp(agenda[i].nome, pivo.nome) <= 0)
         i++;
      else
         if(strcmp(agenda[j].nome, pivo.nome) > 0)
            j--;
         else{
            troca = agenda[i];
            agenda[i] = agenda[j];
            agenda[j] = troca;
            i++;
            j--;
         }
   }
   
   troca = agenda[p];
   agenda[p] = agenda[j];
   agenda[j] = troca;
   
   return j; /* Posicao correta do pivo no vetor que esta sendo ordenado */
}

/* Funcao que ordena nomes usando QUICKSORT */
void ordenaNome(contato agenda[], int p, int r){
   int j;
   if(p < r){
      j = separa(agenda, p, r);
      ordenaNome(agenda, p, j - 1);
      ordenaNome(agenda, j + 1, r);
   }
}

/* Funcao que busca nomes atraves de busca binaria recursiva */
int buscaNome(contato agenda[], char nome[], int esq, int dir){
   if(esq > dir)
      return -1;
   else{   
      int meio = (esq + dir)/2;
      if(strcmp(agenda[meio].nome, nome) == 0)
         return meio;
      else{
         if(strcmp(agenda[meio].nome, nome) > 0)
            return buscaNome(agenda, nome, esq, meio - 1);
         else
            return buscaNome(agenda, nome, meio + 1, dir);
      }
   }
}

/* Função que busca telefones atraves de busca sequencial */
int buscaTelefone(contato agenda[], int telefone, int n_contatos){
   bool encontrado = False; /* Telefone nao encontrado */
   int i = 0;
   while (i < n_contatos && !encontrado){
      if(telefone == agenda[i].tel)
         encontrado = True; /* O telefone procurado esta na agenda */
      else
         i++;
   }    
   if (encontrado)
      return i;
   return -1;
}

/* Função que remove um contato da agenda */
void remover(contato agenda[], int posicao_contato, int n_contatos){
   int i;
   for(i = posicao_contato; i < n_contatos -1; i++)
      agenda[i] = agenda[i + 1];
}

/* Inicializacao do programa */
int main(){
   int n_contatos = 0; // Conta o numero de contatos ja inseridos
   int resp, telefone_lido, i;
   contato agenda[70];
   char parametro, inicial;
   char nome_lido[TAM];
   bool ordenado = False; /* Inicialmente a agenda não esta ordenada */
        
   do{
      parametro = getchar();
      switch(parametro){
         case('i'): /* Insere um novo contato na agenda */
            getchar();
            scanf("%d", &(agenda[n_contatos].tel));
            getchar();
            scanf("%[^\n]", agenda[n_contatos].nome);
            getchar();
            n_contatos++;
            ordenado = False;
            break;
            
         case('r'): /* Faz a remocao de um contato da agenda */
            if(n_contatos > 0){
               getchar();
               scanf("%d", &telefone_lido);
               getchar();
               
               resp = buscaTelefone(agenda, telefone_lido, n_contatos);
               if(resp == -1)
                  printf("Nao foi possivel remover: Contato inexistente!\n\n");
               else{
                  printf("Contato: %-40s %d\nFoi removido com sucesso!\n\n", agenda[resp].nome, agenda[resp].tel);
                  remover(agenda, resp, n_contatos);
                  n_contatos--;
               }
            }
            else
               printf("Nao foi possivel remover: Contato inexistente!\n\n");
               
            break;
         
         case('n'): /* Busca um nome na agenda */
            if(ordenado == False){
               ordenaNome(agenda, 0, n_contatos - 1);
               ordenado = True;
            }
            getchar();
            scanf("%[^\n]", nome_lido);
            getchar();
            resp = buscaNome(agenda, nome_lido, 0, n_contatos - 1);
                
            if(resp == -1)
               printf("Contato nao encontrado!\n\n");
            else
               printf("%-40s %d\n\n", agenda[resp].nome, agenda[resp].tel);
                
            break;
                
         case('t'): /* Busca um telefone na agenda */
            getchar();
            scanf("%d", &telefone_lido);
            getchar();
            resp = buscaTelefone(agenda, telefone_lido, n_contatos);
                
            if(resp == -1)
               printf("Contato nao encontrado!\n\n");
            else
               printf("%-40s %d\n\n", agenda[resp].nome, agenda[resp].tel);
                
            break;
                
         case('p'): /* Faz a impressao de todos os contatos em ordem alfabetica */
            if(ordenado == False){
               ordenaNome(agenda, 0, n_contatos - 1);
               ordenado = True;
            }
            if(n_contatos > 0){ /* Se nao existem contatos na agenda entao nao e necessario imprimir */
               inicial = agenda[0].nome[0];
               printf("----%c----\n", inicial);
               
               for(i = 0; i < n_contatos; i++){
                  if(agenda[i].nome[0] == inicial)
                     printf("%-40s %d\n", agenda[i].nome, agenda[i].tel);
                  else{
                     printf("----%c----\n", agenda[i].nome[0]);
                     inicial = agenda[i].nome[0];
                     printf("%-40s %d\n", agenda[i].nome, agenda[i].tel);
                  }
               }
               putchar('\n');
               }
            else
               printf("\n");
            break;
        }
   } while(parametro != 'f');
   
   system("pause");
    
   return 0;
}
