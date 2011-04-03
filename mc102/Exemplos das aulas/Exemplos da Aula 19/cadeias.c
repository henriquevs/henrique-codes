#include <stdio.h>
#include <stdlib.h>

/* Faz uma cópia de orig em dest, incluindo o caracter terminador \0. 
   Supoe que dest tem espaco suficiente. */
void copia_str(char *orig, char *dest) {
  while (*orig != '\0') {
    *dest = *orig;
    dest++;
    orig++;
  }
  *dest = *orig;
}

int main() {
  char s1[] = "cadeia";
  char s2[20];

  copia_str(s1, s2);
  printf ("%s\n\n", s2);

  system("pause");

  return 0;
}
