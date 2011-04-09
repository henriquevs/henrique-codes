/* Preciso terminar este lab */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct cliente{
   char nome[16]; /* Nome com no maximo 15 caracteres */
   struct cliente *prox;
} Cliente;

typedef struct caixa{
   int numero_do_caixa; /* O numero do caixa representa o servico, i.e., cada caixa faz um servico diferente */
   struct cliente *inicio_especial;
   struct cliente *fim_especial;
   struct cliente *inicio_normal;
   struct cliente *fim_normal;
   struct caixa *next;
} Caixa;

/* Testa a alocacao de memoria para o caixa */
void teste_memoria_caixa(Caixa *p){
   if(p == NULL){
      printf("Memoria insuficiente\n");
      exit(1);
   }
}

/* Testa a alocacao de memoria para o cliente */
void teste_memoria_cliente(Cliente *q){
   if(q == NULL){
      printf("Memoria insuficiente\n");
      exit(1);
   }
}

/* Cria os caixas "no formato de uma lista ligada */
Caixa *cria_caixas(int n){
   Caixa *inicio=NULL, *aux=NULL, *p;
   int i;

   for(i=0; i<n; i++){
      if(i == 0){
         p=(Caixa*)malloc(sizeof(Caixa));
         teste_memoria_caixa(p); /* Verifica */
         p->numero_do_caixa=i+1; /* Este numero representa o servico do caixa */
         p->inicio_especial=NULL;
         p->fim_especial=NULL;
         p->inicio_normal=NULL;
         p->fim_normal=NULL;
         p->next=NULL;
         inicio=p; /* Ponteiro do inicio da sequencia de caixas */
         aux=inicio; /* Faz a ligacao do primeiro elemento da "lista" de caixas com um possível segundo elemento */
         p=p->next;
      }
      else{ /* Vai preenchendo a sequencia de caixas na forma de lista ligada; notar que a referencia ao inicio desta lista nao se perde */
         p=(Caixa*)malloc(sizeof(Caixa));
         teste_memoria_caixa(p); /* Verifica */
         p->numero_do_caixa=i+1; /* Este numero representa o servico do caixa */
         p->inicio_especial=NULL;
         p->fim_especial=NULL;
         p->inicio_normal=NULL;
         p->fim_normal=NULL;
         p->next=NULL;
         aux->next=p;
         aux=p;
         p=p->next;
      }
   }
   return inicio;
}

/* Cria o no para inserir o cliente na sua respectiva fila */
Cliente *cria_cliente(char nome[], int servico){
   Cliente *aux=NULL;
   aux=(Cliente*)malloc(sizeof(Cliente));
   teste_memoria_cliente(aux); /* Verifica */
   strcpy(aux->nome,nome);
   aux->prox=NULL;
   return aux;
}

/* Busca o caixa em que o cliente deve ser inserido */
Caixa *busca_caixa(int n, Caixa *inicio){
   Caixa *aux=inicio;
   while(aux != NULL){
      if(aux->numero_do_caixa == n) return aux;
      else aux=aux->next;
   }
   return NULL;
}

Caixa *insere(char nome[], int servico, int prioridade, Caixa *inicio){
   Cliente *q=NULL;
   Caixa *procura=NULL;
   
   q=cria_cliente(nome, servico);
   procura=busca_caixa(servico, inicio);
   if(procura != NULL){ /* Encontrou o caixa correto em que o cliente deve ser inserido */
      

      
      if(prioridade == 1){ /* Cliente especial */
         
         if(procura->inicio_especial==NULL || procura->fim_especial==NULL){ /* Fila de clientes especiais vazia */
            procura->inicio_especial=q;
            procura->fim_especial=q;
            return procura;
         }
         else{
            procura->fim_especial->prox=q;
            procura->fim_especial=q; /* Atualia o final da fila */
            return procura;
         }
      

      }
      else if(prioridade == 0){ /* Cliente normal */
      
         if(procura->inicio_normal==NULL || procura->fim_normal==NULL){ /* Fila de clientes normais vazia */
            procura->inicio_normal=q;
            procura->fim_normal=q;
            return procura;
         }
         else{
            procura->fim_normal->prox=q;
            procura->fim_normal=q; /* Atualia o final da fila */
            return procura;
         }
      

      }
   
   
   
   }
   printf("Erro ao inserir cliente\n");
   return NULL;

}









int main(){
   int n_caixas, opcao, prioridade, servico; /* "servico" se refere ao numero do caixa */
   Caixa *balcoes, *aux=NULL;
   char nome_lido[16];
   
   scanf("%d", &n_caixas); /* Capta o numero de caixas do banco */
   
   balcoes=cria_caixas(n_caixas); /* "balcoes" aponta para o inicio da fila dos caixas */
   
   printf("'testando' - numero do servico do primeiro caixa: %d\n", balcoes->numero_do_caixa); // Está funcionando
   balcoes=balcoes->next;
   printf("'testando' - numero do servico do segundo caixa: %d\n", balcoes->numero_do_caixa); // Está funcionando
   
   do{
      scanf("%d", &opcao);
      
      switch(opcao){
         
         case 1: /* novo cliente entra no banco */
            scanf(" %s %d %d", nome_lido, &prioridade, &servico);
            aux=insere(nome_lido, servico, prioridade, balcoes);
            
            if(aux != NULL){
               if(prioridade == 1)
                  printf("O(A) cliente %s entrou na fila %d como cliente especial\n", nome_lido, servico);
               else if(prioridade == 0)
                  printf("O(A) cliente %s entrou na fila %d como cliente normal\n", nome_lido, servico);
            }
            
            break;
            
         case 2: /* imprime a fila de clientes em cada caixa */
            
            
            break;
            
         case 3: /* imprime o próximo cliente a ser atendido em cada caixa */
            
            
            break;
            
         case 4: /* novo atendimento (próximo cliente) */
            
            
            break;
            
         
      }
   } while(opcao != 5);
   
   // case 5: /* encerra expediente */
            
            
      
}
