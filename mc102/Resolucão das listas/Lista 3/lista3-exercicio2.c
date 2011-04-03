/* Lista de exercícios 3
   Exercício 2 - Agenda telefônica que permite ao usuário o cadastramento e a consulta dos dados armazenados */

#include <stdio.h>
#include <stdlib.h>

int main(){
    int posicao_agenda, i;
    int agenda[10]; //Maximo de 10 contatos
    int n_contatos = 0; // Conta o numero de contatos armazenados
    char parametro;

    /* Preenche com zero cada posicao da agenda para, futuramente, verificarmos se ela está com contatos */
    for(i=0; i<10; i++){
        agenda[i] = 0;
    }

    do{
        printf("Digite a opcao desejada:\n");
        printf("c: Cadastrar um numero\n");
        printf("l: Listar os numeros salvos\n");
        printf("m: Mostrar um numero salvo\n");
        printf("s: Sair\n\n");

        parametro = getchar();

        switch(parametro){
        
        case 'c': 
            printf("Digite a posicao da agenda (de 1 a 10):\n");
            scanf("%d", &posicao_agenda);
            printf("Telefone:\n");
            if(agenda[posicao_agenda - 1] == 0){
                scanf("%d", &agenda[posicao_agenda - 1]);
                n_contatos++;
            }
            else
                scanf("%d", &agenda[posicao_agenda - 1]);
            break;

        case 'l':
            if(n_contatos>0){ // Confere se existem telefones salvos na agenda
                i=0;
                while(i<10){
                    if(agenda[i] != 0)
                        printf("%10d\n\n", agenda[i]);
                    i++;
                }
            }
            else
                printf("Nao existem contatos na agenda\n\n");
            break;

        case 'm':
            printf("Entre com um indice (de 1 a 10)\n");
            scanf("%10d", &posicao_agenda);
            
            if(agenda[posicao_agenda - 1] == 0)
                printf("Nao existe contato nesta posicao\n\n");
            else
                printf("%d\n\n", agenda[posicao_agenda - 1]);
            break;
        }
    }
    while(parametro != 's');

    system("pause");

    return 0;
}
