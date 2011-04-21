/*  UNICAMP - Universidade Estadual de Campinas
    MC202 - Estruturas de Dados
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratorio 04 - Campo Minado  */

#include <stdio.h>
#include <stdlib.h>

/* Estrutura de cada elemento da matriz */
typedef struct elemento{
   int visivel; /* Booleano que indica se o elemento esta(1) ou nao(0) visivel */
   char simbolo;
   int n_bombas; /* Numero de bombas ao redor do elemento */
} Elemento;

/* Teste de memória para a alocacao das linhas */
void teste_memoria1(Elemento **matriz){
   if(matriz==NULL){
      printf("Memoria insuficiente\n");
      exit(1);
   }
}

/* Teste de memória para a alocacao das colunas */
void teste_memoria2(Elemento *matriz){
   if(matriz==NULL){
      printf("Memoria insuficiente\n");
      exit(1);
   }
}

/* Aloca a matriz dinamicamente */
Elemento **aloca_matriz(int n_linhas, int n_colunas){
   Elemento **aux=NULL;
   int i=0;
   
   aux=(Elemento**)malloc(n_linhas*sizeof(Elemento*));
   teste_memoria1(aux);
   while(i<n_linhas){
      aux[i]=(Elemento*)malloc(n_colunas*sizeof(Elemento));
      teste_memoria2(aux[i]);
      i++;
   }
   return aux;

}

/* Libera toda memoria alocada */
void libera_matriz(Elemento **matriz, int n_linhas){
   int i=0;
   for(i=0; i<n_linhas; i++)
      free(matriz[i]);
   free(matriz);
}

/* Conta o numero de bombas ao redor de cada elemento da matriz e armazena o dado no elemento */
void contar_bombas_vizinhas(Elemento **matriz, int n_linhas, int n_colunas){
   int i, j;

   for(i=0; i<n_linhas; i++){
      for(j=0; j<n_colunas; j++){
         if((i+1)<n_linhas && matriz[i+1][j].simbolo=='*')  matriz[i][j].n_bombas++; /* Checando abaixo */
         
         if((j+1)<n_colunas && matriz[i][j+1].simbolo=='*')  matriz[i][j].n_bombas++; /* Checando direita */
         
         if((i-1)>=0 && matriz[i-1][j].simbolo=='*')  matriz[i][j].n_bombas++; /* Checando acima */
         
         if((j-1)>=0 && matriz[i][j-1].simbolo=='*')  matriz[i][j].n_bombas++; /* Checando esquerda */
         
         if((i+1)<n_linhas && (j+1)<n_colunas && matriz[i+1][j+1].simbolo=='*')  matriz[i][j].n_bombas++; /* Checando abaixo e direita */
         
         if((i+1)<n_linhas && (j-1)>=0 && matriz[i+1][j-1].simbolo=='*')  matriz[i][j].n_bombas++; /* Checando abaixo e esquerda */
         
         if((i-1)>=0 && (j+1)<n_colunas && matriz[i-1][j+1].simbolo=='*')  matriz[i][j].n_bombas++; /* Checando acima e direita */
         
         if((i-1)>=0 && (j-1)>=0 && matriz[i-1][j-1].simbolo=='*')  matriz[i][j].n_bombas++; /* Checando acima e esquerda */
      }
   }
}

/* Capta os elementos da matriz passados na entrada */
void capta(Elemento **matriz, int n_linhas, int n_colunas, int *minas){
   int i, j;
   char simbolo;
   
   for(i=0; i<n_linhas; i++){
      for(j=0; j<n_colunas; j++){
         do simbolo=getchar(); /* Verifica caracter valido */
         while(simbolo!='#' && simbolo!='*'); /* Avanca o cursor */
         if(simbolo=='*') (*minas)+=1; /* Conta o total de minas do jogo */
         matriz[i][j].simbolo = simbolo;
         matriz[i][j].visivel = 0;
         matriz[i][j].n_bombas = 0;
      }
   }
}

/* Retorna o numero de elementos revelados */
int revelar(Elemento **matriz, int n_linhas, int n_colunas, int i, int j){ /* Recebe as posicoes do elemento */
   int p=1; /* Quantidade de elementos revelados; Elemento atual eh visivel */
   
   if(matriz[i][j].visivel == 0) matriz[i][j].visivel = 1; /* Mostra elemento */
   else return 0; /* Elemento já foi revelado */
   
   if(matriz[i][j].n_bombas>0 && matriz[i][j].n_bombas<9) /* Caso base da recursao */
      return p;
   
   if(matriz[i][j].n_bombas==0){
      if(i+1<n_linhas) p=p+revelar(matriz, n_linhas, n_colunas, i+1, j); /* Chama a funcao recursivamente para o elemento debaixo */
      
      if(i-1>=0) p=p+revelar(matriz, n_linhas, n_colunas, i-1, j); /* Chama a funcao recursivamente para o elemento de cima */
      
      if(j+1<n_colunas) p=p+revelar(matriz, n_linhas, n_colunas, i, j+1); /* Chama a funcao recursivamente para o elemento da direita */
      
      if(j-1>=0) p=p+revelar(matriz, n_linhas, n_colunas, i, j-1); /* Chama a funcao recursivamente para o elemento da esquerda */
      
      if(i+1<n_linhas && j+1<n_colunas) p=p+revelar(matriz, n_linhas, n_colunas, i+1, j+1); /* Chama a funcao recursivamente para o elemento debaixo e direita */
      
      if(i+1<n_linhas && j-1>=0) p=p+revelar(matriz, n_linhas, n_colunas, i+1, j-1); /* Chama a funcao recursivamente para o elemento debaixo e esquerda */
      
      if(i-1>=0 && j+1<n_colunas) p=p+revelar(matriz, n_linhas, n_colunas, i-1, j+1); /* Chama a funcao recursivamente para o elemento de cima e direita */
      
      if(i-1>=0 && j-1>=0) p=p+revelar(matriz, n_linhas, n_colunas, i-1, j-1); /* Chama a funcao recursivamente para o elemento de cima e esquerda */
      
      return p;
   }
   printf("Erro na funcao revelar\n");
   exit(1);
}

/* Executa uma jogada */
int executar_jogada(Elemento **matriz, int n_linhas, int n_colunas, int i, int j){ /* Recebe as posicoes da jogada */
   int p;

   if(matriz[i][j].visivel == 1) return -1; /* So executa a jogada se o elemento nao foi revelado */
   
   if(matriz[i][j].simbolo=='*'){ /* Jogador perdeu */
      matriz[i][j].visivel = 1; /* Mostra o elemento */
      return 0;
   }
   
   if(matriz[i][j].n_bombas>0 && matriz[i][j].n_bombas<9){ /* Existe(m) bomba(s) ao redor do elemento */
      matriz[i][j].visivel = 1; /* Mostra elemento */
      return 1; /* Jogada concluida */
   }
   
   if(matriz[i][j].n_bombas==0){ /* Verifica o numero de bombas ao redor dos vizinhos */
      p=revelar(matriz, n_linhas, n_colunas, i, j);
      return p; /* Retorna a quantidade de elementos revelados recursivamente */
   }
   
   printf("Erro na funcao executar_jogada\n");
   return -1;
}

/* Imprime toda a matriz resultante */
void imprime_matriz(Elemento **matriz, int linhas, int colunas, char resultado){
   int i, j;
   
   if(resultado=='p') /* Jogador perdeu */
      for(i=0; i<linhas; i++){
         for(j=0; j<colunas; j++)
            if(matriz[i][j].simbolo=='*') printf("%c", matriz[i][j].simbolo); /* Mostra todas as bombas */
            else if(matriz[i][j].visivel==0) printf("#"); /* Elementos que nao foram revelados continuam ocultos */
            else printf("%d", matriz[i][j].n_bombas);
         putchar('\n');
      }
   else
      for(i=0; i<linhas; i++){
         for(j=0; j<colunas; j++)
            if(matriz[i][j].visivel==0) printf("#"); /* Imprime elementos que nao foram revelados */
            else printf("%d", matriz[i][j].n_bombas);
         putchar('\n');
      }
}

/* Execucao */
int main(){
   Elemento **matriz; /* Matriz do jogo */
   int n_linhas, n_colunas, jogada_i, jogada_j, tmp;
   int elementos_revelados=0, total_minas=0, jogadas_validas=0;
   char resultado='i', /* Jogador não ganhou nem perdeu */
        aux;
   
   scanf("%d %d", &n_colunas, &n_linhas);
   
   matriz=aloca_matriz(n_linhas, n_colunas);

   capta(matriz, n_linhas, n_colunas, &total_minas); /* Capta a matriz passada na entrada e conta o total de minas */

   contar_bombas_vizinhas(matriz, n_linhas, n_colunas);

   aux=getchar();
   while(aux!=EOF){ /* Lemos as jogadas validas ate o fim do arquivo */
      ungetc(aux, stdin);

      scanf("%d %d", &jogada_i, &jogada_j);
      tmp = executar_jogada(matriz, n_linhas, n_colunas, jogada_i-1, jogada_j-1);
      if(tmp != -1){ /* Nao executa jogadas iguais */
         jogadas_validas++;
         elementos_revelados = elementos_revelados + tmp; /* Adiciona caracteres revelados na jogada */
         
         if(tmp==0){ /* Jogador perdeu */
            resultado='p';
            elementos_revelados+=1;
            break;
         }
         
         if(elementos_revelados+total_minas == n_linhas*n_colunas){ /* "n_linhas*n_colunas" = total de elementos */
            resultado='v'; /* Jogador ganhou */
            break;
         }
      }
      do{
         aux=getchar();
      } while (aux=='\n');
      
   }
   printf("Minas: %d\n", total_minas);
   printf("Jogadas: %d\n", jogadas_validas);
   printf("Revelados: %d\n", elementos_revelados);
   if(resultado=='v') printf("Resultado: =)\n");
   if(resultado=='p') printf("Resultado: =(\n");
   if(resultado=='i') printf("Resultado: ?\n");
   
   imprime_matriz(matriz, n_linhas, n_colunas, resultado);
   
   libera_matriz(matriz, n_linhas); /* Libera toda memoria alocada */
   
   return 0;
}