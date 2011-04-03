/*
 * Cópia de arquivo para a saída padrão.
 */
#include<stdio.h>

int main() {
  FILE* f;
  char c;
  
  f = fopen ("teste.txt", "r");

  if (f == NULL) {
    perror("teste.txt");
    
    system("pause");
    
    return 1;
  }
  
  while (fscanf(f, "%c", &c) != EOF)
    printf("%c", c);
  fclose(f);  
  
  system("pause");
  
  return 0;
}
