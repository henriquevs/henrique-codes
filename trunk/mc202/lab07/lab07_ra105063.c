/* UNICAMP - Universidade Estadual de Campinas
   MC202 - Estruturas de Dados
   Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
   Laboratorio 07 - Grafo */

#include <stdio.h>
#include <stdlib.h>

#define COR_FUNDO 200

// Estrutura dos vertices
typedef struct vertice{
   int num_vertice;
   int pos_linha_vertice;
   int pos_coluna_vertice;
   int numero_pixels;
   int min_linha_vertice;
   int min_coluna_vertice;
   int max_linha_vertice;
   int max_coluna_vertice;
   int x; // Coluna
   int y; // Linha
   struct vertice *prox;
} Vertice;

// Verifica alocacao de memoria para a imagem
void verifica_memoria(unsigned char *imagem){
   if(imagem==NULL){
      printf("Erro na alocacao dos pixels da imagem\n");
      exit(1);
   }
}

// Verifica alocacao de memoria para o vertice
void verifica_memoria_vertice(Vertice *p){
   if(p==NULL){
      printf("Erro na alocacao do vertice\n");
      exit(1);
   }
}

// Impressao da imagem (na forma de matriz)
void imprime_imagem(unsigned char *imagem ,int n_linhas, int n_colunas){
   int i, contador=0;
   for(i=0; i<(n_linhas*n_colunas); i++){
      printf("%d ", imagem[i]);
      contador++;
      if((contador%n_colunas)==0){ // Verifica quando chega-se ao fim da linha
         ungetc(' ', stdin);
         printf("\n");
      }
   }
}

// Retorna a posicao do elemento no vetor ou -1 caso a operação seja invalida
int get_pos(int n_linhas, int n_colunas, int i, int j){ // "i" = posicao na linha e "j" = posicao na coluna
   if(i<0 || j<0 || i>=n_linhas || j>=n_colunas)
      return -1;
   else
      return (i*n_colunas+j);
}

// Caminha no possivel vertice e conta sua quantidade de  pixels
// Sinaliza o possivel vertice com o valor '13' para poder analisar outros candidatos a vertices
void encontra_vertices(Vertice **p, unsigned char *imagem, int n_linhas, int n_colunas, int i, int j){ // "i" = posicao na linha e "j" = posicao na coluna

   (*p)->numero_pixels++; // Conta os pixels presentes na componente conexa (incluindo o primeiro pixel visto)
   
   // Atualiza as posicoes de maximo e minimo no candidato a vertice
   if(i < (*p)->min_linha_vertice) (*p)->min_linha_vertice=i;
   if(i > (*p)->max_linha_vertice) (*p)->max_linha_vertice=i;
   if(j < (*p)->min_coluna_vertice) (*p)->min_coluna_vertice=j;
   if(j > (*p)->max_coluna_vertice) (*p)->max_coluna_vertice=j;
      
   
   if(get_pos(n_linhas, n_colunas, i+1, j)!=-1 && imagem[get_pos(n_linhas, n_colunas, i+1, j)] == 0){ // Verifica abaixo
      imagem[get_pos(n_linhas, n_colunas, i+1, j)] = 13;
      encontra_vertices(p, imagem, n_linhas, n_colunas, i+1, j);
   }
   
   if(get_pos(n_linhas, n_colunas, i-1, j)!=-1 && imagem[get_pos(n_linhas, n_colunas, i-1, j)] == 0){ // Verifica acima
      imagem[get_pos(n_linhas, n_colunas, i-1, j)] = 13;
      encontra_vertices(p, imagem, n_linhas, n_colunas, i-1, j);
   }
   
   if(get_pos(n_linhas, n_colunas, i, j+1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i, j+1)] == 0){ // Verifica direita
      imagem[get_pos(n_linhas, n_colunas, i, j+1)] = 13;
      encontra_vertices(p, imagem, n_linhas, n_colunas, i, j+1);
   }
   
   if(get_pos(n_linhas, n_colunas, i, j-1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i, j-1)] == 0){ // Verifica esquerda
      imagem[get_pos(n_linhas, n_colunas, i, j-1)] = 13;
      encontra_vertices(p, imagem, n_linhas, n_colunas, i, j-1);
   }
   
   if(get_pos(n_linhas, n_colunas, i+1, j+1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i+1, j+1)] == 0){ // Verifica abaixo e direita
      imagem[get_pos(n_linhas, n_colunas, i+1, j+1)] = 13;
      encontra_vertices(p, imagem, n_linhas, n_colunas, i+1, j+1);
   }
   
   if(get_pos(n_linhas, n_colunas, i+1, j-1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i+1, j-1)] == 0){ // Verifica abaixo e direita
      imagem[get_pos(n_linhas, n_colunas, i+1, j-1)] = 13;
      encontra_vertices(p, imagem, n_linhas, n_colunas, i+1, j-1);
   }
   
   if(get_pos(n_linhas, n_colunas, i-1, j+1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i-1, j+1)] == 0){ // Verifica acima e direita
      imagem[get_pos(n_linhas, n_colunas, i-1, j+1)] = 13;
      encontra_vertices(p, imagem, n_linhas, n_colunas, i-1, j+1);
   }
   
   if(get_pos(n_linhas, n_colunas, i-1, j-1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i-1, j-1)] == 0){ // Verifica acima e esquerda
      imagem[get_pos(n_linhas, n_colunas, i-1, j-1)] = 13;
      encontra_vertices(p, imagem, n_linhas, n_colunas, i-1, j-1);
   }
}

// Procura um vertice a partir de um indice passado para a funcao
Vertice *encontra_vertice(Vertice *lista_de_vertices, int indice){
   Vertice *aux=lista_de_vertices;
   if(aux==NULL) return NULL;
   else{
      while(aux!=NULL && aux->num_vertice!=indice)
	 aux=aux->prox;
      if(aux!=NULL) return aux;// Se encontrar o vertice com o indice procurado a funcao retorna um ponteiro para este vertice
      else return NULL;
   }
}

// Troca a cor de uma componente conexa para uma cor desejada
void troca_cor_componente(int i, int j, unsigned char *imagem ,int n_linhas, int n_colunas, unsigned char cor_atual, unsigned cor_futura){ // 'i' e 'j' indicam a minha posicao na imagem
   int aux = get_pos(n_linhas, n_colunas, i, j);
  
   if(aux!=-1 && imagem[aux] == cor_atual){
   
      imagem[aux]=cor_futura;
      
      // Chama a funcao recursivamente para os oito vizinhos, isto e, muda a cor de toda a componente conexa
      troca_cor_componente(i+1, j, imagem, n_linhas, n_colunas, cor_atual, cor_futura); // Abaixo
      
      troca_cor_componente(i-1, j, imagem, n_linhas, n_colunas, cor_atual, cor_futura); // Acima
      
      troca_cor_componente(i, j+1, imagem, n_linhas, n_colunas, cor_atual, cor_futura); // Direita

      troca_cor_componente(i, j-1, imagem, n_linhas, n_colunas, cor_atual, cor_futura); // Esquerda
      
      troca_cor_componente(i+1, j+1, imagem, n_linhas, n_colunas, cor_atual, cor_futura); // Abaixo e Esquerda
      
      troca_cor_componente(i+1, j-1, imagem, n_linhas, n_colunas, cor_atual, cor_futura); // Abaixo e Direita
      
      troca_cor_componente(i-1, j+1, imagem, n_linhas, n_colunas, cor_atual, cor_futura); // Acima e Esquerda
      
      troca_cor_componente(i-1, j-1, imagem, n_linhas, n_colunas, cor_atual, cor_futura); // Acima e direita
   }
}

// Encontra aresta e guarda a informacao de quais vertices ela esta ligada
void encontra_aresta(Vertice *lista_de_vertices, unsigned char *vertice_A, unsigned char *vertice_B, unsigned char *imagem, int n_linhas, int n_colunas, int i, int j, int numero_de_vertices){ // "i" = posicao na linha e "j" = posicao na coluna
   int aux=get_pos(n_linhas, n_colunas, i, j);
   Vertice *tmp1, *tmp2;
   
   if(aux!=-1 && imagem[aux]==128){
      
      imagem[aux]=COR_FUNDO;
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j)]<=numero_de_vertices){ // Verifica se ha vertice abaixo
	 tmp1=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j)]);
	 if(tmp1!=NULL && (*vertice_A)==0)
	    (*vertice_A)=imagem[get_pos(n_linhas, n_colunas, i+1, j)];
	 else{
	    tmp2=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j)]);
	    if(tmp2!=NULL && tmp2->num_vertice!=(*vertice_A) && (*vertice_B)==0){
	       (*vertice_B)=imagem[get_pos(n_linhas, n_colunas, i+1, j)];
	       return;
	    }
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j)]<=numero_de_vertices){ // Verifica se ha vertice acima
	 tmp1=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j)]);
	 if(tmp1!=NULL && (*vertice_A)==0)
	    (*vertice_A)=imagem[get_pos(n_linhas, n_colunas, i-1, j)];
	 else{
	    tmp2=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j)]);
	    if(tmp2!=NULL && tmp2->num_vertice!=(*vertice_A) && (*vertice_B)==0){
	       (*vertice_B)=imagem[get_pos(n_linhas, n_colunas, i-1, j)];
	       return;
	    }
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i, j+1)]<=numero_de_vertices){ // Verifica se ha vertice a direita
	 tmp1=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i, j+1)]);
	 if(tmp1!=NULL && (*vertice_A)==0)
	    (*vertice_A)=imagem[get_pos(n_linhas, n_colunas, i, j+1)];
	 else{
	    tmp2=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i, j+1)]);
	    if(tmp2!=NULL && tmp2->num_vertice!=(*vertice_A) && (*vertice_B)==0){
	       (*vertice_B)=imagem[get_pos(n_linhas, n_colunas, i, j+1)];
	       return;
	    }
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i, j-1)]<=numero_de_vertices){ // Verifica se ha vertice a esquerda
	 tmp1=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i, j-1)]);
	 if(tmp1!=NULL && (*vertice_A)==0)
	    (*vertice_A)=imagem[get_pos(n_linhas, n_colunas, i, j-1)];
	 else{
	    tmp2=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i, j-1)]);
	    if(tmp2!=NULL && tmp2->num_vertice!=(*vertice_A) && (*vertice_B)==0){
	       (*vertice_B)=imagem[get_pos(n_linhas, n_colunas, i, j-1)];
	       return;
	    }
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j+1)]<=numero_de_vertices){ // Verifica se ha vertice abaixo e esquerda
	 tmp1=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j+1)]);
	 if(tmp1!=NULL && (*vertice_A)==0)
	    (*vertice_A)=imagem[get_pos(n_linhas, n_colunas, i+1, j+1)];
	 else{
	    tmp2=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j+1)]);
	    if(tmp2!=NULL && tmp2->num_vertice!=(*vertice_A) && (*vertice_B)==0){
	       (*vertice_B)=imagem[get_pos(n_linhas, n_colunas, i+1, j+1)];
	       return;
	    }
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j-1)]<=numero_de_vertices){ // Verifica se ha vertice abaixo e direita
	 tmp1=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j-1)]);
	 if(tmp1!=NULL && (*vertice_A)==0)
	    (*vertice_A)=imagem[get_pos(n_linhas, n_colunas, i+1, j-1)];
	 else{
	    tmp2=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j-1)]);
	    if(tmp2!=NULL && tmp2->num_vertice!=(*vertice_A) && (*vertice_B)==0){
	       (*vertice_B)=imagem[get_pos(n_linhas, n_colunas, i+1, j-1)];
	       return;
	    }
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j+1)]<=numero_de_vertices){ // Verifica se ha vertice acima e direita
	 tmp1=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j+1)]);
	 if(tmp1!=NULL && (*vertice_A)==0)
	    (*vertice_A)=imagem[get_pos(n_linhas, n_colunas, i-1, j+1)];
	 else{
	    tmp2=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j+1)]);
	    if(tmp2!=NULL && tmp2->num_vertice!=(*vertice_A) && (*vertice_B)==0){
	       (*vertice_B)=imagem[get_pos(n_linhas, n_colunas, i-1, j+1)];
	       return;
	    }
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j-1)]<=numero_de_vertices){ // Verifica se ha vertice acima e esquerda
	 tmp1=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j-1)]);
	 if(tmp1!=NULL && (*vertice_A)==0)
	    (*vertice_A)=imagem[get_pos(n_linhas, n_colunas, i-1, j-1)];
	 else{
	    tmp2=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j+1)]);
	    if(tmp2!=NULL && tmp2->num_vertice!=(*vertice_A) && (*vertice_B)==0){
	       (*vertice_B)=imagem[get_pos(n_linhas, n_colunas, i-1, j-1)];
	       return;
	    }
	 }
      }
      
      // Chama a funcao recursivamente para os oito vizinhos
      encontra_aresta(lista_de_vertices, vertice_A, vertice_B, imagem, n_linhas, n_colunas, i+1, j, numero_de_vertices); // abaixo
      encontra_aresta(lista_de_vertices, vertice_A, vertice_B, imagem, n_linhas, n_colunas, i-1, j, numero_de_vertices); // acima
      encontra_aresta(lista_de_vertices, vertice_A, vertice_B, imagem, n_linhas, n_colunas, i, j+1, numero_de_vertices); // direita
      encontra_aresta(lista_de_vertices, vertice_A, vertice_B, imagem, n_linhas, n_colunas, i, j-1, numero_de_vertices); // esquerda
      encontra_aresta(lista_de_vertices, vertice_A, vertice_B, imagem, n_linhas, n_colunas, i+1, j+1, numero_de_vertices); // abaixo e direita
      encontra_aresta(lista_de_vertices, vertice_A, vertice_B, imagem, n_linhas, n_colunas, i+1, j-1, numero_de_vertices); // abaixo e esquerda
      encontra_aresta(lista_de_vertices, vertice_A, vertice_B, imagem, n_linhas, n_colunas, i-1, j+1, numero_de_vertices); // acima e direita
      encontra_aresta(lista_de_vertices, vertice_A, vertice_B, imagem, n_linhas, n_colunas, i-1, j-1, numero_de_vertices); // acima e esquerda
      
   }
}

// Cria e retorna um ponteiro para o candidato a vertice
Vertice *cria_no_vertice(Vertice *p, int n_linhas, int n_colunas){
   p=(Vertice*)malloc(sizeof(Vertice));
   verifica_memoria_vertice(p);
   p->numero_pixels=0;
   p->min_linha_vertice=n_linhas;
   p->min_coluna_vertice=n_colunas;
   p->max_linha_vertice=0;
   p->max_coluna_vertice=0;
   p->prox=NULL;
   
   return p;
}

// Insere um vertice de forma ordenada numa lista ligada simples
Vertice *add_lista_vertices(Vertice *lista, Vertice *p){
   Vertice *aux=lista, *ant=NULL;
   if(lista==NULL){ // Lista de vertices vazia
      p->num_vertice=1; // Primeiro vertice da lista
      lista=p;
   }
   else{
      if(p->pos_linha_vertice < aux->pos_linha_vertice || (p->pos_linha_vertice == aux->pos_linha_vertice && p->pos_coluna_vertice < aux->pos_coluna_vertice) ){ // Insere no comeco
	 p->prox=aux;
	 p->num_vertice=aux->num_vertice; // Determina o indice do novo vertice
	 while(aux!=NULL){ // Atualiza os indices de todos os vertices da lista que estao localizados apos o vertice que foi inserido
	    aux->num_vertice++;
	    aux=aux->prox;
	 }
	 lista=p;
      }
      else{ // Insere no meio ou no final
	 while(aux!=NULL && ((p->pos_linha_vertice > aux->pos_linha_vertice) || (p->pos_linha_vertice == aux->pos_linha_vertice && p->pos_coluna_vertice > aux->pos_coluna_vertice))){
	    ant=aux;
	    aux=aux->prox;
	 }
	 ant->prox=p;
	 p->prox=aux;
	 if(aux!=NULL) p->num_vertice=aux->num_vertice; // Determina o indice do novo vertice
	 else p->num_vertice=ant->num_vertice+1; // Tratamento do caso em que o novo vertice foi inserido na ultima posicao da lista
	 while(aux!=NULL){ // Atualiza os indices de todos os vertices da lista que estao localizados apos o vertice que foi inserido
	    aux->num_vertice++;
	    aux=aux->prox;
	 }
      }
   }
   return lista;
}

// Imprime as informacoes dos vertices de acordo com o especificado no enunciado
void imprime_vertices(Vertice *lista){
   Vertice *aux=lista;
   while(aux!=NULL){
      printf("Vertice %d: pixels[%d], posicao[%d, %d], Min[%d, %d], Max[%d, %d]\n", aux->num_vertice, aux->numero_pixels, aux->pos_linha_vertice, aux->pos_coluna_vertice, aux->min_linha_vertice, aux->min_coluna_vertice, aux->max_linha_vertice, aux->max_coluna_vertice);
      aux=aux->prox;
   }
}

// Criacao da matriz de adjacencia
unsigned char **cria_matriz_adjacencia(unsigned char **nova_matriz, int numero_vertices){
   int i;
   nova_matriz=(unsigned char**)malloc(numero_vertices*sizeof(unsigned char*));
   if(nova_matriz==NULL){ // Verifica alocacao de memoria
      printf("Erro na primeira alocacao dos elementos da matriz\n");
      exit(1);
   }
   for(i=0; i<numero_vertices; i++){
      nova_matriz[i]=(unsigned char*)malloc(numero_vertices*sizeof(unsigned char));
      if(nova_matriz[i]==NULL){
	 printf("Erro na segunda alocacao dos elementos da matriz\n");
      }
   }
   return nova_matriz;
}

// Marca a matriz de adjacencia da imagem
unsigned char **marca_matriz(unsigned char **matriz, unsigned char vertice_A, unsigned char vertice_B){
   matriz[vertice_A-1][vertice_B-1]=1;
   matriz[vertice_B-1][vertice_A-1]=1;
   return matriz;
}

// Imprime a imagem no formato de uma matriz
void imprime_matriz(unsigned char **matriz, int n_linhas, int n_colunas){
   int i, j, var=1;
   for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++){
         if(var%n_colunas != 0)
	    printf("%u ", matriz[i][j]);
         else
	    printf("%u\n", matriz[i][j]);
         var++;
      }
}

// Calcula o grau do grafo
int calcula_grau_do_grafo(unsigned char **matriz, int ordem_da_matriz){
   int i, j, grau_do_grafo1=0, grau_do_grafo2=0;
   if(matriz!=NULL){
      for(i=0; i<ordem_da_matriz; i++){
	 for(j=0; j<ordem_da_matriz; j++){
	    if(matriz[i][j]==1) grau_do_grafo2++;
	 }
	 if(grau_do_grafo1 < grau_do_grafo2) grau_do_grafo1=grau_do_grafo2;
	 grau_do_grafo2=0;
      }
   }
   return grau_do_grafo1;
}

// Libera a memoria alocada pela lista de vertices
void libera_lista(Vertice *lista){
   Vertice *aux;
   while(lista!=NULL){
      aux=lista;
      lista=lista->prox;
      free(aux);
   }
}

// Libera a memoria alocada pela imagem
void libera_matriz(unsigned char **matriz, int n_linhas){
   int i;
   for(i=0; i<n_linhas; i++)
      free(matriz[i]);
   free(matriz);
}

int main(){
   char tipo[2];
   char tmp;
   int n_linhas, n_colunas, val_maximo, i, j, numero_de_vertices, numero_de_arestas=0, grau_do_grafo=0;
   unsigned char *imagem, **matriz_de_adjacencia=NULL, vertice_A=0, vertice_B=0;
   unsigned int aux;
   Vertice *p=NULL, *lista=NULL, *r=NULL; // "lista" é o ponteiro para o inicio da lista ligada simples que contem os vertices como nos
   
   scanf("%c%c", &tipo[0], &tipo[1]);
   
   getchar();
   
   tmp=getchar();
   while(tmp=='#'){ // Desconsidera 	    printf("Valor de vertice_A = %d\nValor de vertice_B = %d\n", vertice_A, vertice_B);comentarios na leitura
      while(tmp!='\n')
         tmp = getchar();
      tmp=getchar();
   }
   ungetc(tmp, stdin);
   
   scanf("%d %d", &n_colunas, &n_linhas); // Captura as dimensões da imagem
   
   scanf("%d", &val_maximo); // Captura a escala dos pixels da imagem
   
   imagem=(unsigned char*)malloc(n_linhas*n_colunas*sizeof(unsigned char)); // Aloca a memoria necessaria para armazenar a imagem
   verifica_memoria(imagem);
   
   // Captura a imagem
   for(i=0; i<n_linhas; i++){
      for(j=0; j<n_colunas; j++){
         scanf("%u", &aux);
         imagem[get_pos(n_linhas, n_colunas, i, j)]=(unsigned char)aux;
      }
   }
   
   for(i=0; i<n_linhas*n_colunas; i++)
      if(imagem[i] != 0 && imagem[i]!= 128) 
         imagem[i]=COR_FUNDO; // Manipulacao da imagem para eliminar lixo a fim de poder analisar os candidatos a vértices e arestas 
   
   numero_de_vertices=0;
   // Le a imagem e cria uma lista ligada simples com os vertices encontrados
   for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++){
         if(imagem[get_pos(n_linhas, n_colunas, i, j)]==0){
	    p=cria_no_vertice(p, n_linhas, n_colunas); // cria o candidado a vertice
            imagem[get_pos(n_linhas, n_colunas, i, j)]=13;
	    encontra_vertices(&p, imagem, n_linhas, n_colunas, i, j);
	    
	    if((p->numero_pixels) >= 3000){ // Encontramos um vertice

	       // Calcula as posicoes na linha e coluna
	       p->pos_linha_vertice = ((p->max_linha_vertice - p->min_linha_vertice)/2) + p->min_linha_vertice;
	       p->pos_coluna_vertice = ((p->max_coluna_vertice - p->min_coluna_vertice)/2) + p->min_coluna_vertice;
	       
	       // Utilizaremos estas coordenadas no momento em que formos mudar a cor do vertice
	       p->y=i;
	       p->x=j;
	       
	       lista=add_lista_vertices(lista, p); // Adiciona o novo vertice ordenadamente na lista ligada
	       numero_de_vertices++; // Conta o numero de vertices validos
	    }
	    else{
	       // Se o candidato nao eh vertice alteramos os valores dos seus pixels para a cor de fundo, a fim de eliminar o lixo de memoria
	       troca_cor_componente(i, j, imagem, n_linhas, n_colunas, 13, COR_FUNDO); // Passo 'i' e 'j' para a funcao porque tenho certeza de que nesta posicao o candidato nao eh vertice
	       free(p);// Candidato nao eh vertice
	    }
	 }
      }
      
   // Os pixels de cada componente conexa tem o mesmo valor do indice de seu vertice
   r=lista;
   while(r!=NULL){
      troca_cor_componente(r->y, r->x, imagem, n_linhas, n_colunas, 13, r->num_vertice);
      r=r->prox;
   }
   
   // Criacao da matriz de adjacencia
   matriz_de_adjacencia=cria_matriz_adjacencia(matriz_de_adjacencia, numero_de_vertices);
   
   // Inicializacao dos valores da matriz de adjacencia
   for(i=0; i<numero_de_vertices; i++)
      for(j=0; j<numero_de_vertices; j++)
	 matriz_de_adjacencia[i][j]=0;
   
   // Caminha na imagem, encontra as arestas e marca as informacoes na matriz de adjacencia
   for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++){
	 vertice_A=0;
	 vertice_B=0;
	 
	 encontra_aresta(lista, &vertice_A, &vertice_B, imagem, n_linhas, n_colunas, i, j, numero_de_vertices);
	 
	 if(vertice_A!=0 && vertice_B!=0){
	    matriz_de_adjacencia = marca_matriz(matriz_de_adjacencia, vertice_A, vertice_B);
	    numero_de_arestas++;
	 }
      }
   
   // Libera memoria alocada pela imagem
   free(imagem);
   
   //Calcula o grau do grafo
   grau_do_grafo=calcula_grau_do_grafo(matriz_de_adjacencia, numero_de_vertices);
   
   printf("Numero de vertices: %d\nNumero de arestas: %d\nGrau do grafo: %d\n", numero_de_vertices, numero_de_arestas, grau_do_grafo);
   imprime_vertices(lista);
   imprime_matriz(matriz_de_adjacencia, numero_de_vertices, numero_de_vertices);
   
   libera_lista(lista);
   libera_matriz(matriz_de_adjacencia, numero_de_vertices);
   
   /*printf("P2\n%d %d\n", n_colunas, n_linhas);
   imprime_imagem(imagem , n_linhas, n_colunas);*/


   return 0;
}
