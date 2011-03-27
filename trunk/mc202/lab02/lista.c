#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

/* Definicao do registro de usuarios */
typedef struct user{
   int id;
   char nome[TAM];
   struct amigos *lista_de_amigos;
   struct user *user_prox;   
} User;

/* Definicao do registro de amigos */
typedef struct amigos{
   struct user *usr;
   struct amigos *amigo_next;
} Amigos;

/* Busca um usuario na lista */
User *buscaUsuario(User *lista, int id){
   User *p = lista;
   
   while(p != NULL){
      if(p->id == id) return p;
      else p = p->user_prox;
   }
   return p; /* Retorna o ponteiro do usuario detentor do "id" passado na entrada desta funcao ou nulo, caso ele nao seja encontrado */
}

/* Cria um novo no (usuario) */
User *cria_usuario(int id, char *name, User* proximo){
   User *p; /* "p" eh um ponteiro para o novo no */
   p = (User*)malloc(sizeof(User));
  
   strcpy(p->nome, name);
   p->id = id;
   p->lista_de_amigos = NULL; /* Quando um usuario eh inserido ele nao tem amigos */
   p->user_prox = proximo;   
   return p;
}

/* Insere (adiciona) um novo usuario de forma ordenada crescentemente */
void adicionaUsuario(int id_lido, char nome_lido[], User **usuario){
   User *p=NULL, *ant=NULL;
   
   if(*usuario == NULL){ /* Caso em que a lista eh vazia */
      *usuario = cria_usuario(id_lido, nome_lido, p);
      printf("O usuario %s (ID %d) foi adicionado na rede\n", nome_lido, id_lido);
      return;
   }

   else{
      p = *usuario; 
      if((p->id) > id_lido){ /* Insercao no comeco */
         p = cria_usuario(id_lido, nome_lido, p);
         *usuario = p;
         printf("O usuario %s (ID %d) foi adicionado na rede\n", nome_lido, id_lido);
         return;
      }
      else{
         while(p!=NULL && (p->id) < id_lido){ /* Insere no meio ou no final */
            ant = p;
            p = p->user_prox;
         }
         if(p==NULL){ /* Insere usuario no final da lista */
            ant->user_prox = cria_usuario(id_lido, nome_lido, p);
            printf("O usuario %s (ID %d) foi adicionado na rede\n", nome_lido, id_lido);
         }
         else if(p->id != id_lido){ /* nao insere dois usuarios diferentes com o mesmo id */
            ant->user_prox = cria_usuario(id_lido, nome_lido, p);
            printf("O usuario %s (ID %d) foi adicionado na rede\n", nome_lido, id_lido);
         }
      }
   }
}

/* Cria um novo no (amigo) */
Amigos *cria_amigo(User *usuario, Amigos *proximo){
   Amigos* r; /* "p" eh um ponteiro para o novo no */
   r = (Amigos*)malloc(sizeof(Amigos));
   
   r->usr = usuario;
   r->amigo_next = proximo;
   return r;  
}

/* Cria uma relacao de amizade entre os usuarios id1 e id2 */
int adicionaAmigo(User *lista, int id1, int id2){
   User *p=lista, *q=lista;
   Amigos *pa=NULL, *ant=NULL;
   
   while(p!=NULL){ /* Busca pelo id 1 */
      if(p->id == id1){
         while(q!=NULL){ /* id1 encontrado; busca pelo id2 */
            if(q->id == id2){
               pa = p->lista_de_amigos;
               if(pa==NULL || pa->usr->id > id2){ /* Insere no inicio da lista de amigos */
                  p->lista_de_amigos = cria_amigo(q, pa);
                  return 1;
               }
               while(pa!=NULL && pa->usr->id < id2){ /* Percorre a lista para inserir no meio ou no final */
                  ant = pa;
                  pa = pa->amigo_next;
               }
               if(pa==NULL){ /* Insercao no final da lista de amigos */
                  ant->amigo_next = cria_amigo(q, pa);
                  return 1;
               }
               else if(pa->usr->id != id2){ /* Insere no meio da lista */
                  ant->amigo_next = cria_amigo(q, pa);
                  return 1;
               }
               else{
                  return 0; /* Relacao de amizade ja existe */
               }
            }
            else q = q->user_prox;
         }
         break; /* id 2 nao existe na lista; id1 ja encontrado aborta busca no restante da lista */
      }
      else p = p->user_prox;
   }
   return 0;
}

int removeAmigo(User *lista, int id1, int id2){
   User *p=lista, *q=lista;
   Amigos *pa=NULL, *ant=NULL;
   
   while(p!=NULL){ /* busca pelo id 1 */
      if(p->id == id1){ /* Usuario detentor do id1 encontrado */ 
         while(q!=NULL){ /* id1 encontrado; busca pelo id2 */
            if(q->id == id2){ /* Usuario detentor do id2 encontrado */
               pa = p->lista_de_amigos;
               if(pa!=NULL && pa->usr->id == id2){ /* Testa */
                  p->lista_de_amigos = pa->amigo_next;
                  free(pa); /* Amigo id2 removido do inicio da lista de amigos do id1 */
                  return 1;
               }
               while(pa!=NULL){
                  if(pa->usr->id == id2){ /* a amizade existe */    
                     ant->amigo_next = pa->amigo_next;
                     free(pa); /* Amigo id2 removido do meio ou do final da lista de amigos do id1 */
                     return 1;
                  }
                  else{
                     ant = pa;
                     pa = pa->amigo_next;
                  }
               }
               //printf("nao existe amizade entre os usuarios %s e %s\n", p->nome, q->nome);
               return 0;
            }
            else q = q->user_prox;
         }
         break; /* id 2 nao existe na lista; id1 ja encontrado; aborta busca no restante da lista */
      }
      else p = p->user_prox;
   }
   return 0;
}

User *removerUsuario(User *lista, int id){
   User *p=lista, *ant=NULL;
   Amigos *pa=NULL;
   int aux, id_aux;
   
   if(p==NULL) return NULL; /* A lista de usuarios esta vazia */
   
   if(p->id == id){ /* Remove usuario do inicio lista */
      pa = p->lista_de_amigos;
      while(pa != NULL){ /* Percorre lista de amigos */
         id_aux = pa->usr->id;
         aux = removeAmigo(lista, id, id_aux); /* Remove o primeiro amigo da lista do usuario com o id passado na entrada */
         if(aux == 1){
            aux = removeAmigo(lista, id_aux, id); /* Remove o usuario da lista da lista de amigos do amigo */
            if(aux != 1){
               printf("erro ao remover vinculo de amizade\n");
               exit(1);
            }   
         }
         else{
            printf("erro ao remover vinculo de amizade\n");
            exit(1);
         }
         pa = pa->amigo_next;
      }
      lista = lista->user_prox;
      printf("O usuario %s foi excluido da rede\n", p->nome);
      free(p); /* Usuario removido do inicio da lista com sucesso */
      return lista;
   }
   
   while(p!=NULL){ /* Remove usuario do meio ou do final da lista */
      if(p->id == id){
         pa = p->lista_de_amigos;
         while(pa != NULL){ /* Percorre lista de amigos */
            id_aux = pa->usr->id;
            aux = removeAmigo(lista, id, id_aux); /* Remove o primeiro amigo da lista do usuario com o id passado na entrada */
            if(aux == 1) aux = removeAmigo(lista, id_aux, id); /* Remove o usuario da lista da lista de amigos do amigo */   
            else{
               printf("erro ao remover vinculo de amizade\n");
               exit(1);
            }
            pa = pa->amigo_next;
         }
         ant->user_prox = p->user_prox;
         printf("O usuario %s foi excluido da rede\n", p->nome);
         free(p); /* Usuario removido do meio ou final da lista com sucesso */
         return lista;
      }
      else {
         ant = p;
         p = p->user_prox;
      }
   }
   return lista;
}

void imprimeUsuarios(User *usuario){                              /* 5 Funciona */
   int flag = 0;
   printf("Usuarios da rede:");
   while(usuario){
     if(usuario->user_prox != NULL){ /* Imprime ate o penultimo usuario */
        printf(" %s,", usuario->nome);
        usuario = usuario->user_prox;
   flag++;
     }
     else{
   printf(" %s\n", usuario->nome); /* Imprime o ultimo usuario */
        usuario = usuario->user_prox;
   flag++;
     }
   }
   if(flag == 0)
     printf("\n");
}

/* Imprime toda lista de amigos */                             /* 6 Funciona */
void imprimeAmigos(Amigos *amigos){
   while(amigos){
     if(amigos->amigo_next){ /* Imprime ate o penultimo amigo */
        printf(" %s,", amigos->usr->nome);
        amigos = amigos->amigo_next;
     }
     else{
   printf(" %s\n", amigos->usr->nome); /* Imprime o ultimo amigo */
        amigos = amigos->amigo_next;
     }
   }
}

/* Funcao que imprime amigos em comum de dois usuarios */
void imprimeAmigosEmComum(User *lista, int id1, int id2){                      /* 5 */
   User *user1, *user2;
   Amigos *p, *q;
   int flag1=0;
   
   /* Encontra ID1 e ID2 */
   user1 = buscaUsuario(lista, id1);
   user2 = buscaUsuario(lista, id2);

   if(user1 == NULL || user2 == NULL) return; /* Se nao encontrar nada, cancela a operacao */
   printf("Amigos em comum entre %s e %s:", user1->nome, user2->nome);
   
   p = user1->lista_de_amigos;
   q = user2->lista_de_amigos;
   while(p!=NULL && q!=NULL){
      if(p->usr->id == q->usr->id){
         if(flag1 == 0){
            printf(" %s", p->usr->nome);
            flag1++;
         }
         else{
            printf(", %s", p->usr->nome);
         }
         p = p->amigo_next;
         q = q->amigo_next;
      }
      else{
         if(p->usr->id < q->usr->id)
            p = p->amigo_next;
         else
            q = q->amigo_next;
      }
   }
   printf("\n");
}

int converte(char string[23]){
   int p;
   if(strcmp(string, "addUsuario") == 0)
      p = 1;
   
   if(strcmp(string, "addAmigo") == 0)
      p = 2;
   
   if(strcmp(string, "removerAmigo") == 0)
      p = 3;
   
   if(strcmp(string, "removerUsuario") == 0)
      p = 4;
   
   if(strcmp(string, "imprimirUsuarios") == 0)
      p = 5;
   
   if(strcmp(string, "imprimirAmigos") == 0)
      p = 6;
   
   if(strcmp(string, "imprimirAmigosEmComum") == 0)
      p = 7;
   
   return p;
}

int main(){
   User *lista=NULL, *aux1=NULL, *aux2=NULL;
   char string[23], nome_lido[TAM];
   int flag, id_lido, id_1, id_2, teste;
   
   
   while(scanf("%s", string) != EOF){
      flag = converte(string);
      
      switch(flag){
         case 1: /* Opcao "addUsuario" */    //ok
            scanf(" %d", &id_lido);
            scanf(" %s", nome_lido);
            adicionaUsuario(id_lido, nome_lido, &lista);
            break;
   
         case 2: /* Opcao "addAmigo" */      //ok
            scanf(" %d %d", &id_1, &id_2);
            teste = adicionaAmigo(lista, id_1, id_2);
            if(teste == 1){
               teste = adicionaAmigo(lista, id_2, id_1);
               if(teste == 1){
                  aux1 = buscaUsuario(lista, id_1);
                  aux2 = buscaUsuario(lista, id_2);
                  printf("Os usuarios %s e %s se tornaram amigos\n", aux1->nome, aux2->nome);             
               }
               break;
            }
            else
               break;
         
         case 3: /* Opcao "removerAmigo" */
            scanf(" %d %d", &id_1, &id_2);
            teste = removeAmigo(lista, id_1, id_2);
            if(teste == 1){
               teste = removeAmigo(lista, id_2, id_1);
               if(teste == 1){
                  aux1 = buscaUsuario(lista, id_1);
                  aux2 = buscaUsuario(lista, id_2);
                  printf("Os usuarios %s e %s nao sao mais amigos\n", aux1->nome, aux2->nome);             
               }
               break;
            }
            else
               break;
         
         case 4: /* Opcao "removerUsuario" */
            scanf(" %d", &id_lido);
            lista = removerUsuario(lista, id_lido);
            break;
      
         case 5: /* Opcao "imprimirUsuarios" */
            imprimeUsuarios(lista);
            break;
      
         case 6: /* Opcao "imprimirAmigos" */
            scanf(" %d", &id_lido);
            aux1 = buscaUsuario(lista, id_lido);
            if(aux1 == NULL) /* Verifica se o usuario aux1 existe na lista */
               break;
            else{
               if(aux1->lista_de_amigos != NULL){
                  printf("Amigos de %s:", aux1->nome);
                  imprimeAmigos(aux1->lista_de_amigos);
                  break;
               }
               else{
                  printf("Amigos de %s:\n", aux1->nome);
                  break;
               }
            }
      
         case 7: /* Opcao "imprimirAmigosEmComum" */
            scanf(" %d %d", &id_1, &id_2);
            imprimeAmigosEmComum(lista,id_1, id_2);
            break;
    
         case '#': /* Caso em que o parametro passado na entrada eh um comentario */
            while(getchar() != '\n');
            break;
      }
   }
}