#include <stdio.h>
#include <stdlib.h>

/* Nao rode este programa. Ele pode travar a sua maquina... */

int main() {
  char *p;

  while ((p = malloc(100)) != NULL);
  
  printf("Memoria esgotada.\n");

  system("pause");

  return 0;
}
