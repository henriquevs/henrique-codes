/*  UNICAMP - Universidade Estadual de Campinas
    MC202 - Estruturas de Dados
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratorio 03 - Banco Utopia */

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

/* Cria os caixas "no formato de uma lista ligada" */
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
         inicio=p; /* Ponteiro do inicio da sequencia de caixas de atendimento */
         aux=inicio; /* Faz a ligacao do primeiro elemento da "lista" de caixas com um possível segundo elemento */
         p=p->next;
      }
      else{ /* Vai preenchendo a sequencia de caixas na forma de lista ligada; notar que a referencia ao inicio da lista nao se perde */
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

/* Insere o cliente numa fila */
Caixa *insere(char nome[], int servico, int prioridade, Caixa *inicio){
   Cliente *q=NULL;
   Caixa *procura=NULL;
   
   q=cria_cliente(nome, servico);
   procura=busca_caixa(servico, inicio);
   if(procura != NULL){ /* Encontrou o caixa correto em que o cliente deve ser inserido */
      if(prioridade == 1){ /* Cliente especial */
         if(procura->inicio_especial==NULL || procura->fim_especial==NULL){ /* Fila de clientes especiais vazia */
            procura->inicio_especial=q;
            procura->fim_especial=q; /* Atualiza o final da fila */
            return procura;
         }
         else{
            procura->fim_especial->prox=q;
            procura->fim_especial=q; /* Atualiza o final da fila */
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
   return NULL; /* Erro ao inserir cliente */
}

/* Imprime a fila (caso esta não esteja vazia) de clientes de um caixa, comecando pelos clientes especiais e terminando com os normais */
void imprime(Caixa *inicio){
   Caixa *p=inicio;
   Cliente *q=NULL, *r=NULL;
   int flag1=0, flag2=0;
      
   /* Verifica se a fila de clientes especiais nao esta vazia */
   if(p->inicio_especial!=NULL && p->fim_especial!=NULL){ /* Se entrarmos neste "if" entao a lista de clientes especiais nao eh vazia */
      q=p->inicio_especial;
      r=q;
      printf("Servico %d:\n", p->numero_do_caixa);
      while(q!=NULL){ /* Anda ate o ultimo cliente especial */
         if(r->prox!=NULL && q->prox!=NULL){ /* Imprime ate o penultimo cliente especial */
            printf("%s->", q->nome);
            r=q;
            q=q->prox;
         }
         else{
            printf("%s", q->nome); /* Imprime o ultimo cliente especial */
            q=q->prox;
         }               
      }
      flag1=1; /* Indica que imprimimos todos os clientes especiais */
   }

   /* Verifica se a fila de clientes normais nao esta vazia */
   if(p->inicio_normal!=NULL && p->fim_normal!=NULL){ /* Se entrarmos neste "if" eh porque a lista de clientes normais nao eh vazia */
      /* Verifica se houve impressao de clientes especiais */
      if(flag1 == 1){ /* Se entrarmos neste "if" entao houve impressao de clientes especiais */
         q=p->inicio_normal;
         r=q;
         printf("->");
         while(q!=NULL){
            if(r->prox!=NULL && q->prox!=NULL){ /* Imprime ate o penultimo cliente normal */
               printf("%s->", q->nome);
               r=q;
               q=q->prox;
            }
            else{
               printf("%s", q->nome); /* Imprime o ultimo cliente normal */
               q=q->prox;
            }
         }
         flag2=1; /* Indica que imprimimos todos os clientes normais */
      } 
      else{
         if(flag1 == 0){ /* Se entrarmos neste "if" entao NAO houve impressao de clientes especiais */
            q=p->inicio_normal;
            r=q;
            printf("Servico %d:\n", p->numero_do_caixa);
            while(q!=NULL){
               if(r->prox!=NULL && q->prox!=NULL){ /* Imprime ate o penultimo cliente normal */
                  printf("%s->", q->nome);
                  r=q;
                  q=q->prox;
               }
               else{
                  printf("%s", q->nome); /* Imprime o ultimo cliente normal */
                  q=q->prox;
               }
            }
            flag2=1; /* Indica que imprimimos todos os clientes normais */
         }
      }
   }
   /* Se houve impressao de clientes, finalizamos a impressao com a quebra de linha */
   if(flag1==1 || flag2==1) printf("\n");
}

/* Impressao dos proximos a serem atendidos */
void imprime_proximos(Caixa *balcao){
   if(balcao->inicio_especial != NULL){ /* Verifica se a fila de clientes especiais esta vazia */
      printf("Servico %d:\n", balcao->numero_do_caixa);
      printf("%s\n", balcao->inicio_especial->nome);
      return;
   }
   else if(balcao->inicio_normal != NULL){ /* Verifica se a fila de clientes normais esta vazia */
      printf("Servico %d:\n", balcao->numero_do_caixa);
      printf("%s\n", balcao->inicio_normal->nome);
      return;
   }
}

/* Faz todas as filas avancarem, caso tenham cliente(s), de uma unidade */
Cliente *remover(Caixa *balcao){ /* A liberacao da memoria ocorre na funcao "main" */
   Cliente *aux=NULL;
   
   if(balcao->inicio_especial != NULL){ /* Verifica se a fila de clientes especiais nao esta vazia */
      aux=balcao->inicio_especial;
      if(balcao->inicio_especial == balcao->fim_especial){ /* Remocao quando so existe um cliente na fila */
         balcao->inicio_especial = NULL; /* Atualiza  o inicio da fila de clientes */
         balcao->fim_especial = NULL; /* Atualiza  o fim da fila de clientes */
      }
      else balcao->inicio_especial = balcao->inicio_especial->prox;
      return aux;
   }
   else if(balcao->inicio_normal != NULL){ /* Verifica se a fila de clientes normais esta vazia */
      aux=balcao->inicio_normal;
      if(balcao->inicio_normal == balcao->fim_normal){ /* Remocao quando so existe um cliente na fila */
         balcao->inicio_normal = NULL; /* Atualiza  o inicio da fila de clientes */
         balcao->fim_normal = NULL; /* Atualiza  o fim da fila de clientes */
      }
      else balcao->inicio_normal = balcao->inicio_normal->prox; /* Atualiza  o inicio da fila de clientes */
      return aux;
   }
   return NULL; /* Erro ao remover cliente */
}

/* Desaloca toda a memoria "preenchida pelos clientes" */
void desalocar_clientes(Cliente *q){
   Cliente *aux=NULL;
   while(q!=NULL){
      aux=q;
      q=q->prox;
      free(aux);
   }
}

/* Desaloca toda a memória "preenchida pelos caixas" */
void desalocar_caixas(Caixa *p){
   Caixa *aux=NULL;
   while(p!=NULL){
      if(p!=NULL){
         aux=p;
         p=p->next;
         desalocar_clientes(aux->inicio_especial); /* Libera fila de clientes especiais */
         desalocar_clientes(aux->inicio_normal); /* Libera fila de clientes normais */
         free(aux); /* Libera o caixa */
      }
   }
}

int main(){
   int n_caixas, opcao, prioridade, servico; /* "servico" se refere ao numero do caixa */
   Caixa *balcoes=NULL, *aux=NULL;
   Cliente *tmp=NULL;
   char nome_lido[16];
   
   scanf("%d", &n_caixas); /* Capta o numero de caixas do banco */
   
   balcoes=cria_caixas(n_caixas); /* "balcoes" aponta para o inicio da "lista ligada de caixas" */
   
   do{
      scanf("%d", &opcao);
      switch(opcao){ /* Avalia a opcao desejada */
         
         case 1: /* Novo cliente entra no banco */
            scanf(" %s %d %d", nome_lido, &prioridade, &servico);
            aux=insere(nome_lido, servico, prioridade, balcoes);
            if(aux != NULL){ /* Inseriu corretamente */
               if(prioridade == 1)
                  printf("O(A) cliente %s entrou na fila %d como cliente especial.\n", nome_lido, servico);
               else if(prioridade == 0)
                  printf("O(A) cliente %s entrou na fila %d como cliente normal.\n", nome_lido, servico);
            }
         break;
            
         case 2: /* Imprime a fila de clientes em cada caixa */
            aux=balcoes;
            printf("Visao geral dos clientes:\n");
            while(aux != NULL){
               imprime(aux);
               aux=aux->next;
            }
         break;

         case 3: /* Imprime o próximo cliente a ser atendido em cada caixa */
            aux=balcoes;
            printf("Proximos clientes a serem atendidos:\n");
            while(aux != NULL){
               imprime_proximos(aux);
               aux=aux->next;
            }
         break;
            
         case 4: /* Novo atendimento em todas as filas nao vazias (próximo cliente) */
            aux=balcoes;
            while(aux != NULL){ /* Removeu corretamente */
               tmp=remover(aux);
               if(tmp!=NULL){
                  printf("Um(a) cliente foi atendido(a) na fila %d.\n", aux->numero_do_caixa);
                  free(tmp); /* Libera memoria "alocada pelo cliente" */
               }
               else
                  printf("A fila %d esta vazia.\n", aux->numero_do_caixa);
               aux=aux->next;
            }
         break;

      }
   } while(opcao != 5); /* Encerra o expediente */
   printf("Encerrando expediente... Clientes nao atendidos:\n");
   aux=balcoes;
   while(aux != NULL){
      imprime(aux);
      aux=aux->next;
   }
   
   /* Desaloca toda a memoria utilizada no programa */
   desalocar_caixas(balcoes);
   
   return 0;

}
