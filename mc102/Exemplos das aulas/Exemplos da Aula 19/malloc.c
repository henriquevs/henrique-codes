#include <stdio.h>
#include <stdlib.h>

int main() {
  int *p;
  int i;

  p = (int*) malloc(100 * sizeof(int)); /* Vetor com 100 posicoes */

  for (i = 0; i < 100; i++){
    p[i] = i;
    printf("%d\n", p[i]);
  }
  system("pause");
  
  return 0;
}
