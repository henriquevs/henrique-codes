/* Lista de exercícios 4
   Funções
   Exercício 3 - Programa que calcula a soma de dois vetores de mesmo tamanho.
   O resultado é guardado em uma terceira matriz */

#include <stdio.h>

void somaMatrizes(int matA[][], int matB[][], int matResultado[dim1][dim2], int dim1, int dim2){
    int i, j;
    
    for(i=0; i<dim1; i++){
        for(j=0; j<dim2; j++){
            matResultado[i][j] = matA[i][j] + matB[i][j];
        }
    }
}
