/* Programa que conta o numero de linhas de um arquivo */
#include <stdio.h>

int main(void){
    int c;
    int n_linhas = 0; /* Contador do numero de linhas */
    FILE* fp;
    
    fp = fopen("teste.txt", "rt");
    
    if(fp == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        system("pause");
        return 1;
    }
    
    /* Le caractere a caractere */
    while((c = fgetc(fp)) != EOF){
        if(c == '\n')
            n_linhas++;
    }
    
    /* Fecha arquivo */
    fclose(fp);
    
    /* Exibe resultado na tela */
    printf("Numero de linhas = %d", n_linhas);
    
    system("pause");
    
    return 0;
}
