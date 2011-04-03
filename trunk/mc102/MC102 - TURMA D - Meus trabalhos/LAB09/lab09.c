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
  scanf("%d", &parametro);

  fr = fopen(nome_arq, "r");

  if(fr == NULL){
    printf("ERRO: Arquivo de entrada nao existe!!\n");
    
    system("pause");
    
    return 1;
  }

  if(parametro == 'c'){ /* Faz a codificacao do arquivo */
    strcat(nome_arq, "_codificado");
    fw = fopen(nome_arq, "w");

    while(fscanf(fr, "%c", &aux) != EOF){
      printf("%c", aux + 3);
      fprintf(fw, "%c", aux + 3);
    }
  }

  if(parametro == 'd'){ /* Faz a decodificacao do arquivo */
    strcat(nome_arq, "_decodificado");
    fw = fopen(nome_arq, "w");

    while(fscanf(fr, "%c", aux - 3) != EOF){
      printf("%c", aux - 3);
      fprintf(fw, "%c", aux - 3);
    }
  }

  fclose(fr);
  fclose(fw);

  system("pause");
  
  return 0;
}
