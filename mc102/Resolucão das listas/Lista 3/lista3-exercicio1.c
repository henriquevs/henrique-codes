/* Lista de exercícios 3
   Exercício 1 - Programa que cadastra as notas de n alunos de uma disciplina
   e retorna os alunos que obtiveram a maior e a menor nota */

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 100 // O vetor nota guardara a nota de no maximo 100 alunos

int main(){

    int n, i, j, indice_maior, indice_menor;
    float nota[TAMANHO];
    float maior, menor;

    printf("Numero de alunos:\n");
    scanf("%d", &n);

    printf("Entre com as notas\n");
    for(i=0; i<n; i++){
        scanf("%f", &nota[i]);
    }

    /* Encontra a maior nota */
    maior = nota[0];
    indice_maior = 1;
    for(j=1; j<n; j++){
        if(maior < nota[j]){
            maior = nota[j];
            indice_maior = j + 1;     
        }
    }

    /* Encontra a menor nota */
    menor = nota[0];
    indice_menor = 1;
    for(j=1; j<n; j++){
        if(menor > nota[j]){
            menor = nota[j];
            indice_menor = j + 1;
        }
    }

    /* Imprime as posicoes e as notas dos alunos que obtiveram a maior e a menor nota, respectivamente */
    printf("O aluno numero %d teve a maior nota (%2.2f) e o aluno %d teve a menor nota (%2.2f)\n\n", indice_maior, maior, indice_menor, menor);

    system ("pause");

    return 0;
}
