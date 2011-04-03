#include <stdio.h>
#include <stdlib.h>

int somaVet(int vetor[], int tam){
    if(tam != 0)
        return;
    else{
        if(tam == 1)
            return vetor[tam - 1];
        else
            return (vetor[tam] + somaVet(vetor[], tam - 1);
    }
}

int main(){
     int resp;
     int v[5] = {2, 3, 4, 7, 1};
     
     resp = somaVet(v, 5);
     
     printf("Soma = %d", resp);
     
     system("pause");
     
     return 0;
}

