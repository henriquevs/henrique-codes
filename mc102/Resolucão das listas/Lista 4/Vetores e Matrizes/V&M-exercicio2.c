/* Lista de exercíos 4
   Vetores e Matrizes
   Exercício 2 - Programa que executa a multiplicação de duas matrizes quaisquer,
   lembrando que as dimensões das matrizes tem de ser compatíveis para ocorrer a operação */

#include <stdio.h>
#include <stdlib.h>

int main (){
    int linhasA, colunasA, linhasB, colunasB, i, j, k;
    int matA[linhasA][colunasA], matB[linhasB][colunasB], matC[linhasA][colunasB];

    printf("Numeros de linhas e de colunas da matriz A:\n");
    scanf("%d %d", &linhasA, &colunasA);

    printf("Numeros de linhas e de colunas da matriz B:\n");
    scanf("%d %d", &linhasB, &colunasB);

    if(colunasA == linhasB){

        /* Lê a matriz A */
        for(i=0; i<linhasA; i++){
            for(j=0; j<colunasA; j++){
                scanf("%d", &matA[i][j]);
            }
        }
       
        /* Imprime a matriz A */
        for(i=0; i<linhasA; i++){
            for(j=0; j<colunasA; j++){
                printf("%4d", matA[i][j]);
            }
            printf("\n");
        }
       
        /* Lê a matriz B */
        for(i=0; i<linhasB; i++){
            for(j=0; j<colunasB; j++){
                scanf("%d", matB[i][j]);
            }
        }
 
        /* Imprime a matriz B */
        for(i=0; i<linhasB; i++){
            for(j=0; j<colunasB; j++){
                printf("%4d", matB[i][j]);
            }
            printf("\n");
        }

        /* A matriz C é o resultado da multiplicação da matriz A pela matriz B */
        for(i=0; i<linhasA; i++){
            for(j=0; j<colunasB; j++){
                matC[i][j] = 0;
                for(k=0; k<colunasA; k++){
                    matC[i][j] += matA[i][k] * matB[k][j];
                }
            }
        }

        /* Imprime a matriz C */
        for(i=0; i<linhasA; i++){
            for(j=0; j<colunasB; j++){
                printf("%4d", matC[i][j]);
            }
            printf("\n");
        }

    }
    
    else
    printf("Nao eh possivel efetuar a multiplicacao");

    system("pause");

    return 0;
}
