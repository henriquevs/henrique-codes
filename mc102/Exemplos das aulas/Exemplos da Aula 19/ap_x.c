#include <stdio.h>
#include <stdlib.h>

int main() {
  int x = 100;
  int *ap_x = &x;

  printf("Valor de x = %d\n", x);
  printf("Endereco de x = 0x%x\n", (unsigned int) &x);
  printf("Endereco de x = 0x%x\n", (unsigned int) ap_x);
  
  system("pause");
  
  return 0;
}
