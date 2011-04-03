/* Calcula a soma e o produto de 2 numeros inteiros */
#include <stdio.h>

void SomaProduto(int a, int b, int* s, int* p){
     *s = a + b;
     *p = a * b;
}

int main(){
    int a, b;
    a = 2;
    b = 3;
    
    SomaProduto(a, b, &a, &b);
    
    printf("Soma = %d e Produto = %d\n\n", a, b);
    
    system("pause");
    
    return 0;
}
