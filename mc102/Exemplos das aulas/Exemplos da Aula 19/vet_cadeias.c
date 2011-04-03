#include <stdio.h>

void imprime_vetor_cadeias(char *v[], int n) {
  int i;
  for (i = 0; i < n; i++) 
    printf("%s\n", v[i]);
}

int main() {
  char *cores[] = {"amarelo",
		   "verde",
		   "vermelho",
		   "laranja",
		   "preto"};

  imprime_vetor_cadeias(cores, 5);
 
  putchar('\n');
 
  system("pause");
 
  return 0;
}
