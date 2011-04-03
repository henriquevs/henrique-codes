/* Lista de exercícios 4
   Funções
   Exercício 6 - Programa que recebe uma cadeia de strings e as retornam invertidas */

#include <stdio.h>

#define TAM 150 // Quantidade maxima de caracteres digitados

/* Função que inverte os caracteres digitados na entrada */
void troca(char vetor[], char trocado[TAM], int n_letras){
     int i;
     int aux=0;
     for(i=n_letras-1; i>=0; i--){
         trocado[aux]=vetor[i];
         aux++;
     }
}

int main(){
     char vetor[TAM], trocado[TAM];
     int n_letras=0, encontrado=0;
     int j;
     
     printf("Digite:\n");
     for(j=0; (j<TAM) && (!encontrado); j++){
         scanf("%c", &vetor[j]);
         if(vetor[j]=='\n')
             encontrado=1;
         else
             n_letras++;
     }
     printf("\n");
     
     // A função inverte as strings
     troca(vetor,trocado, n_letras);
     
     printf("Invertido:\n");
     for(j=0; j<n_letras; j++){
         printf("%c", trocado[j]);
     }
     printf("\n\n");     
     
     system("pause");
     
     return 0;
}
