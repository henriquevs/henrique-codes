/* Lista de exercícios 4
   Funções
   Exercício 1 - Programa que multiplica um valor inteiro v por uma constante */

#include <stdio.h>
#include <stdlib.h> 

// Passagem de parametros por referencia
int multiplica(int *v, int constante){
    return (*v)*constante;
}

int main(){
    int v, constante, resultado;

    printf("Valor de v:\n");
    scanf("%d", &v);
    printf("Valor da constante:\n");
    scanf("%d", &constante);

    resultado = multiplica(&v, constante);

    printf("O resultado eh: %d\n\n", resultado);

    system("pause");

    return 0;
}
