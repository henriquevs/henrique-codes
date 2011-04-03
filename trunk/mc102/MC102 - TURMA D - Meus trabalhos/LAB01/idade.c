#include <stdio.h>

/* UNICAMP - Universidade Estadual de Campinas
   MC102 - Algoritmos e Programação de Computadores
   Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
   Laboratório 01 - Cálculo da idade */

int main () 
{
	int dia, mes, ano, w, idade;
	int d; /* Dia de nascimento */
	int m; /* Mï¿½s de nascimento */
	int a; /* Ano de nascimento */
	
	// Data atual de comparaï¿½ï¿½o
        dia = 17;
	mes = 8;
	ano = 2010;
	
	// Lï¿½ a data de nascimento
        scanf("%d", &d);
	scanf("%d", &m);
	scanf("%d", &a);
	
        w = ano - a;
	
	// Verifica se jï¿½ fez aniversï¿½rio este ano
        if (mes - m > 0)
	   idade = w;
	else if (mes - m < 0)
           idade = w - 1;
        else if (dia - d < 0)
           idade = w - 1;
        else
           idade = w;
                
        // Imprime a idade atual
	
        printf("%d anos", idade);
		
	return 0;
}  
