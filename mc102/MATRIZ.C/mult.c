#include <stdio.h>

# define TAM 3

void imprimeMatriz(int mat[TAM][TAM]);

int main (){
    
    int matA[TAM][TAM], matB[TAM][TAM], matC[TAM][TAM];
    int i, j, k;
    
    // Lê a matriz A na ordem de preenchimento das linhas
    for(i = 0; i < TAM; i++){
          for(j = 0; j < TAM; j++){
                scanf("%3d", &matA[i][j]);
          }
    }
    
    // Imprime a matriz A
    for(i = 0; i < TAM; i++){
          for(j = 0; j < TAM; j++){
                printf("%3d", matA[i][j]);
          }
          printf("\n");
    }
    
    // Lê a matriz B na ordem de preenchimento das linhas
    for(i = 0; i < TAM; i++){
          for(j = 0; j < TAM; j++){
                scanf("%3d", &matB[i][j]);
          }
    }
    
    // Imprime a matriz B
    for(i = 0; i < TAM; i++){
          for(j = 0; j < TAM; j++){
                printf("%3d", matB[i][j]);
          }
          printf("\n");
    }
    
    // A matriz C equivale à matriz A multiplicada pela matriz B
    for(i = 0; i < TAM; i++){
          for(j = 0; j < TAM; j++){
          matC[i][j] = 0;
                for(k = 0; k < TAM; k++){
                      matC[i][j] += matA[i][k] * matB[k][j];
                }
          }
    }
    
    // Imprime a matriz C
    for(i = 0; i < TAM; i++){
          for(j = 0; j < TAM; j++){
                printf("%6d", matC[i][j]);
          }
          printf("\n");
    }
    
    system("pause");
    
    return 0;
}
