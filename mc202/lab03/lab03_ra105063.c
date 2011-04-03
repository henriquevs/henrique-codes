/* Preciso terminar este lab */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct celula{
   char nome[16]; /* Nome com no maximo 15 caracteres */
   int servico;
   struct celula *prox;
} Celula;

typedef struct fila{
   struct celula *inicio;
   struct celula *fim;
} Fila;

/* Para usar a impressao devo colocar:
   fila = imprime(fila);
*/

/* Lembrar de apagar todos os elementos da fila e por ultimo apagar a fila */

/* Para 5 caixas sera uma matriz de cinco linhas por duas colunas, as linhas representam os caixas e as colunas representam os tipos de servico: normal ou especial 
ou posso fazer dois vetores, um para clientes normais e outro para os especiais
*/

int main(){
   int n_caixas, n_filas, parametro;
   Fila * vecFilas;
   Celula * aux;
   
   //scanf("%d", &n_caixas);
   n_caixas = 2;
   n_filas = n_caixas * 2;
   // Aloca filas
   vecFilas = (Fila*)malloc(sizeof(Fila)*n_filas);
   // Cria Nó
   aux = (Celula*)malloc(sizeof(Celula));
   strcpy(aux->nome,"joao");
   aux->servico = 1;
   aux->prox = NULL;
   // Acerta ponteiros para o nó
   vecFilas[0].inicio = aux;
   vecFilas[0].fim = aux;
   // Cria Nó
   aux = (Celula*)malloc(sizeof(Celula));
   strcpy(aux->nome,"maria");
   aux->servico = 2;
   aux->prox = NULL;
   // Acerta ponteiros para o nó
   vecFilas[0].fim->prox = aux;
   vecFilas[0].fim = aux;
   
   aux = vecFilas[0].inicio;
   while (aux!=NULL) {
      printf("%s %d\n", aux->nome, aux->servico);
      aux = aux->prox;
   }
   
   return 0;
}





















/* Testa se a memoria foi alocada corretamente */
void teste_memoria(Fila *p){
   if(p == NULL){
      printf("Memoria insuficiente\n");
      exit(1);
   }
}

/* Recebe um ponteiro do final e retorna um novo ponteiro para o final da fila */   
Fila *insere(Fila *fila, char nome[]){ /* Na fila, sempre inserimos no final */
   Celula *cel=NULL;
   
   cel=(Celula*)malloc(sizeof(Celula));
   /* Lembrar de verificar se a memória foi alocada corretamente */

   cel->prox = NULL;
   
   /* Insercao quando a fila esta vazia */
   if(fila->inicio == NULL && fila->fim == NULL){
      fila->inicio = cel;
      fila->fim = cel;
   }
   else{
      fila->fim->prox = cel;
      fila->fim = cel; /* Atualiza o final da fila */
   }
   return fila; /* Retorna a fila atualizada */
}

/* Pega o elemento e este sai da fila, porem nao ha liberacao de memoria e retorna esse elemento */
Celula *get(Fila **fila){
   Celula *aux=NULL;
   
   if((*fila)->inicio == NULL || (*fila)->fim == NULL) /* Fila sem nenhum elemento */
      return NULL;
   else if((*fila)->inicio == (*fila)->fim){ /* Fila com somente um elemento */
      aux = (*fila)->inicio;
      (*fila)->inicio = NULL;
      (*fila)->fim = NULL;
   }
   else{ /* Fila com mais de um elemento */
      aux = (*fila)->inicio;
      (*fila)->inicio = aux->prox;
   }
   return aux;
}

/* Remove do inicio */   
Fila *remover(Fila *fila){ /* Na estrutura Fila sempre removemos do inicio */
   Celula *aux=NULL;
   
   aux=(Celula*)malloc(sizeof(Celula));
   /* Lembrar de testar se a memoria foi alocada corretamente */
   
   /* Fila vazia */
   if(fila->inicio==NULL || fila->fim==NULL)
      return NULL;
   /* Caso em que a fila tem elementos */
   if(fila->inicio == fila->fim){ /* Fila com somente um elemento */
      free(fila->inicio); /* Podia ser free(fila->fim) */
      fila->inicio = NULL;
      fila->fim = NULL;
   }
   /* Fila com mais de um elemento */
   else{
      aux = fila->inicio;
      fila->inicio = aux->prox;
      free(aux);
   }
   return fila; 
}

/* Imprime todos os elementos */
Fila *imprime(Fila *fila){
   Celula *aux_cel;
   Fila *aux_fila;
   
   aux_fila = (Fila*)malloc(sizeof(Fila)); /* Crio uma fila nova idêntica à primeira, à medida que imprimo cada elemento da mesma */
   /* Lembrar de testar se a memoria foi alocada corretamente */
   
   while((aux_cel = get(&fila)) != NULL){
      /* Dar um printf no aux de acordo com o enunciado */
      aux_fila = insere(aux_fila, aux_cel->nome);
      free(aux_cel);
   }
   free(fila); /* Removo a fila antiga */
   return aux_fila; /* Retorno a nova fila */
}

/* Cria os caixas para o atendimento */
Fila *cria_caixas(int n_caixas){
   Fila **mat;
   int i;
   
   mat=(Fila**)malloc(sizeof(Fila));
   teste_memoria(*mat); /* Verificacao */
   for(i=0; i<n; i++){
      mat[i]=(Fila*)malloc(sizeof(Fila));
      teste_memoria(mat[i]); /* Verificacao */
   }
}
