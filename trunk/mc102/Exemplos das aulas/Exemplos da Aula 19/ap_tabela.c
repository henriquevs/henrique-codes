#include <stdio.h>
#include <stdlib.h>

int main() {
  int **ap_ap_int;
  int    *ap_int;
  int    i = 100;

  ap_int = &i;
  ap_ap_int = &ap_int;

  printf (" Nome     |  Endereco  | Valor \n");
  printf ("        i | 0x%x  | %d \n", (unsigned int) &i, i);
  printf ("   ap_int | 0x%x  | 0x%x \n", (unsigned int) &ap_int, (unsigned int) ap_int);
  printf ("ap_ap_int | 0x%x  | 0x%x \n", (unsigned int) &ap_ap_int, (unsigned int) ap_ap_int);

  system("pause");
  
  return 0;
}
