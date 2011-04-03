/*  UNICAMP - Universidade Estadual de Campinas
    MC102 - Algoritmos e Programa��o de Computadores
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laborat�rio 03 - Jogo da Senha  */
    
#include <stdio.h>
#include <stdlib.h>

int main () {
    int i, j, k;
    int palpite[5], senha[5];
    int acertos = 0;

    
    scanf("%1d %1d %1d %1d %1d", &senha[0], &senha[1], &senha[2], &senha[3], &senha[4]);
    
    // Pula 50 linhas para que o jogador n�o saiba o n�mero a ser adivinhado
    for(j = 0; j < 50; j++)
        printf("\n");
    
    // Sempre que o jogador der um palpite errado o jogo aguardar� um novo palpite como entrada
    while(acertos != 5)
    {
        acertos = 0;  //zera para come�ar novo palpite
        scanf("%1d %1d %1d %1d %1d", &palpite[0], &palpite[1], &palpite[2], &palpite[3], &palpite[4]);
        for(i=0; i<5; i++)
        {
            for(k=0; k<5; k++)
            {
                if(palpite[i] == senha[k])
                {
                    if(i == k) {
                        printf("x");
                        acertos++;

                    } else
                        printf("o");
                }
            }
        }
        printf("\n");
    }
    
    // O jogo termina quando o jogador acerta o palpite
    printf("PARABENS!Voce encontrou a senha!");
        
    system("pause");
        
    return 0;
}
