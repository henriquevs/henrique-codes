#include <stdio.h>
#include <stdlib.h>

int main() {
  int i;
  int *p;

  for (i = 0; i < 100; i++) {
    p = (int*) malloc(100 * sizeof(int)); /* Vetor de inteiros com 100 posicoes */
    printf("endereco alocado = 0x%x\n", (unsigned int) p);
    free(p);
  }

  system("pause");

  return 0;
}
