/*
 * Copia de arquivo para outro arquivo.
 */
#include<stdio.h>

int main() {
  FILE  *fr, *fw;
  char c;
  
  fr = fopen ("teste.txt", "r");
  fw = fopen ("saida.txt", "w");

  if (fr == NULL) {
    perror("teste.txt");
    system("pause");
    return 1;
  }

  if (fw == NULL) {
    perror("saida.txt");
    system("pause");
    return 2;
  }
  
  while (fscanf(fr, "%c", &c) != EOF)
    fprintf(fw, "%c", c);
  
  fclose(fr);
  fclose(fw);
  
  system("pause");
  
  return 0;
}
