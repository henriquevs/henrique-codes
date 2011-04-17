/* lab04 - Campo minado */

#include <stdio.h>
#include <stdlib.h>

/* Estrutura do elemento da matriz */
typedef struct elemento{
   int visivel; /* Booleano que indica se o elemento esta ou nao visivel */
   char simbolo;
   int n_bombas; /* Numero de bombas ao redor do elemento */
} Elemento;

/* Teste de memória 1 */


/* Aloca a matriz dinamicamente */
Elemento **aloca_matriz(int n_linhas, int n_colunas){
   Elemento **aux=NULL;
   int i=0;
   
   aux=(Elemento**)malloc(n_linhas*sizeof(Elemento*));
   if(aux==NULL)
      printf("Erro de alocacao\n");
   else
      printf("Alocacao correta\n");
   // Testar se a memória foi alocada corretamente
   while(i<n_linhas){
      aux[i]=(Elemento*)malloc(n_colunas*sizeof(Elemento));
      if(aux==NULL)
         printf("Erro de alocacao: %d\n", i);
      else
         printf("Alocacao correta: %d\n", i);
      // Testar se a memória foi alocada corretamente
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
void capta(Elemento **matriz, int n_linhas, int n_colunas){
   int i, j;
   char simbolo;
   
   for(i=0; i<n_linhas; i++){
      for(j=0; j<n_colunas; j++){
         do simbolo=getchar(); /* Verifica caracter valido */
         while(simbolo!='#' && simbolo!='*');
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
   else return 0;
   
   if(matriz[i][j].n_bombas>0 && matriz[i][j].n_bombas<9) /* Caso base da recursao */
      return p;
   
   if(matriz[i][j].n_bombas==0){
      if(i+1<n_linhas)                   p=p+revelar(matriz, n_linhas, n_colunas, i+1, j); /* Chama a funcao recursivamente para o elemento debaixo */
      
      if(i-1>=0)                         p=p+revelar(matriz, n_linhas, n_colunas, i-1, j); /* Chama a funcao recursivamente para o elemento de cima */
      
      if(j+1<n_colunas)                  p=p+revelar(matriz, n_linhas, n_colunas, i, j+1); /* Chama a funcao recursivamente para o elemento da direita */
      
      if(j-1>=0)                         p=p+revelar(matriz, n_linhas, n_colunas, i, j-1); /* Chama a funcao recursivamente para o elemento da esquerda */
      
      if(i+1<n_linhas && j+1<n_colunas)  p=p+revelar(matriz, n_linhas, n_colunas, i+1, j+1); /* Chama a funcao recursivamente para o elemento debaixo e direita */
      
      if(i+1<n_linhas && j-1>=0)         p=p+revelar(matriz, n_linhas, n_colunas, i+1, j-1); /* Chama a funcao recursivamente para o elemento debaixo e esquerda */
      
      if(i-1>=0 && j+1<n_colunas)        p=p+revelar(matriz, n_linhas, n_colunas, i-1, j+1); /* Chama a funcao recursivamente para o elemento de cima e direita */
      
      if(i-1>=0 && j-1>=0)               p=p+revelar(matriz, n_linhas, n_colunas, i-1, j-1); /* Chama a funcao recursivamente para o elemento de cima e esquerda */
      
      return p;
   }
   printf("Erro na funcao revelar\n");
   exit(1);
}

/* Executa uma jogada */
int executar_jogada(Elemento **matriz, int n_linhas, int n_colunas, int i, int j){ /* Recebe as posicoes da jogada */
   int p;

   if(matriz[i][j].visivel == 1) return 0;
   
   if(matriz[i][j].simbolo=='*'){
      matriz[i][j].visivel = 1; /* Mostra elemento */
      return 0; /* Jogador perdeu */
   }
   if(matriz[i][j].n_bombas>0 && matriz[i][j].n_bombas<9){
      matriz[i][j].visivel = 1; /* Mostra elemento */
      return 1; /* Jogada concluida */
   }
   if(matriz[i][j].n_bombas==0){
      printf("teste executar jogada\n");
      p=revelar(matriz, n_linhas, n_colunas, i, j);
      return p; /* Retorna a quantidade de elementos revelados recursivamente */
   }
   printf("Erro na funcao executar_jogada\n");
   return -1;
}

/* Imprime toda a matriz */
void imprime_matriz_simbolos(Elemento **matriz, int linhas, int colunas){
   int i, j;
   
   putchar('\n');
   for(i=0; i<linhas; i++){
      for(j=0; j<colunas; j++)
         printf("%c", matriz[i][j].simbolo);
      putchar('\n');
   }
   putchar('\n');
}

/* Imprime toda a matriz */
void imprime_matriz(Elemento **matriz, int linhas, int colunas){
   int i, j;
   
   for(i=0; i<linhas; i++){
      for(j=0; j<colunas; j++)
         if(matriz[i][j].visivel==0) printf("#");
         else printf("%d", matriz[i][j].n_bombas);
      putchar('\n');
   }
}

/* Execucao */
int main(){
   Elemento **matriz;
   int n_linhas, n_colunas, jogada_i, jogada_j, tmp;
   int elementos_revelados=0, minas_encontradas=0, total_minas=6, jogadas_validas=0; /* Contadores */
   char resultado='i', /* Jogador não ganhou nem perdeu */
        aux;
   
   scanf("%d %d", &n_colunas, &n_linhas);
   printf("linhas: %d\ncolunas: %d\n", n_linhas, n_colunas);
   matriz=aloca_matriz(n_linhas, n_colunas);

   capta(matriz, n_linhas, n_colunas);
   contar_bombas_vizinhas(matriz, n_linhas, n_colunas);
   imprime_matriz_simbolos(matriz, n_linhas, n_colunas);

   aux=getchar();
   while(aux!=EOF){ /* Se entrarmos no loop, a jogada eh valida */
      ungetc(aux, stdin);

      scanf("%d %d", &jogada_i, &jogada_j);
      printf("Escaneou jogada: %d %d\n", jogada_i, jogada_j);
      tmp = executar_jogada(matriz, n_linhas, n_colunas, jogada_i-1, jogada_j-1);
      imprime_matriz(matriz, n_linhas, n_colunas);
      jogadas_validas++;
      elementos_revelados = elementos_revelados + tmp; /* Adiciona caracteres revelados na jogada */
      printf("Revelados: %d\n", elementos_revelados);
      
      if(tmp==0){
         resultado='p'; /* Jogador perdeu */
         break;
      }
      if(minas_encontradas==total_minas){
         resultado='v'; /* Jogador ganha */
         break;
      }
      do {
         aux=getchar();
      } while (aux=='\n');
   }
   return 0;
}
