#include <stdio.h>
#include <stdlib.h>
/* Retorna a soma de m + m + 1 + ... + n - 1 + n */

int soma(int m, int n) {
  if (m == n)
    return n;
  else
    return m + soma(m+1, n);
}

int main() {
  int m, n, s;
  
  printf("Digite m: ");
  scanf("%d", &m);
  printf("Digite n: ");
  scanf("%d", &n);  
  
  s = soma(m, n);
  
  printf("Soma de %d a %d = %d\n", m, n, s);
  
  system("pause");  
  return 0;
}
