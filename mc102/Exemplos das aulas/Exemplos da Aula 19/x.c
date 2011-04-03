#include <stdio.h>

int y = 200;

int main() {
  int x = 100;
  printf("Valor de x = %d\n", x);
  printf("Endereco de x = 0x%x\n", (unsigned int) &x);

  printf("Valor de y = %d\n", y);
  printf("Endereco de y = 0x%x\n", (unsigned int) &y);
  
  system("pause");
  
  return 0;
}
