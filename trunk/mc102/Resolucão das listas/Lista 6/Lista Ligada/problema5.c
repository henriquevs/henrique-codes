/* Lista de Exercicios 6 - Lista Ligada - Problema 5*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sequencia{
    int numero;
    struct sequencia* prox;
} Sequencia;

Sequencia* criaNo(int n, Sequencia* prox){
    Sequencia* pt;
    pt = (Sequencia*)malloc(sizeof(Sequencia));
    pt->numero = n;
    pt->prox = prox;
    return pt;
}

/* Insere de forma desordenada, de acordo com os dados passados na entrada padrão */
void insere(int n, Sequencia* comeco){
    Sequencia* aux, *ant;
    if(comeco == NULL)
        criaNo(n, NULL);
    else{
        aux = comeco;
        while(aux != NULL){
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = criaNo(n, aux);
    }
}

Sequencia* removePar(Sequencia** comeco){
    Sequencia* aux;
    while(*comeco != NULL){
        if(((*comeco)->numero) % 2 == 0){ /* Elimina no com valor par */
            aux = *comeco;
            comeco = &((*comeco)->prox);
            free(aux);
        }
        else
             comeco = &((*comeco)->prox);
    }
    return *comeco;
}

/* Impressao da Lista */
void imprimeLista(Sequencia* comeco){
    int valor;
    valor = comeco->numero;
    printf("Impressao da lista sem numeros pares:\n\n");
    while(comeco != NULL){
        if(comeco->prox == NULL)
            printf("%d", valor);        
        else
            printf("%d - ", valor);
    }
    printf("\n\n");
}

/* Inicializacao */
int main(){
    Sequencia* comeco;
    comeco = NULL; /* Inicializacao da lista como vazia */ 
    int numero_lido;
    char parametro;
   
    do{
       parametro = getchar();
       switch(parametro){
         case('i'): /* Insere um novo no */
            getchar();
            scanf("%d", &numero_lido);
            getchar();
            insere(numero_lido, comeco);                        
            break;
            
         case('r'): /* Faz a remocao de nos com numeros pares */
            removePar(&comeco);
            printf("Remocao feita com sucesso\n");
            break;
         
         
         case('p'): /* Faz a impressao de todos os nos que contem numeros impares */
            if(comeco != NULL)
               imprimeLista(comeco);
            break;
      }

   } while(parametro != 'f');

   system("pause");
    
   return 0;   
}
