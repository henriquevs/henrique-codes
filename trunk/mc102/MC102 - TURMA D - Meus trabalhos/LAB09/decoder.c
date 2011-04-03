/*  UNICAMP - Universidade Estadual de Campinas
    MC102 - Algoritmos e Programacao de Computadores
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratorio 09 - Cifra de Cesar */
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

  FILE *fr, *fw;
  char nome_arq[40]; /* Nome do arquivo */
  char parametro, aux;

  parametro = getchar();
  getchar();
  scanf("%[^\n]s", nome_arq);
  fr = fopen(nome_arq, "r");

  if(fr == NULL){
    printf("ERRO: Arquivo de entrada nao existe!!\n");
    return 0;
  }

  if(parametro == 'c'){ /* Faz a codificacao do arquivo */
    strcat(nome_arq, "_codificado");
    fw = fopen(nome_arq, "w");

    while(fscanf(fr, "%c", &aux) != EOF){
      if(aux != '\n'){
	printf("%c", aux + 3);
	fprintf(fw, "%c", aux + 3);
      }
      else{
	printf("\n");
	fprintf(fw, "\n");
      }
    }
  }

  if(parametro == 'd'){ /* Faz a decodificacao do arquivo */
    strcat(nome_arq, "_decodificado");
    fw = fopen(nome_arq, "w");

    while(fscanf(fr, "%c", &aux) != EOF){
      if(aux != '\n'){
	printf("%c", aux - 3);
	fprintf(fw, "%c", aux - 3);
      }
      else{
	printf("\n");
	fprintf(fw, "\n");
      }
    }
  }

  fclose(fr);
  fclose(fw);

  return 0;
}
