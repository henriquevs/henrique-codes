/* Lista de Exercicios 6 - Apontadores - Problema 2 */

/* Funcao que encontra os dois maiores numeros de uma lista ligada */
void acheOsDoisMaiores(int a[], int n, int* maior, int* seg_maior){
    int i, aux;
    if(n == 0) /* Vetor nao existe */
        return;
    else{
        if(n == 1){
           *maior = a[0];
           seg_maior = maior;
        }
        else{
            if(a[0] > a[1]){
                *maior = a[0];
                *seg_maior = a[1];
            }
            else{
                *maior = a[1];
                *seg_maior = a[0];        
            }
            for(i = 1; i < n; i++){
                if(a[i] > *maior){
                    seg_maior = maior;
                    *maior = a[i];
                }
            }
        }
    }
}
