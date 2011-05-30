/* UNICAMP - Universidade Estadual de Campinas
   MC202 - Estruturas de Dados
   Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
   Laboratorio 06 - Filtro da Mediana */

#include <stdio.h>
#include <stdlib.h>

#define TAM 49

void verifica_memoria1(int **p){
   if(p==NULL){
      printf("Erro na alocação da matriz\n");
      exit(1);
   }
}

void verifica_memoria2(int *q){
   if(q==NULL){
      printf("Erro na alocação do elemento na matriz\n");
      exit(1);
   }
}

int **cria_matriz(int largura, int altura){
   int **mat=NULL;
   int i;
   mat=(int**)malloc(altura*sizeof(int*));
   verifica_memoria1(mat);
   for(i=0; i<altura; i++){
      mat[i]=(int*)malloc(largura*sizeof(int));
      verifica_memoria2(mat[i]);
   }
   return mat;
}

void imprime_matriz(int **matriz, int largura, int altura){
   int i, j;
   for(i=0; i<altura; i++){
      for(j=0; j<largura; j++){
         if(j<largura-1)
            printf("%d ", matriz[i][j]);
         else if(j==largura-1)
            printf("%d\n", matriz[i][j]);
      }
   }
}

// Ordenacao do vetor atraves do algoritmo "Insertion Sort"
void ordena_vetor(int vetor[], int tamanho){
   int i, j;
   int aux;
   for(i = 1; i < tamanho; i++){
      aux = vetor[i];
      for(j = i - 1; (j >= 0) && (aux < vetor[j]); j--){
         vetor[j + 1] = vetor[j];
      }
      vetor[j + 1] = aux;
   }
}

// Aplica o filtro da mediana dentro dos limites da matriz
int mascara(int **matriz, int largura, int altura, int pos_x, int pos_y){
   int v[TAM];
   int i, j, k=0, val;
   for(i=pos_y-3; i<=pos_y+3; i++){
      if(i>=0 && i<altura){
         for(j=pos_x-3; j<=pos_x+3; j++){
            if(j>=0 && j<largura){
               v[k]=matriz[i][j]; // Guarda os valores medianos
               k++;
            }
         }
      }
   }
   
   ordena_vetor(v, k);
   
   if(k%2==0) // vetor com numero par de elementos
      val=(v[(k/2)-1]+v[(k/2)])/2;
   else
      val=v[k/2]; // vetor com numero impar de elementos
   
   return val;
}

// Execucao
int main(){
   char tipo[2]; // Tipo da imagem
   int largura, altura, val_maximo, i, j;
   char tmp;
   int **matriz_1=NULL, **matriz_2=NULL;
   
   tmp=getchar();
   tipo[0]=tmp;

   tmp=getchar();
   tipo[1]=tmp;
   
   tmp=getchar();
   
   tmp=getchar();
   while(tmp=='#'){ // Ignora os comentarios que porventura existam
      while(tmp!='\n')
         tmp=getchar();
      tmp=getchar();
   }
   ungetc(tmp, stdin);
   
   scanf("%d %d", &largura, &altura); // Dimensoes da matriz
   
   scanf("%d", &val_maximo); // Escala de cor
   
   matriz_1=cria_matriz(largura, altura); // Matriz de entrada
   matriz_2=cria_matriz(largura, altura); // Matriz de saida
   
   // Le a matriz da entrada
   for(i=0; i<altura; i++){
      for(j=0; j<largura; j++)
         scanf("%d", &matriz_1[i][j]);
   }
   
   // Aplica o filtro da mediana na matriz de entrada e guarda os valores na matriz de saida
   for(i=0; i<altura; i++)
      for(j=0; j<largura; j++)
         matriz_2[i][j]=mascara(matriz_1, largura, altura, j, i);

   printf("%c%c\n", tipo[0], tipo[1]);
   printf("# MC202D: LAB06 - FILTRO DA MEDIANA\n");
   printf("%d %d\n", largura, altura);
   printf("%d\n", val_maximo);
   imprime_matriz(matriz_2, largura, altura); // Imprime a matriz de saida
   
   return 0;
}