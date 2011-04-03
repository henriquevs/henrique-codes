#include <stdio.h>

#include <stdlib.h>

int main () {

    int posicao_peca[2];
    int i, j, check = 0;
    char  tab[8][8], peca, c;

   /* Reconhece as posi��es da pe�a (torre, bispo ou rainha) */
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            while ((c = getchar()) == '\n'); //ignora quebra de linha (n�o � caracter do tabuleiro)
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
        }
    }


    /* Preenche tabuleiro vertical e horizontalmente */
    if (peca == 't' || peca == 'r') { //torre e rainha se movem vertical e horizontalmente

        //percorre a horizontal (coordenada i � fixa e j varia cruzando o tabuleiro)
        i = posicao_peca[0]; //coordena i da rainha ou torre
        for (j=0; j<8; j++)
            if (tab[i][j] == '.')
                tab[i][j] = '*';
            else if (tab[i][j] == 'R')
                check = 1; //achou o Rei

        //percorre a vertical (coordenada j � fixa e i varia cruzando o tabuleiro)
        j = posicao_peca[1]; //coordena j da rainha ou torre
        for (i=0; i<8; i++)
            if (tab[i][j] == '.')
                tab[i][j] = '*';
            else if (tab[i][j] == 'R')
                check = 1; //achou o Rei
    }

    /* Preenche tabuleiro diagonalmente */
    if (peca == 'b' || peca == 'r') { //bisco e rainha se movem diagonalmente

        i = posicao_peca[0]; //coordena i da rainha ou torre
        j = posicao_peca[1]; //coordena j da rainha ou torre

        //acha posi��o inicial para percorrer o tabuleiro
        if (i<j) {
            j = j - i;
            i = 0;
        } else {
            i = i - j;
            j = 0;
        }

        //preenche primeira diagonal
        while (i<8 && j<8) {
            if (tab[i][j] == '.')
                tab[i][j] = '*';
            else if (tab[i][j] == 'R')
                check = 1; //achou o Rei

            //avan�a para a pr�xima posi��o
            i++;
            j++;
        }

        i = posicao_peca[0]; //coordena i da rainha ou torre
        j = posicao_peca[1]; //coordena j da rainha ou torre

        //acha posi��o inicial para percorrer o tabuleiro
        if (i<(7-j)) {
            j = j + i;
            i = 0;
        } else {
            i = i - (7-j);
            j = 7;
        }

        //preenche segunda diagonal
        while (i<8 && j>=0) {
            if (tab[i][j] == '.')
                tab[i][j] = '*';
            else if (tab[i][j] == 'R')
                check = 1; //achou o Rei

            //avan�a para a pr�xima posi��o
            i++;
            j--;
        }

    }

    //imprime tabuleiro
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++)
            printf("%c", tab[i][j]);
        printf("\n");
    }

    if (check == 1)
        printf("O Rei esta em check!\n");
    else
        printf("O Rei nao esta em check!\n");

    return 0;
}
