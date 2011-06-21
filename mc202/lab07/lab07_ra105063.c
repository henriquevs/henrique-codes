// lab 07

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

// Estrutura das arestas
typedef struct aresta{
   // Ao criar aresta, inicializar os ponteiros com 'NULL'
   Vertice *vertice_A;
   Vertice *vertice_B;
   struct aresta *next;
} Aresta;


// Verifica alocacao de memoria para a imagem
void verifica_memoria(unsigned char *imagem){					//FUNCIONA
   if(imagem==NULL){
      printf("Erro na alocacao dos pixels da imagem\n");
      exit(1);
   }
}

// Verifica alocacao de memoria para o vertice
void verifica_memoria_vertice(Vertice *p){					//FUNCIONA
   if(p==NULL){
      printf("Erro na alocacao do vertice\n");
      exit(1);
   }
}

// Impressao da imagem (na forma de matriz)
void imprime_imagem(unsigned char *imagem ,int n_linhas, int n_colunas){	//FUNCIONA
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

// Retorna a posicao do elemento no vetor ou -1 caso a operação seja invalida   //FUNCIONA
int get_pos(int n_linhas, int n_colunas, int i, int j){ // "i" = posicao na linha e "j" = posicao na coluna
   if(i<0 || j<0 || i>=n_linhas || j>=n_colunas)
      return -1;
   else
      return (i*n_colunas+j);
}

// Caminha no possivel vertice e conta sua quantidade de  pixels		//FUNCIONA
// Sinalizo o possivel vertice com o valor '13' para poder analisar outros possiveis candidatos a vertices
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


// Cria um no para a aresta
Aresta *cria_no_aresta(Aresta *q){						//FUNCIONA
   q=(Aresta*)malloc(sizeof(Aresta));
   if(q==NULL){
      printf("Erro na alocacao da aresta\n");
      exit(1);
   }
   else{
      q->vertice_A=NULL;
      q->vertice_B=NULL;
      q->next=NULL;
   }
   return q;
}

// Insere as arestas numa lista ligada simples
Aresta *insere_aresta(Aresta *lista_de_arestas, Aresta *novo){			//FUNCIONA
   Aresta *aux=lista_de_arestas;
   if(aux==NULL) lista_de_arestas=novo;
   else{
      while(aux->next!=NULL) aux=aux->next; // Avanca ate o penultimo no da lista de arestas
      if(novo->vertice_A!=NULL && novo->vertice_B!=NULL){
	 printf("Na insercao da aresta na lista ligada: indice verticeA: %d\n", novo->vertice_A->num_vertice);
	 printf("Na insercao da aresta na lista ligada: indice verticeB: %d\n", novo->vertice_B->num_vertice);
	 aux->next=novo; // Insere somente as arestas validas
      }
   }
   return lista_de_arestas; // Retorna a lista de arestas atualizada
}

// Procura um vertice a partir de um indice passado para a funcao
Vertice *encontra_vertice(Vertice *lista_de_vertices, int indice){		//FUNCIONA
   Vertice *aux=lista_de_vertices;
   if(aux==NULL) return NULL;
   else{
      while(aux!=NULL && aux->num_vertice!=indice)
	 aux=aux->prox;
      if(aux!=NULL) return aux;// Se encontrar o vertice com o indice procurado a funcao retorna um ponteiro para este vertice
      else return NULL;
   }
}

// Encontra aresta e guarda a informacao de quais vertices ela esta ligada
void encontra_aresta(Vertice *lista_de_vertices, Aresta **q, unsigned char *imagem, int n_linhas, int n_colunas, int i, int j, int numero_de_vertices){ // "i" = posicao na linha e "j" = posicao na coluna
   int aux=get_pos(n_linhas, n_colunas, i, j);
   Vertice *tmp;
   
   if(aux!=-1 && imagem[aux]==128){
      
      imagem[aux]=COR_FUNDO;
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j)]<=numero_de_vertices){ // Verifica se ha vertice abaixo
	 tmp=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j)]);
	 if(tmp!=NULL && (*q)->vertice_A==NULL){
	    (*q)->vertice_A=tmp;
	    printf("Na resursao da aresta: indice verticeA: %d\n", (*q)->vertice_A->num_vertice);
	 }
	 else if(tmp!=NULL && (*q)->vertice_A->num_vertice!=imagem[get_pos(n_linhas, n_colunas, i+1, j)] && (*q)->vertice_B==NULL){
	    (*q)->vertice_B=tmp;
	    printf("Na resursao da aresta: indice verticeB: %d\n", (*q)->vertice_B->num_vertice);
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j)]<=numero_de_vertices){ // Verifica se ha vertice acima
	 tmp=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j)]);
	 if(tmp!=NULL && (*q)->vertice_A==NULL){
	    (*q)->vertice_A=tmp;
	    printf("Na resursao da aresta: indice verticeA: %d\n", (*q)->vertice_A->num_vertice);
	 }
	 else if(tmp!=NULL && (*q)->vertice_A->num_vertice!=imagem[get_pos(n_linhas, n_colunas, i-1, j)] && (*q)->vertice_B==NULL){
	    (*q)->vertice_B=tmp;
	    printf("Na resursao da aresta: indice verticeB: %d\n", (*q)->vertice_B->num_vertice);
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i, j+1)]<=numero_de_vertices){ // Verifica se ha vertice a direita
	 tmp=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i, j+1)]);
	 if(tmp!=NULL && (*q)->vertice_A==NULL){
	    (*q)->vertice_A=tmp;
	    printf("Na resursao da aresta: indice verticeA: %d\n", (*q)->vertice_A->num_vertice);
	 }
	 else if(tmp!=NULL && (*q)->vertice_A->num_vertice!=imagem[get_pos(n_linhas, n_colunas, i, j+1)] && (*q)->vertice_B==NULL){
	    (*q)->vertice_B=tmp;
	    printf("Na resursao da aresta: indice verticeB: %d\n", (*q)->vertice_B->num_vertice);
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i, j-1)]<=numero_de_vertices){ // Verifica se ha vertice a esquerda
	 tmp=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i, j-1)]);
	 if(tmp!=NULL && (*q)->vertice_A==NULL){
	    (*q)->vertice_A=tmp;
	    printf("Na resursao da aresta: indice verticeA: %d\n", (*q)->vertice_A->num_vertice);
	 }
	 else if(tmp!=NULL && (*q)->vertice_A->num_vertice!=imagem[get_pos(n_linhas, n_colunas, i, j-1)] && (*q)->vertice_B==NULL){
	    (*q)->vertice_B=tmp;
	    printf("Na resursao da aresta: indice verticeB: %d\n", (*q)->vertice_B->num_vertice);
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j+1)]<=numero_de_vertices){ // Verifica se ha vertice abaixo e esquerda
	 tmp=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j+1)]);
	 if(tmp!=NULL && (*q)->vertice_A==NULL){
	    (*q)->vertice_A=tmp;
	    printf("Na resursao da aresta: indice verticeA: %d\n", (*q)->vertice_A->num_vertice);
	 }
	 else if(tmp!=NULL && (*q)->vertice_A->num_vertice!=imagem[get_pos(n_linhas, n_colunas, i+1, j+1)] && (*q)->vertice_B==NULL){
	    (*q)->vertice_B=tmp;
	    printf("Na resursao da aresta: indice verticeB: %d\n", (*q)->vertice_B->num_vertice);
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j-1)]<=numero_de_vertices){ // Verifica se ha vertice abaixo e direita
	 tmp=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i+1, j-1)]);
	 if(tmp!=NULL && (*q)->vertice_A==NULL){
	    
	    (*q)->vertice_A=tmp;
	    printf("Na resursao da aresta: indice verticeA: %d\n", (*q)->vertice_A->num_vertice);
	 }
	 else if(tmp!=NULL && (*q)->vertice_A->num_vertice!=imagem[get_pos(n_linhas, n_colunas, i+1, j-1)] && (*q)->vertice_B==NULL){
	    (*q)->vertice_B=tmp;
	    printf("Na resursao da aresta: indice verticeB: %d\n", (*q)->vertice_B->num_vertice);
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j+1)]<=numero_de_vertices){ // Verifica se ha vertice acima e direita
	 tmp=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j+1)]);
	 if(tmp!=NULL && (*q)->vertice_A==NULL){
	    (*q)->vertice_A=tmp;
	    printf("Na resursao da aresta: indice verticeA: %d\n", (*q)->vertice_A->num_vertice);
	 }
	 else if(tmp!=NULL && (*q)->vertice_A->num_vertice!=imagem[get_pos(n_linhas, n_colunas, i-1, j+1)] && (*q)->vertice_B==NULL){
	    (*q)->vertice_B=tmp;
	    printf("Na resursao da aresta: indice verticeB: %d\n", (*q)->vertice_B->num_vertice);
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j-1)]<=numero_de_vertices){ // Verifica se ha vertice acima e esquerda
	 tmp=encontra_vertice(lista_de_vertices, imagem[get_pos(n_linhas, n_colunas, i-1, j-1)]);
	 if(tmp!=NULL && (*q)->vertice_A==NULL){
	    (*q)->vertice_A=tmp;
	    printf("Na resursao da aresta: indice verticeA: %d\n", (*q)->vertice_A->num_vertice);
	 }
	 else if(tmp!=NULL && (*q)->vertice_A->num_vertice!=imagem[get_pos(n_linhas, n_colunas, i-1, j-1)] && (*q)->vertice_B==NULL){
	    (*q)->vertice_B=tmp;
	    printf("Na resursao da aresta: indice verticeB: %d\n", (*q)->vertice_B->num_vertice);
	 }
      }
      
      // Chama a funcao recursivamente para os oito vizinhos
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i+1, j, numero_de_vertices); // abaixo
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i-1, j, numero_de_vertices); // acima
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i, j+1, numero_de_vertices); // direita
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i, j-1, numero_de_vertices); // esquerda
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i+1, j+1, numero_de_vertices); // abaixo e direita
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i+1, j-1, numero_de_vertices); // abaixo e esquerda
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i-1, j+1, numero_de_vertices); // acima e direita
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i-1, j-1, numero_de_vertices); // acima e esquerda
      
   }
}

// Cria e retorna um ponteiro para o candidato a vertice			//FUNCIONA
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

// Insere um vertice de forma ordenada numa lista ligada simples		//FUNCIONA
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
void imprime_vertices(Vertice *lista){						//FUNCIONA
   Vertice *aux=lista;
   while(aux!=NULL){
      printf("Vertice %d: pixels[%d], posicao[%d, %d], Min[%d, %d], Max[%d, %d]\n", aux->num_vertice, aux->numero_pixels, aux->pos_linha_vertice, aux->pos_coluna_vertice, aux->min_linha_vertice, aux->min_coluna_vertice, aux->max_linha_vertice, aux->max_coluna_vertice);
      aux=aux->prox;
   }
}

// Troca a cor de uma componente conexa para uma cor desejada		//FUNCIONA
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

// Imprime os vertices nos quais as arestas estão ligadas			//FUNCIONA
void imprime_informacao(Aresta *lista_de_arestas){
   Aresta *r=lista_de_arestas;
   int contador=1;
   while(r!=NULL){
      if(r->vertice_A!=NULL && r->vertice_B!=NULL)
      printf("Aresta%d indiceVertice_A = %d indiceVertice_B = %d\n", contador, r->vertice_A->num_vertice, r->vertice_B->num_vertice);
      contador++;
      r=r->next;
      
   }
}

// Criacao da matriz de adjacencia						//FUNCIONA
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
/*unsigned char **marca_matriz(unsigned char **matriz, Aresta *p, int n_linhas, int n_colunas){
   int i, j;
   for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++){
         if(p->vertice_A!=NULL && p->vertice_B!=NULL){
            if(i==p->vertice_A->num_vertice && j==p->vertice_B->num_vertice){
               matriz[i][j]=1;

	    }
	 }
      }
   return matriz;
}*/

void imprime_matriz(unsigned char **matriz, int n_linhas, int n_colunas){	//FUNCIONA
   int i, j, var=0;
   for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++){
         printf("%u ", matriz[i][j]);
         var++;
         if(var%n_colunas == 0){
            ungetc(' ', stdin);
            printf("\n");
         }
      }
}


int main(){
   char tipo[2];
   char tmp;
   int n_linhas, n_colunas, val_maximo, i, j, numero_de_vertices;
   unsigned char *imagem, **matriz_de_adjacencia=NULL;
   unsigned int aux;
   Vertice *p=NULL, *lista=NULL, *r=NULL; // "lista" é o ponteiro para o inicio da lista ligada simples que contem os vertices como nos
   Aresta *q=NULL, *lista_de_arestas=NULL, *var=NULL;
   
   scanf("%c%c", &tipo[0], &tipo[1]);
   
   getchar();
   
   tmp=getchar();
   while(tmp=='#'){ // Desconsidera comentarios na leitura
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
	 p=cria_no_vertice(p, n_linhas, n_colunas); // cria o candidado a vertice
         if(imagem[get_pos(n_linhas, n_colunas, i, j)]==0){
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
   
   // Le a imagem e cria uma lista ligada simples com as arestas encontradas
   q=cria_no_aresta(q); // cria o no "aresta"
   for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++){
	 
	 encontra_aresta(lista, &q, imagem, n_linhas, n_colunas, i, j, numero_de_vertices);
	 
	 lista_de_arestas=insere_aresta(lista_de_arestas, q);
      }
   
   matriz_de_adjacencia=cria_matriz_adjacencia(matriz_de_adjacencia, numero_de_vertices);
   
   // Inicializa os valores da matriz de adjacencia
   for(i=0; i<numero_de_vertices; i++)
      for(j=0; j<numero_de_vertices; j++)
	 matriz_de_adjacencia[i][j]=0;
   
   // Preenche a matriz de adjacencia
   /*var=lista_de_arestas;
   while(var!=NULL){
      for(i=0; i<numero_de_vertices; i++)
	 for(j=0; j<numero_de_vertices; j++)
	    if(var->vertice_A!=NULL && var->vertice_B!=NULL && i==var->vertice_A->num_vertice && j==var->vertice_B->num_vertice){
	       matriz_de_adjacencia[i][j]=1;
	       matriz_de_adjacencia[j][i]=1;
	    }
      var=var->next;
   }*/
   
   imprime_matriz(matriz_de_adjacencia, numero_de_vertices, numero_de_vertices);
   
   
   
   /*printf("P2\n%d %d\n", n_colunas, n_linhas);
   imprime_imagem(imagem , n_linhas, n_colunas);*/
   //imprime_vertices(lista);

   imprime_informacao(lista_de_arestas);

   return 0;
}
