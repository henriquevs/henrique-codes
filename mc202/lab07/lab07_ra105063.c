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
   
   if(get_pos(n_linhas, n_colunas, i+1, j)!=-1 && imagem[get_pos(n_linhas, n_colunas, i+1, j)] == 0){ // Verifica abaixo
      imagem[get_pos(n_linhas, n_colunas, i+1, j)] = 13;
      if(
      encontra_vertices(imagem, n_linhas, n_colunas, i+1, j);
   }
   
   if(get_pos(n_linhas, n_colunas, i-1, j)!=-1 && imagem[get_pos(n_linhas, n_colunas, i-1, j)] == 0){ // Verifica acima
      imagem[get_pos(n_linhas, n_colunas, i-1, j)] = 13;
      encontra_vertices(imagem, n_linhas, n_colunas, i-1, j);
   }
   
   if(get_pos(n_linhas, n_colunas, i, j+1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i, j+1)] == 0){ // Verifica direita
      imagem[get_pos(n_linhas, n_colunas, i, j+1)] = 13;
      encontra_vertices(imagem, n_linhas, n_colunas, i, j+1);
   }
   
   if(get_pos(n_linhas, n_colunas, i, j-1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i, j-1)] == 0){ // Verifica esquerda
      imagem[get_pos(n_linhas, n_colunas, i, j-1)] = 13;
      encontra_vertices(imagem, n_linhas, n_colunas, i, j-1);
   }
   
   if(get_pos(n_linhas, n_colunas, i+1, j+1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i+1, j+1)] == 0){ // Verifica abaixo e direita
      imagem[get_pos(n_linhas, n_colunas, i+1, j+1)] = 13;
      encontra_vertices(imagem, n_linhas, n_colunas, i+1, j+1);
   }
   
   if(get_pos(n_linhas, n_colunas, i+1, j-1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i+1, j-1)] == 0){ // Verifica abaixo e direita
      imagem[get_pos(n_linhas, n_colunas, i+1, j-1)] = 13;
      encontra_vertices(imagem, n_linhas, n_colunas, i+1, j-1);
   }
   
   if(get_pos(n_linhas, n_colunas, i-1, j+1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i-1, j+1)] == 0){ // Verifica acima e direita
      imagem[get_pos(n_linhas, n_colunas, i-1, j+1)] = 13;
      encontra_vertices(imagem, n_linhas, n_colunas, i-1, j+1);
   }
   
   if(get_pos(n_linhas, n_colunas, i-1, j-1)!=-1 && imagem[get_pos(n_linhas, n_colunas, i-1, j-1)] == 0){ // Verifica acima e esquerda
      imagem[get_pos(n_linhas, n_colunas, i-1, j-1)] = 13;
      encontra_vertices(imagem, n_linhas, n_colunas, i-1, j-1);
   }
   //return;
}

// Cria um no para o candidato a vertice
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

int main(){
   char tipo[2];
   char tmp;
   int n_linhas, n_colunas, val_maximo, i, j, n_pixels;
   unsigned char *imagem;
   unsigned int aux;
   Vertice *p=NULL;
   
   scanf("%c%c", &tipo[0], &tipo[1]);
   
   //printf("tipo[0]:%c - tipo[1]:%c\ttipo da imagem:%c%c\n", tipo[0], tipo[1], tipo[0], tipo[1]);
   
   getchar();
   
   tmp=getchar();
   while(tmp=='#'){ // Desconsidera comentarios na leitura
      while(tmp!='\n')
         tmp = getchar();
      tmp=getchar();
   }
   ungetc(tmp, stdin);
   
   scanf("%d %d", &n_colunas, &n_linhas); // Captura as dimensões da imagem
   //printf("Dimensoes da imagem:\tlinhas=%d\tcolunas=%d\n", n_linhas, n_colunas);
   
   scanf("%d", &val_maximo); // Captura a escala dos pixels da imagem
   //printf("Valor maximo de cada pixel: %d\n", val_maximo);
   
   imagem=(unsigned char*)malloc(n_linhas*n_colunas*sizeof(unsigned char)); // Aloca a memoria necessaria para armazenar a imagem
   verifica_memoria(imagem);
   
   // Captura a imagem
   for(i=0; i<n_linhas; i++){
      for(j=0; j<n_colunas; j++){
         scanf("%u", &aux);
         imagem[get_pos(n_linhas, n_colunas, i, j)]=(unsigned char)aux;
      }
   }
   //printf("\nImagem Capturada:\n");
   //imprime_imagem(imagem, n_linhas, n_colunas);
   
   for(i=0; i<n_linhas*n_colunas; i++)
      if(imagem[i] != 0 && imagem[i]!= 128) 
         imagem[i]=255; // Manipulo a imagem para eliminar lixo e poder analisar os candidatos a vértices e arestas 
   
   p=cria_no_vertice(p, n_linhas, n_colunas); // cria o candidado a vertice
   
   for(i=0; i<n_linhas; i++)
      for(j=0; j<n_colunas; j++)
         if(imagem[get_pos(n_linhas, n_colunas, i, j)]==0){
            imagem[get_pos(n_linhas, n_colunas, i, j)]=13;
	    encontra_vertices(p, imagem, n_linhas, n_colunas, i, j);
         }

   printf("P2\n%d %d\n%d\n", n_colunas, n_linhas, val_maximo);
   imprime_imagem(imagem, n_linhas, n_colunas);
   
   return 0;
}