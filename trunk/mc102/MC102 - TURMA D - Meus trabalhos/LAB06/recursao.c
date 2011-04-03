/*  UNICAMP - Universidade Estadual de Campinas
    MC102 - Algoritmos e Programacao de Computadores
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laboratorio 06 - Recursao */

#include <stdio.h>

// Funcao que calcula o fatorial de um numero
long long int Fatorial(long long int m){
  if(m == 0)
    return 1;
  else
    return m * Fatorial(m - 1);
}

// Funcao que encontra o valor de um elemento da sequencia de fibonacci
long long int Fibonacci(long long int n){
  if(n == 0)
    return 0;
  else{
    if(n == 1)
      return 1;
    else
      return (Fibonacci(n - 1) + Fibonacci(n - 2));
  }
}

// Funcao que encontra o maximo divisor comum de dois numeros
long long int MDC(long long int m, long long int n){
  if(m % n == 0)
    return n;
  else
    return MDC(n, m%n);
}

// Inicializacao do programa
int main(){
  long long int m, n, fib, fat, mdc;
  scanf("%lld", &m);
  getchar();
  scanf("%lld", &n);

  fat = Fatorial(m);
  printf("Fatorial(%lld): %lld\n", m, fat);

  fib = Fibonacci(n);
  printf("Fibonacci(%lld): %lld\n", n, fib);

  // O mdc de dois numeros eh calculado colocando-os na ordem do maior para o menor
  if(fat > fib)
    mdc = MDC(fat, fib);
  else
    mdc = MDC(fib, fat);
  printf("MDC: %lld\n", mdc);

  return 0;
}
