#include <stdio.h>

# define TAM 3

void imprimeMatriz(int mat[TAM][TAM]);

int main(){
  
  int matA[TAM][TAM],matC[TAM][TAM],matB[TAM][TAM];
  int i,j,k;

  /*le a matriz a*/
  for(i = 0; i < TAM; i++)
    for(j = 0; j < TAM; j++)
      scanf("%3d",&matA[i][j]);
  
    /*imprime a matriz a*/
  for(i = 0; i < TAM; i++){
    for(j = 0; j < TAM; j++){
      printf("%3d",matA[i][j]);
    }
    printf("\n");
  }
  
  /*le a matriz b*/
  for(i = 0; i < TAM; i++)
    for(j = 0; j < TAM; j++)
      scanf("%3d",&matB[i][j]);
  
    /*imprime a matriz b*/
  for(i = 0; i < TAM; i++){
    for(j = 0; j < TAM; j++){
      printf("%3d",matB[i][j]);
    }
    printf("\n");
  }
  
  /*multiplica matriz a vezes a matriz b e guarda na matriz c*/
  for(i = 0; i < TAM; i++)
    for(j = 0; j < TAM; j++){
      matC[i][j] = 0;
      for(k = 0; k <TAM; k++)
	matC[i][j] += matA[i][k] * matB[k][j];
	}
  
  /*imprime a matriz c*/
  for(i = 0; i < TAM; i++){
    for(j = 0; j < TAM; j++){
      printf("%3d ",matC[i][j]);
    }
    printf("\n");
  }
  
  system("pause");
  
  return 0;
}
