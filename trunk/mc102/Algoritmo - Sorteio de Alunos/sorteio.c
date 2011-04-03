/**
autor: Leonardo P. Tizzei
objetivo: sortear um aluno aleatoriamente de uma lista de alunos que deve ser a entrada do programa
data: setembro/2010
 **/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
# define NUMERO_ALUNOS 64

/*essa funcao cria um vetor de alunos que sao passados na entrada padrao*/
void criaVetorDeAlunos(char vetor[][40], int num_alunos){
  int i,j;
  int ra;
  char c;
  
  for(i = 0; i < num_alunos; i++){
    scanf("%d",&ra);
    c = getchar();
    j = 0;
    
    /*le o nome*/
    while( ( ( c = getchar()) != '\n') && ( j < 40 ) ){
      vetor[i][j] = c;
      j++;
    }
    vetor[i][j] = '\0';
   
    
  }

}

/*dado o vetor de alunos, o tamanho do vetor*/
void imprimeUmNome(char vetor[][40], int indiceAleatorio){
  

  if( ( indiceAleatorio < NUMERO_ALUNOS ) && ( indiceAleatorio >= 0) ){
    printf("%s\n",vetor[indiceAleatorio]);
  }
  else{
    printf("O indice aleatorio gerado eh maior que o tamanho do vetor ou negativo\n");
  }
 
}

int main(void){

  int id;
  
  char alunos[NUMERO_ALUNOS][40];  
  
  /*gera um numero aleatorio, entre 0 e NUMERO_ALUNOS*/
  unsigned int iseed = (unsigned int)time(NULL);
  srand(iseed);
  id = rand();
  id = id % NUMERO_ALUNOS;
  
  /*le a entrada padrao*/
  criaVetorDeAlunos( alunos , NUMERO_ALUNOS ) ;
  
  /*imprime o nome de um aluno*/
  imprimeUmNome(alunos,id);
  
  

  return 0;

}

