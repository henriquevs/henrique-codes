/* Lista de exercícios  4
   Vetores e Matrizes
   Exercício 1 - Dado a inicial e a inicial do nome de cinco alunos, o programa imprime o e-mail da DAC dos mesmos */

#include <stdio.h>
#include <stdlib.h>

int main (){
    int registro[5];
    char inicial[5];
    int i;

    printf("Coloque 5 RAs:\n");
    for(i=0; i<5; i++){
        scanf("%d", &registro[i]);
    }

    printf("Coloque 5 iniciais:\n");
    for(i=0; i<5; i++){
        scanf("%c", &inicial[i]);
    }

    for(i=0; i<5; i++){
        printf("%c%06d@dac.unicamp.br\n", inicial[i], registro[i]);
    }

    system("pause");

    return 0;
}
