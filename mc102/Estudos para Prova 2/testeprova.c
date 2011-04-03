#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Programa que concatena dois arquivos

int main() 
{
	FILE *arq1, *arq2, *arq3;
	char nome1[40], nome2[40], nome3[40], letra;
	
	scanf("%s %s %s", nome1, nome2, nome3);
	
    arq1 = fopen(nome1, "r");
	    	
	if (arq1 == NULL) 
    {    				
		printf("ERRO: 1 Arquivo de entrada nao existe!!\n");		
        return;
	}
	   
	arq3 = fopen(nome3, "w");
	if (arq3 == NULL) {    				
		perror("ERRO ao abrir o Arquivo a ser criado !!\n");		
        return;
	}
	
	while (fscanf(arq1, "%c", &letra) != EOF ) {
         fprintf(arq3, "%c", letra);
	     printf("%c", letra);
    }
	fprintf(arq3, "\n");
    printf("\n"); 
        
    fclose(arq1);
      
    arq2 = fopen(nome2, "r");
    if (arq2== NULL)
    {
        perror("ERRO: 2 Arquivo de entrada nao existe!!\n");
        return; }
	     
	while (fscanf(arq2 , "%c", &letra) != EOF )
	     {
         fprintf(arq3, "%c", letra);
	     printf("%c", letra);}
	     
    fprintf(arq3, "\n");
    printf("\n");
    
    fclose(arq2);
    fclose(arq3);	
	
	system("pause");
	return 0;
}
