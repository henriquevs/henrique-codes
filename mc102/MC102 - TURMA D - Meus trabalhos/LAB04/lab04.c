/*  UNICAMP - Universidade Estadual de Campinas
    MC102 - Algoritmos e Programação de Computadores
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratório 04 - check the check */

#include <stdio.h>

int main () {

   int posicao_peca[2];
   int i, j, check = 0;
   char  tab[8][8], peca, c;
   
   // Reconhece as posições da peça (torre, bispo ou rainha)
   for(i = 0; i < 8; i++){
      j = 0;
      while(((c = getchar()) != '\n') && (j < 8)){ // Ignora quebra de linha (não é caracter do tabuleiro)
	      tab[i][j] = c;
	    	 
            switch(tab[i][j]){
         	    case 't':
            	   posicao_peca[0] = i;
            	   posicao_peca[1] = j;
            	   peca = 't';
                   break;
         	    case 'b':
            	   posicao_peca[0] = i;
            	   posicao_peca[1] = j;
            	   peca = 'b';
    	           break;
         	    case 'r':
            	   posicao_peca[0] = i;
            	   posicao_peca[1] = j;
            	   peca = 'r';
            	   break;
            }
	    j++;
      }
   }


   
   //Preenche o tabuleiro vertical e horizontalmente
   if(peca == 't' || peca == 'r'){ //torre e rainha podem se movimentar na horizontal e na vertical

       //Para "caminhar" pela linha, mantemos i constante e variamos j
       i = posicao_peca[0]; //Coordena i para torre ou rainha 
       for(j = 0; j < 8; j++){
	       if(tab[i][j] == '.')
               tab[i][j] = '*';
	       else
	           if(tab[i][j] == 'R')
	               check = 1; //O Rei foi encontrado
       }		
   
       //Para "caminhar" pela coluna, mantemos j constante e variamos i
       j = posicao_peca[1]; //Coordena j para torre ou rainha
          for(i = 0; i < 8; i++){
             if(tab[i][j] == '.')
	             tab[i][j] = '*';
	      else
	         if(tab[i][j] == 'R')
	             check = 1; //O Rei foi encontrado
          }
   } 

   //Preenche o tabuleiro diagonalmente
   if(peca == 'b' || peca == 'r'){ //bispo e rainha podem se movimentar nas diagonais

       //Para "caminhar" pela primeira diagonal, variamos i e j simultaneamente
       i = posicao_peca[0]; //Coordena i para bispo ou rainha
       j = posicao_peca[1]; //Coordena j para bispo ou rainha

       //Preenche metade da primeira diagonal abaixo
       while((i < 8) && (j < 8)){
          if(tab[i][j] == '.')
	          tab[i][j] = '*';
          else
              if(tab[i][j] == 'R')
	              check = 1; //O Rei foi encontrado

       //Avança para a próxima posição
       i++;
       j++;
       }

       i = posicao_peca[0]; //Coordena i para bispo ou rainha
       j = posicao_peca[1]; //Coordena j para bispo ou rainha
       
       //Preenche metade da segunda diagonal acima
       while((i >= 0) && (j < 8)){
          if(tab[i][j] == '.')
	          tab[i][j] = '*';
          else
              if(tab[i][j] == 'R')
	              check = 1; //O Rei foi encontrado

       //Avança para a próxima posição
       i--;
       j++;
       }
   
       i = posicao_peca[0]; //Coordena i para bispo ou rainha
       j = posicao_peca[1]; //Coordena j para bispo ou rainha
       
       //Preenche segunda metade da primeira diagonal acima
       while((i >= 0) && (j >= 0)){
          if(tab[i][j] == '.')
	          tab[i][j] = '*';
          else
              if(tab[i][j] == 'R')
	              check = 1; //O Rei foi encontrado

       //Avança para a próxima posição
       i--;
       j--;
       }
       
       i = posicao_peca[0]; //Coordena i para bispo ou rainha
       j = posicao_peca[1]; //Coordena j para bispo ou rainha
       
       //Preenche segunda metade da segunda diagonal abaixo
       while((i < 8) && (j >= 0)){
          if(tab[i][j] == '.')
	          tab[i][j] = '*';
          else
              if(tab[i][j] == 'R')
	              check = 1; //O Rei foi encontrado

       //Avança para a próxima posição
       i++;
       j--;
       }
   }
    //imprime tabuleiro
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            printf("%c", tab[i][j]);
        printf("\n");
    }

    if (check == 1)
        printf("O Rei esta em check!\n");
    else
        printf("O Rei nao esta em check!\n");

    return 0;

}
