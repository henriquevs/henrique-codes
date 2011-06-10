// lab 07

#include <stdio.h>
#include <stdlib.h>

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
} Vertice;

typedef struct aresta{
   int num_aresta;
   struct aresta *prox;
} Aresta;

void verifica_memoria(unsigned char *imagem){
   if(imagem==NULL){
      printf("Erro na alocacao dos pixels da imagem\n");
      exit(1);
   }
}

void verifica_memoria_vertice(Vertice *p){
   if(p==NULL){
      printf("Erro na alocacao do vertice\n");
      exit(1);
   }
}

void imprime_imagem(unsigned char *imagem ,int n_linhas, int n_colunas){
   int i, contador=0;
   for(i=0; i<(n_linhas*n_colunas); i++){
      printf("%d ", imagem[i]);
      contador++;
      if((contador%n_colunas)==0){
         ungetc(' ', stdin);
         printf("\n");
      }
   }
}

// Retorna a posicao no vetor ou -1 caso a operação seja invalida
int get_pos(int n_linhas, int n_colunas, int i, int j){ // "i" = posicao na linha e "j" = posicao na coluna
   if(i<0 || j<0 || i>=n_linhas || j>=n_colunas)
      return -1;
   else
      return (i*n_colunas+j);
}

// "Caminha" na componente conexa que pode ser um vertice e retorna o numero de pixels desta componente
void encontra_vertices(Vertice *p, unsigned char *imagem, int n_linhas, int n_colunas, int i, int j){ // "i" = posicao na linha e "j" = posicao na coluna
   
   p->numero_pixels++; // Conta os pixels presentes na componente conexa
   
   // Atualiza as posicoes de maximo e minimo no candidato a vertice
   if(i < p->min_linha_vertice) p->min_linha_vertice=i;
   if(i > p->max_linha_vertice) p->max_linha_vertice=i;
   if(j < p->min_coluna_vertice) p->min_coluna_vertice=j;
   if(j > p->max_coluna_vertice) p->max_coluna_vertice=j;
      
   
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
   //return p;
}

// Cria um no candidato a vertice
Vertice *cria_no_vertice(Vertice *p, int n_linhas, int n_colunas){
   p=(Vertice*)malloc(sizeof(Vertice));
   verifica_memoria_vertice(p);
   p->numero_pixels=0;
   p->min_linha_vertice=n_linhas;
   p->min_coluna_vertice=n_linhas;
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
      if(p->pos_linha_vertice < aux->pos_linha_vertice || (p->pos_linha_vertice = aux->pos_linha_vertice && p->pos_coluna_vertice < aux->pos_coluna_vertice) ){ // Insere no comeco
	 p->prox=aux;
	 p->num_vertice=aux->num_vertice; // Determina o indice do novo vertice
	 while(aux!=NULL){ // Atualiza os indices de todos os vertices da lista que estao localizados apos o vertice que foi inserido
	    aux->num_vertice++;
	    aux=aux->prox;
	 }
	 lista=p;
      }
      else{ // Insere no meio ou no final
	 //while(aux!=NULL && (p->num_vertice) > aux->num_vertice){
	 while((aux!=NULL && p->pos_linha_vertice > aux->pos_linha_vertice) || (p->pos_linha_vertice = aux->pos_linha_vertice && p->pos_coluna_vertice > aux->pos_coluna_vertice)){
	    ant=aux;
	    aux=aux->prox;
	 }
	 ant->prox=p;
	 p->prox=aux;
	 p->num_vertice=aux->num_vertice; // Determina o indice do novo vertice
	 while(aux!=NULL){ // Atualiza os indices de todos os vertices da lista que estao localizados apos o vertice que foi inserido
	    aux->num_vertice++;
	    aux=aux->prox;
	 }
      }
   }
   return lista;
}

int main(){
   char tipo[2];
   char tmp;
   int n_linhas, n_colunas, val_maximo, i, j	;
   unsigned char *imagem;
   unsigned int aux;
   Vertice *p=NULL, *lista=NULL; // "lista" é o ponteiro para o inicio da lista ligada simples que contem os vertices como nos
   
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
         imagem[i]=255; // Manipulacao da imagem para eliminar lixo a fim de poder analisar os candidatos a vértices e arestas 
   
   p=cria_no_vertice(p, n_linhas, n_colunas); // cria o candidado a vertice
   
   // Le a imagem e cria uma lista ligada simples com os vertices encontrados
   for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++)
         if(imagem[get_pos(n_linhas, n_colunas, i, j)]==0){
            imagem[get_pos(n_linhas, n_colunas, i, j)]=13;
	    encontra_vertices(p, imagem, n_linhas, n_colunas, i, j);
	    
	    if((p->numero_pixels) >= 3000){ // Encontramos um vertice
	       p->pos_linha_vertice = ((p->max_linha_vertice - p->min_linha_vertice)/2) + p->min_linha_vertice;
	       p->pos_coluna_vertice = ((p->max_coluna_vertice - p->min_coluna_vertice)/2) + p->min_coluna_vertice;
	       lista=add_lista_vertices(lista, p); // Adiciona o novo vertice na lista ligada
	    }
	    
         }

   printf("P2\n%d %d\n%d\n", n_colunas, n_linhas, val_maximo);
   imprime_imagem(imagem, n_linhas, n_colunas);
   
   return 0;
}