/**
 * Programa do Cromossomo
 * Objetivo: permitir a insercao, remocao, impressao e crossover de cadeia de cromossomos 
 * Ultima atualizacao em 16/Nov/2010
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _cromossomo{
  char base;
  struct _cromossomo *prox;
} Cromossomo;

/*faz um crossover duplo em duas cadeias de cromossomos ('c1' e 'c2'). Os pontos dos crossover sao determinados por 'primeiro' e 'segundo'*/
void crossover(Cromossomo **c1, Cromossomo **c2, int primeiro, int segundo){
  Cromossomo *q, *p, *aux;
  int i,j;
  q = *c1;
  p = *c2; 

  /*percorre as duas cadeias ate' chegar no ponto do primeiro crossover*/
  for(i = 0; i < primeiro; i++){
     q = q->prox;
     p = p->prox;
  }

  /*faz o primeiro crossover*/
  aux = q->prox;
  q->prox = p->prox;
  p->prox = aux;
  
  /*percorre as duas cadeias ate' chegar no ponto do segundo crossover*/
  for(j = primeiro; j < segundo; j++){
     q = q->prox;
     p = p->prox;
  }
  
  /*faz o segundo crossover*/
  aux = q->prox;
  q->prox = p->prox;
  p->prox = aux;

  
}

/*dado uma base, retorno um apontador pra cromossomo que devera' ser inserido no final da cadeia*/
Cromossomo *criaCromossomo(char base){
  Cromossomo *c;
  c = (Cromossomo*) malloc(sizeof(Cromossomo));
  c->base = base;
  c->prox = NULL;
  return c;
}

/*insere cromossomos no final da cadeia*/
void insereFinal(Cromossomo **c,char base){
  Cromossomo *q;
  /*se a cadeia for vazia, insere no comeco*/
  if(*c == NULL){
    *c = criaCromossomo(base);
  }
  else{
    q = *c;
    /*percorre ate' o final da cadeia*/
    while(q->prox != NULL)
      q = q->prox;
    q->prox = criaCromossomo(base); 
  } 
}

/*imprime a cadeia de cromossomo*/
void imprimeLista(Cromossomo *c){
  if(c == NULL){
    printf("Lista vazia");  
    return;	
  }
  while(c != NULL){
    printf("%c",c->base);
    c = c->prox;
  }
  
}

/*remove o primeiro cromossomo de uma determinada base*/
void removeCromossomo(Cromossomo **inicio,char base){
  Cromossomo *aux, *ant, *p;
  
  /*remocao no inicio da cadeia*/
  if( (*inicio)->base == base){
    aux = *inicio;
    *inicio = (*inicio)->prox;
    free(aux);	
  }
  else{
    /*percorre a cadeia ate' achar o cromossomo a ser removido*/
    ant = *inicio;
    while((ant->prox != NULL) && (ant->prox->base != base)){
      ant = ant->prox;
    }

    /*se o proximo for null, entao nao achou*/
    if( ant->prox == NULL){
      printf("Base nao encontrada!\n");
      return;
    }
    /*caso contrario, achou e tem que remover*/
    else{
      aux = ant->prox;
      p = aux->prox;
      ant->prox = p;
      free(aux);
    }    
  }
  
}

/*cria um cromossomo com a base dada por 'base' e insere ele na posicao dada por 'pos'*/
void insereNaPosicao(Cromossomo **c, char base, int pos){
   Cromossomo *aux, *q;
   int i; 
   
   /*se a cadeia for vazia, nao insere nada, pois supostamente a cadeia ja deveria estar criada*/
   if(*c == NULL){
     printf("Erro! Cadeia vazia!\n");
     return;
   }
   else{
     aux = *c;

     /*se for inserir no comeco da cadeia*/
     if(pos == 0){
       aux = criaCromossomo(base);
       aux->prox = *c;
       *c = aux;
     }
     else{
       /*caso contrario, percorre ate' o ponto da insercao*/
       for(i = 1; i < pos && aux != NULL; i++)
	 aux = aux->prox;

       if( (aux == NULL) && ( i < pos) ){
	 printf("A posicao especificada para insercao do cromossomo (%d) esta' incorreta!\n",pos);
	 return;
       }
       else{
	 q = criaCromossomo(base);
	 q->prox = aux->prox;
	 aux->prox = q; 	 		
       }
     }
     
   }	
   
}


/*libera a memoria alocada para toda a lista*/
void liberaLista(Cromossomo **c){
  Cromossomo *aux;

  while(*c != NULL){
    aux = *c;
    *c = (*c)->prox;
    free(aux);    
  }
  

}


int main(){
  Cromossomo *c1, *c2;
  int i,j,pos;
  char base;

  /*inicializa as cadeias de cromossomos com NULL*/
  c1 = NULL;
  c2 = NULL; 

  /*le os valores digitados pelo usuario e insere na cadeia 1 (c1)*/
  printf("Digite os valores dos 10 cromossomos da primeira cadeia\n");
  for(i = 0; i < 10; i++){
    scanf("%c",&base);
    insereFinal(&c1,base);
  }

  /*le a quebra de linha e nao faz nada*/
  base = getchar();
  
  /*le os valores digitados pelo usuario e insere na cadeia 2 (c2)*/
  printf("Digite os valores dos 10 cromossomos da segunda cadeia\n");
  for(j = 0; j < 10; j++){
    scanf("%c",&base);
    insereFinal(&c2,base);
  }
  
  printf("\nCadeia1: ");
  imprimeLista(c1);
  printf("\n");
  printf("Cadeia2: ");
  imprimeLista(c2);
  printf("\n");

  /*realiza o duplo crossover nas posicoes 3 e 6 das cadeias*/
  crossover(&c1,&c2,3,6);
  printf("\n----------Depois do crossover------------");

  /*imprime a nova cadeia c1*/
  printf("\nCadeia1: ");
  imprimeLista(c1);
  
  /*imprime a nova cadeia c2*/
  printf("\nCadeia2: ");
  imprimeLista(c2);
  printf("\n");
  
  /*insere um novo cromossomo*/
  pos = 2;/*mude essa linha para testar diversas possibilidades*/
  base = 'A';/*mude essa linha para testar diversas possibilidades*/
  printf("Insere o cromossomo %c na posicao %d da cadeia 1\n",base,pos);
  insereNaPosicao(&c1,base,2);
  printf("Cadeia1: ");
  imprimeLista(c1);
  printf("\n"); 
  
  /*remove o primeiro cromossomo de uma dada base*/
  base = 'T';/*mude essa linha para testar diversas possibilidades*/
  printf("Remove a primeira base %c da cadeia 1\n",base);
  removeCromossomo(&c1,base);
  printf("Cadeia1: ");
  imprimeLista(c1);
  printf("\n"); 
  
  /*libera a memoria alocada para representar as cadeias de cromossomos*/
  liberaLista(&c1);
  liberaLista(&c2);
  
  return 0;
}
