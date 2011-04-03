/* Efetua a troca de valores de 2 variaveis inteiras passadas na entrada */
#include <stdio.h>

void troca(int* p, int* i){
     int temp;
     
     temp = *p;
     *p = *i;
     *i = temp;
}

int main(){
     
     int a, b;
     
     printf("Entre com dois numeros\n");
     printf("a = ");
     scanf("%d", &a);
     printf("b = ");
     scanf("%d", &b);
     putchar('\n');
     
     troca(&a, &b);
     
     printf("Os novos valores sao:\na = %d\nb = %d", a, b);
     putchar('\n');
     putchar('\n');
     
     system("pause");
     
     return 0;
}
