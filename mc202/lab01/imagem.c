/*  UNICAMP - Universidade Estadual de Campinas
    MC202 - Estruturas de Dados
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratorio 01 - Contagem de Componentes Conexas */
    
#include <stdio.h>
#include <stdlib.h>

/* Funcao que sai do programa caso a memoria para alocacao dinamica nao seja suficiente */
void memoria_insuficiente(){
   printf("Memoria insuficiente\n");
   exit(0);
}

/* Funcao que anda nas componentes conexas por vizinhanca 4 */         
void vizinhanca_4(char*** mat, int linhas, int colunas, int i, int j) {
   /* Usa uma das duas matrizes criadas para andar nas componentes */
   if((i+1)<linhas && mat[0][i+1][j]=='1'){ /* checando abaixo */
      mat[0][i+1][j] = '0';
      vizinhanca_4(mat, linhas, colunas, i+1, j);
   }
   
   if((j+1)<colunas && mat[0][i][j+1]=='1'){ /* checando direita */
      mat[0][i][j+1] = '0';
      vizinhanca_4(mat, linhas, colunas, i, j+1);
   }
   
   if((i-1)>=0 && mat[0][i-1][j]=='1'){ /* checando acima */
      mat[0][i-1][j] = '0';
      vizinhanca_4(mat, linhas, colunas, i-1, j);
   }
   
   if((j-1)>=0 && mat[0][i][j-1]=='1'){ /* checando esquerda */
      mat[0][i][j-1] = '0';
      vizinhanca_4(mat, linhas, colunas, i, j-1);
   }
}

/* Funcao que anda nas componentes conexas por vizinhanca 8 */
void vizinhanca_8(char*** mat, int linhas, int colunas, int i, int j){
   /* Usa a outra das duas matrizes criadas para andar nas componentes */
   if((i+1)<linhas && mat[1][i+1][j]=='1'){ /* checando abaixo */
      mat[1][i+1][j] = '0';
      vizinhanca_8(mat, linhas, colunas, i+1, j);
   }
   
   if((j+1)<colunas && mat[1][i][j+1]=='1'){ /* checando direita */
      mat[1][i][j+1] = '0';
      vizinhanca_8(mat, linhas, colunas, i, j+1);
   }
   
   if((i-1)>=0 && mat[1][i-1][j]=='1'){ /* checando acima */
      mat[1][i-1][j] = '0';
      vizinhanca_8(mat, linhas, colunas, i-1, j);
   }
   
   if((j-1)>=0 && mat[1][i][j-1]=='1'){ /* checando esquerda */
      mat[1][i][j-1] = '0';
      vizinhanca_8(mat, linhas, colunas, i, j-1);
   }
      
   if((i+1)<linhas && (j+1)<colunas && mat[1][i+1][j+1]=='1'){ /* checando abaixo e direita */
      mat[1][i+1][j+1] = '0';
      vizinhanca_8(mat, linhas, colunas, i+1, j+1);
   }
   
   if((i+1)<linhas && (j-1)>=0 && mat[1][i+1][j-1]=='1'){ /* checando abaixo e esquerda */
      mat[1][i+1][j-1] = '0';
      vizinhanca_8(mat, linhas, colunas, i+1, j-1);
   }
   
   if((i-1)>=0 && (j+1)<colunas && mat[1][i-1][j+1]=='1'){ /* checando acima e direita */
      mat[1][i-1][j+1] = '0';
      vizinhanca_8(mat, linhas, colunas, i-1, j+1);
   }
   
   if((i-1)>=0 && (j-1)>=0 && mat[1][i-1][j-1]=='1'){ /* checando acima e esquerda */
      mat[1][i-1][j-1] = '0';
      vizinhanca_8(mat, linhas, colunas, i-1, j-1);
   }
   
}

int main(){
   int linhas, colunas, i, j;
   int contador_viz_4 = 0;
   int contador_viz_8 = 0;
   char*** mat; /* A imagem (matriz) eh representada por um vetor de ponteiros; neste caso teremos duas matrizes "dispostas no espaco" */
   char tmp;
   
   /* Avanca o cursor ate que cheguemos ao inicio do codigo */
   tmp = getchar();
   
   while(tmp != '#'){
      while(tmp != '\n')
         tmp = getchar();
      tmp = getchar();
   }
   
   while(tmp == '#'){
      while(tmp != '\n')
         tmp = getchar();
      tmp = getchar();
   }
   
   ungetc(tmp, stdin); /* Retrocede o cursor de uma unidade */
   
   /* Captura as dimensoes da matriz */
   scanf("%d %d", &colunas, &linhas);
   
   /* Aloca a matriz (imagem) dinamicamente */
   mat = (char***)malloc(2*sizeof(char**));
   
   if(mat == NULL) /* Verifica se não houve erro na alocacao */
      memoria_insuficiente();
   
   for(i=0; i<2; i++){
      mat[i] = (char**)malloc(linhas*sizeof(char*));
      
      if(mat[i] == NULL) /* Verifica se não houve erro na alocacao */
      memoria_insuficiente();
      
      for(j=0; j<linhas; j++){
         mat[i][j] = (char*)malloc(colunas*sizeof(char));
      
         if(mat[i][j] == NULL) /* Verifica se não houve erro na alocacao */
         memoria_insuficiente();
      
      }
   }

   /* Le a matriz (imagem) passada na entrada e armazena os dados*/
   for(i=0; i<linhas; i++){
      for(j=0; j<colunas; j++){
         scanf("%c", &mat[0][i][j]);
         if(mat[0][i][j]=='\n')
            scanf("%c", &mat[0][i][j]);
         mat[1][i][j] = mat[0][i][j]; /* Cria uma copia da matriz (imagem) para a contagem por vizinhanca 8 */
      }
   }
   
   /* Conta o numero de componentes conexas por vizinhanca 4 */
   for(i=0; i<linhas; i++){
      for(j=0; j<colunas; j++){
         if(mat[0][i][j]=='1'){
            contador_viz_4++;
            vizinhanca_4(mat, linhas, colunas, i, j);
         }
      }
   }
   
   /* Conta o numero de componentes conexas por vizinhanca 8 */
   for(i=0; i<linhas; i++){
      for(j=0; j<colunas; j++){
         if(mat[1][i][j]=='1'){
            contador_viz_8++;
            vizinhanca_8(mat, linhas, colunas, i, j);
         }
      }
   }

   /* Libera a memoria alocada */
   for(i=0; i<2; i++){
      for(j=0; j<linhas; j++)
         free(mat[i][j]);
      free(mat[i]);
   }
   free(mat);
   
   printf("Vizinhanca-4: %d\n", contador_viz_4);
   printf("Vizinhanca-8: %d", contador_viz_8);
   
   return 0;

}
