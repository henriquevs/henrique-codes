#include <stdio.h>
#include <stdlib.h>

int main() {
  int x;
  int *ap_x = &x;

  x = 100;
  printf("Valor de x = %d\n", *ap_x);

  *ap_x = 200;
  printf("Valor de x = %d\n", *ap_x);

  system("pause");

  return 0;
}
