    /*UNICAMP - Universidade Estadual de Campinas
    MC102 - Algoritmos e Programação de Computadores
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratório 02 - Cálculo do dia da semana */

#include <stdio.h>

int main()
{
    int dia, mes, ano, seculo, anoeseculo, passo2, passo3, passo4, passo5, passo6, diadasemana;
    
    // Lê a data informada pelo usuário
    scanf("%d", &dia);
    scanf("%d", &mes);
    scanf("%d", &anoeseculo);
        
    // A variável "ano" representa os dois últimos dígitos do ano diditado na entrada
    ano = anoeseculo % 100;
    
    // A variável "seculo" representa os dois primeiros dígitos do ano digitado na entrada
    seculo = (anoeseculo - ano) / 100;
    
    switch (mes) {
           case 1:
           case 2:
                mes = mes + 10;
                ano = ano - 1;
                break;
           case 3:
           case 4:
           case 5:
           case 6:
           case 7:
           case 8:
           case 9:
           case 10:
           case 11:
           case 12:
                mes = mes - 2;
                break;
    }
    
    // Referente ao passo 1 listado nas orientações do Laboratório
    mes = (mes * 13 - 1) / 5;
    
    // Referente ao passo 2 listado nas orientações do Laboratório
    passo2 = ano / 4;
    
    // Referente ao passo 3 listado nas orientações do Laboratório
    passo3 = seculo / 4;
    
    // Referente ao passo 4 listado nas orientações do Laboratório
    passo4 = seculo * 2;
    
    // Referente ao passo 5 listado nas orientações do Laboratório
    passo5 = mes + passo2 + passo3 + dia + ano;
    
    // Referente ao passo 6 listado nas orientações do Laboratório
    passo6 = passo5 - passo4;
    
    // Referente ao passo 7 listado nas orientações do Laboratório
    diadasemana = passo6 % 7;
    
    if (diadasemana < 0)
           diadasemana = (diadasemana + 7) % 7;
           
    // Informa o dia da semana
    switch (diadasemana) {
           case 0:
                printf("domingo\n");
                break;
           case 1:
                printf("segunda-feira\n");
                break;
           case 2:
                printf("terca-feira\n");
                break;
           case 3:
                printf("quarta-feira\n");
                break;
           case 4:
                printf("quinta-feira\n");
                break;
           case 5:
                printf("sexta-feira\n");
                break;
           case 6:
                printf("sabado\n");
                break;
    }
    
    system("pause");
    
    return 0;
}
