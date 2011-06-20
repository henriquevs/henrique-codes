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
   struct vertice *prox;
   struct coordenadas *pixels; // Ponteiro para a lista de pixels que pertencem ao vertice
} Vertice;

// Estrutura das arestas
typedef struct aresta{
   // Ao criar aresta, inicializar os ponteiros com 'NULL'
   Vertice *vertice_A;
   Vertice *vertice_B;
   struct aresta *next;
} Aresta;

// Estrutura que armazena as infomacoes de posicao de cada pixel
typedef struct coordenadas{
   int pos_x; // Posicao na coluna
   int pos_y; // Posicao na linha
   int indice_do_vertice;
   struct coordenadas *proximo_pixel;
} Coordenadas;

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

// Cria um no para a lista ligada que contem todos os pixels de um dado vertice
Coordenadas *cria_no_pixel(Vertice *p, int posicao_linha, int posicao_coluna){  //FUNCIONA
   Coordenadas *novo=(Coordenadas*)malloc(sizeof(Coordenadas));
   if(novo==NULL){ // Verifica alocacao de memoria
      printf("Erro na alocacao das posicoes do pixel do vertice\n");
      exit(1);
   }
   else{ 
      novo->pos_y=posicao_linha;
      novo->pos_x=posicao_coluna;
      novo->indice_do_vertice = p->num_vertice;
      novo->proximo_pixel=NULL;
   }
   return novo;
}

// Insere os pixels de um dado vertice numa lista ligada simples
Coordenadas *insere_pixel(Vertice *p, Coordenadas *novo){
   Coordenadas *aux = p->pixels;
   if(aux==NULL) p->pixels=novo;
   else{
      while(aux->proximo_pixel != NULL) // Avancamos ate o ultimo elemento da lista de pixels
	 aux=aux->proximo_pixel;
      aux->proximo_pixel=novo;
   }
   return p->pixels; // Retorna a lista de pixels atualizada
}

// Esta funcao "caminha" no possivel vertice e conta sua quantidade de  pixels  //FUNCIONA
// Sinalizo o possivel vertice com o valor '13' para poder analisar outros possiveis candidatos a vertices
void encontra_vertices(Vertice **p, unsigned char *imagem, int n_linhas, int n_colunas, int i, int j){ // "i" = posicao na linha e "j" = posicao na coluna
   Coordenadas *tmp;
   
   tmp=cria_no_pixel((*p), i, j);
   (*p)->pixels=insere_pixel((*p), tmp); // Vai inserindo os pixels na lista ligada de pixels do vertice
   
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

// Verifica se um dado pixel faz parte do componente vertice; a funcao verifica em toda a lista ligada de vertices
int procura_pixel(Vertice *lista_de_vertices, int i, int j){ // "i" = posicao na linha e "j" = posicao na coluna
   Vertice *aux=lista_de_vertices;
   Coordenadas *tmp;
   
   while(aux!=NULL){ // Verificamos em toda a lista de vertices
      tmp=aux->pixels; // Verificamos a lista de pixels da componente
      while(tmp!=NULL){
	 if(tmp->pos_y==i && tmp->pos_x==j) // Encontramos o pixel
	    return tmp->indice_do_vertice; // Retorna o indice do vertice que contem o pixel procurado
	 tmp=tmp->proximo_pixel;
      }
      aux=aux->prox;
   }
   return 0; // Nao encontramos o pixel em nenhum dos vertices (o indice do primeiro vertice eh 1)
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
      aux->next=novo;
   }
   return lista_de_arestas; // Retorna a lista de arestas atualizada
}

// Procura um vertice a partir de um indice passado para a funcao
Vertice *encontra_vertice(Vertice *lista_de_vertices, int indice){
   Vertice *aux=lista_de_vertices;
   if(aux==NULL) return NULL;
   else{
      while(aux->num_vertice!=indice) aux=aux->prox;
      if(aux!=NULL) return aux;// Se encontrar o vertice com o indice procurado a funcao retorna um ponteiro para este vertice
      else return NULL;
   }
}

// Encontra aresta e guarda a informacao de quais vertices ela esta ligada
void encontra_aresta(Vertice *lista_de_vertices, Aresta **q, unsigned char *imagem, int n_linhas, int n_colunas, int i, int j){ // "i" = posicao na linha e "j" = posicao na coluna
   int aux=get_pos(n_linhas, n_colunas, i, j), indice;
   Vertice *procurado=NULL;
   
   if(aux!=-1 && imagem[aux]==128){
      
      imagem[aux]=COR_FUNDO;
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j)]==13){ // Verifica se ha vertice abaixo
	 indice=procura_pixel(lista_de_vertices, i+1, j);
	 if(indice!=0){
	    procurado=encontra_vertice(lista_de_vertices, indice); // Procura o vertice desejado
	    if(procurado!=NULL && (*q)->vertice_A==NULL)
	       (*q)->vertice_A=procurado;
	    else if(procurado!=NULL && (*q)->vertice_B==NULL)
	       (*q)->vertice_B=procurado;
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j)]==13){ // Verifica se ha vertice acima
	 indice=procura_pixel(lista_de_vertices, i-1, j);
	 if(indice!=0){
	    procurado=encontra_vertice(lista_de_vertices, indice); // Procura o vertice desejado
	    if(procurado!=NULL && (*q)->vertice_A==NULL)
	       (*q)->vertice_A=procurado;
	    else if(procurado!=NULL && (*q)->vertice_B==NULL)
	       (*q)->vertice_B=procurado;
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i, j+1)]==13){ // Verifica se ha vertice a direita
	 indice=procura_pixel(lista_de_vertices, i, j+1);
	 if(indice!=0){
	    procurado=encontra_vertice(lista_de_vertices, indice); // Procura o vertice desejado
	    if(procurado!=NULL && (*q)->vertice_A==NULL)
	       (*q)->vertice_A=procurado;
	    else if(procurado!=NULL && (*q)->vertice_B==NULL)
	       (*q)->vertice_B=procurado;
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i, j-1)]==13){ // Verifica se ha vertice a esquerda
	 indice=procura_pixel(lista_de_vertices, i, j-1);
	 if(indice!=0){
	    procurado=encontra_vertice(lista_de_vertices, indice); // Procura o vertice desejado
	    if(procurado!=NULL && (*q)->vertice_A==NULL)
	       (*q)->vertice_A=procurado;
	    else if(procurado!=NULL && (*q)->vertice_B==NULL)
	       (*q)->vertice_B=procurado;
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j+1)]==13){ // Verifica se ha vertice abaixo e esquerda
	 indice=procura_pixel(lista_de_vertices, i+1, j+1);
	 if(indice!=0){
	    procurado=encontra_vertice(lista_de_vertices, indice); // Procura o vertice desejado
	    if(procurado!=NULL && (*q)->vertice_A==NULL)
	       (*q)->vertice_A=procurado;
	    else if(procurado!=NULL && (*q)->vertice_B==NULL)
	       (*q)->vertice_B=procurado;
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i+1, j-1)]==13){ // Verifica se ha vertice abaixo e direita
	 indice=procura_pixel(lista_de_vertices, i+1, j-1);
	 if(indice!=0){
	    procurado=encontra_vertice(lista_de_vertices, indice); // Procura o vertice desejado
	    if(procurado!=NULL && (*q)->vertice_A==NULL)
	       (*q)->vertice_A=procurado;
	    else if(procurado!=NULL && (*q)->vertice_B==NULL)
	       (*q)->vertice_B=procurado;
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j+1)]==13){ // Verifica se ha vertice acima e direita
	 indice=procura_pixel(lista_de_vertices, i-1, j+1);
	 if(indice!=0){
	    procurado=encontra_vertice(lista_de_vertices, indice); // Procura o vertice desejado
	    if(procurado!=NULL && (*q)->vertice_A==NULL)
	       (*q)->vertice_A=procurado;
	    else if(procurado!=NULL && (*q)->vertice_B==NULL)
	       (*q)->vertice_B=procurado;
	 }
      }
      
      if(imagem[get_pos(n_linhas, n_colunas, i-1, j-1)]==13){ // Verifica se ha vertice acima e esquerda
	 indice=procura_pixel(lista_de_vertices, i-1, j-1);
	 if(indice!=0){
	    procurado=encontra_vertice(lista_de_vertices, indice); // Procura o vertice desejado
	    if(procurado!=NULL && (*q)->vertice_A==NULL)
	       (*q)->vertice_A=procurado;
	    else if(procurado!=NULL && (*q)->vertice_B==NULL)
	       (*q)->vertice_B=procurado;
	 }
      }
      
      // Chama a funcao recursivamente para os oito vizinhos
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i+1, j); // abaixo
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i-1, j); // acima
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i, j+1); // direita
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i, j-1); // esquerda
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i+1, j+1); // abaixo e direita
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i+1, j-1); // abaixo e esquerda
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i-1, j+1); // acima e direita
      encontra_aresta(lista_de_vertices, q, imagem, n_linhas, n_colunas, i-1, j-1); // acima e esquerda
      
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
   p->pixels=NULL;
   
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

// Altera os valores dos pixels de um vertice para o valor desejado		//FUNCIONA
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

// Imprime os vertices nos quais as arestas estão ligadas
void imprime_info(Aresta *lista_de_arestas){
   Aresta *r=lista_de_arestas;
   int contador=1;
   while(r!=NULL){
      printf("Aresta %d: VerticeA: indice = %d, VerticeB = %d\n", contador, r->vertice_A->num_vertice, r->vertice_B->num_vertice);
      contador++;
      r=r->next;
   }
}

void imprime_valores_pixels(Vertice *p){
   Coordenadas *aux=p->pixels;
   while(aux!=NULL){
      printf("posicao coluna: %d\nposicao linha: %d\n", aux->pos_x, aux->pos_y);
      aux=aux->proximo_pixel;
   }
}

int main(){
   char tipo[2];
   char tmp;
   int n_linhas, n_colunas, val_maximo, i, j;
   unsigned char *imagem;
   unsigned int aux;
   Vertice *p=NULL, *lista=NULL; // "lista" é o ponteiro para o inicio da lista ligada simples que contem os vertices como nos
   Aresta *q=NULL, *lista_de_arestas=NULL;
   
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
	       
	       lista=add_lista_vertices(lista, p); // Adiciona o novo vertice na lista ligada
	    }
	    else{
	       // Se o candidato nao eh vertice alteramos os valores dos seus pixels para a cor de fundo, a fim de eliminar o lixo de memoria
	       troca_cor_componente(i, j, imagem, n_linhas, n_colunas, 13, COR_FUNDO); // Passo 'i' e 'j' para a funcao porque tenho certeza de que nesta posicao o candidato nao eh vertice
	       free(p);// Candidato nao eh vertice
	    }
	 }
      }
   
   printf("%d\n", lista->num_vertice);
   
   q=cria_no_aresta(q);
   q->vertice_A=lista;
   q=insere_aresta(lista_de_arestas, q);
   //q=insere_aresta(
   //q->vertice_A->num_vertice=10;
   
   // Le a imagem e cria uma lista ligada com as arestas encontradas
   /*for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++){
	 q=cria_no_aresta(q);
	 if(imagem[get_pos(n_linhas, n_colunas, i, j)]==128){
	    
	    encontra_aresta(lista, &q, imagem, n_linhas, n_colunas, i, j);
	    
	    if(q->vertice_A!=NULL && q->vertice_B!=NULL)
	       lista_de_arestas=insere_aresta(lista_de_arestas, q);
	    else free(q);
	 }
      }*/
   
   //printf("P2\n%d %d\n", n_colunas, n_linhas);
   //imprime_imagem(imagem, n_linhas, n_colunas);
   
   //printf("posicao na coluna do primeiro pixel do primeiro vertice:%d\n", lista->pixels->pos_x);
   //printf("%d", lista_de_arestas->vertice_A->num_vertice);
   //if(lista_de_arestas!=NULL) printf("indice do verticeA ligado a aresta: %d\n", lista_de_arestas->vertice_A->num_vertice);
   
   Vertice *u=encontra_vertice(lista, 2);
   printf("indice do vertice procurado: %d     %d\n", u->num_vertice, u->prox->pixels->pos_x);
   
   if(q!=NULL)
      printf("%d\n", q->vertice_A->num_vertice);
   else
      printf("erro\n");
   //imprime_vertices(lista);
   
   //imprime_info(lista_de_arestas);
   
   imprime_valores_pixels(lista);   
      
   return 0;
}