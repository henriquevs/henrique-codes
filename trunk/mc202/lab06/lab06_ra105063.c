// lab 06

#include <stdio.h>
#include <stdlib.h>

#define TAM 49

void verifica_memoria1(int **p){
   if(p==NULL){
      printf("Erro na alocação da matriz\n");
      exit(1);
   }
}

void verifica_memoria2(int *q){
   if(q==NULL){
      printf("Erro na alocação do elemento na matriz\n");
      exit(1);
   }
}

int **cria_matriz(int largura, int altura){
   int **mat=NULL;
   int i;
   mat=(int**)malloc(altura*sizeof(int*));
   verifica_memoria1(mat);
   for(i=0; i<altura; i++){
      mat[i]=(int*)malloc(largura*sizeof(int));
      verifica_memoria2(mat[i]);
   }
   return mat;
}

void imprime_matriz(int **matriz, int largura, int altura){
   int i, j;
   for(i=0; i<altura; i++){
      for(j=0; j<largura; j++){
         if(j<largura-1)
            printf("%d ", matriz[i][j]);
         else if(j==largura-1)
            printf("%d\n", matriz[i][j]);
      }
   }
}

// Insertion Sort
void ordena_vetor(int vetor[], int n_contatos){ // A funcao esta funcionando
   int i, j;
   int aux[1];
   for(i = 1; i < n_contatos; i++){
      aux[0] = vetor[i];
      for(j = i - 1; (j >= 0) && (aux[0] < vetor[j]); j--){
         vetor[j + 1] = vetor[j];
      }
      vetor[j + 1] = aux[0];
   }
}

int mascara(int **matriz, int largura, int altura, int pos_x, int pos_y){
   int v[TAM];
   int i, j, k=0, val;
   for(i=pos_y-3; i<=pos_y+3; i++){
      if(i>=0 && i<altura){
         for(j=pos_x-3; j<=pos_x+3; j++){
            if(j>=0 && j<largura){
               v[k]=matriz[i][j];
               k++;
            }
         }
      }
   }
   
   ordena_vetor(v, k);
   
   if(k%2==0)
      val=(v[(k/2)-1]+v[(k/2)])/2;
   else
      val=v[k/2];
   
   return val;
}

int main(){
   char tipo[2];
   int largura, altura, val_maximo, i, j;
   char tmp;
   int **matriz_1=NULL, **matriz_2=NULL;
   int q[5];
   q[0]=33;
   q[1]=23;
   q[2]=3;
   q[3]=12;
   q[4]=25;
   
   ordena_vetor(q, 5);
   //printf("%d %d %d %d %d\n", q[0], q[1], q[2], q[3], q[4]);
   
   tmp=getchar();
   tipo[0]=tmp;
   //printf("%c\n", tipo[0]);

   tmp=getchar();
   tipo[1]=tmp;
   //printf("%c\n", tipo[1]);
   
   tmp=getchar();
   
   tmp=getchar();
   while(tmp=='#'){
      while(tmp!='\n')
         tmp=getchar();
      tmp=getchar();
   }
   ungetc(tmp, stdin);
   
   scanf("%d %d", &largura, &altura);
   
   scanf("%d", &val_maximo);
   
   //printf("Largura:%d\nAltura:%d\nValor Maximo da cor da imagem:%d\n", largura, altura, val_maximo);
   
   matriz_1=cria_matriz(largura, altura);
   matriz_2=cria_matriz(largura, altura);
   
   // Le a matriz da entrada
   for(i=0; i<altura; i++){
      for(j=0; j<largura; j++)
         scanf("%d", &matriz_1[i][j]);
   }
   
   //imprime_matriz(matriz_1, largura, altura);
   
   for(i=0; i<altura; i++)
      for(j=0; j<largura; j++)
         matriz_2[i][j]=mascara(matriz_1, largura, altura, j, i);

   printf("%c%c\n", tipo[0], tipo[1]);
   printf("# MC202D: LAB06 - FILTRO DA MEDIANA\n");
   printf("%d %d\n", largura, altura);
   printf("%d\n", val_maximo);
   imprime_matriz(matriz_2, largura, altura);
   
   return 0;
}