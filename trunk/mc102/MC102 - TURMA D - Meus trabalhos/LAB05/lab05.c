/*  UNICAMP - Universidade Estadual de Campinas
    MC102 - Algoritmos e Programa��o de Computadores
    Aluno: Henrique Vicente Souza - RA: 105063 - Turma D
    Laborat�rio 05 - Agenda Telef�nica */
    
#include <stdio.h>
#include <string.h>

/* Cria��o do registro contato */
typedef struct contato{
    char nome[150];
    int telefone;
} contato;

typedef enum{False, True} bool; // Usaremos compara��es booleanas para saber se a agenda est� ordenada

/* Estabelecimento da fun��o que ordena, por inser��o, os nomes que est�o gravados na agenda */
void ordenaNome(contato agenda[], int n_contatos){
    int i, j;
    contato aux;
    for(i = 1; i < n_contatos; i++){
        aux = agenda[i];
        for(j = i - 1; (j >= 0) && (strcmp(aux.nome,agenda[j].nome) < 0); j--){
            agenda[j + 1] = agenda[j];
        }
        agenda[j + 1] = aux;
    }
}

/* Estabelecimento da fun��o que busca nomes que est�o gravados na agenda atrav�s de busca bin�ria */
int buscaNome(contato agenda[], char nome[], int n_contatos){
    int inicio, fim, meio;
    inicio = 0;
    fim = n_contatos - 1;
    while(inicio <= fim){
        meio = (inicio + fim)/2;
        if(strcmp(nome,agenda[meio].nome) == 0)
            return meio;
        else{
            if(strcmp(nome,agenda[meio].nome) < 0)
                fim = meio - 1;
            else
                inicio = meio + 1;
        }
    }
    return -1;
}

/* Estabelecimento da fun��o que busca telefones que est�o gravados na agenda atrav�s de busca sequencial */
int buscaTelefone(contato agenda[], int telefone, int n_contatos){
    bool encontrado = False; // Telefone n�o encontrado
    int i = 0;
    while (i < n_contatos && !encontrado){
        if(telefone == agenda[i].telefone)
            encontrado = True; // O telefone procurado est� na agenda
        else
            i++;
    }    
    if (encontrado)
        return i;
    return -1;
}

/* Inicializa��o do programa */
int main(){
    int n_contatos = 0; // Conta o numero de contatos j� inseridos
    int resp, telefone_lido, i;
    contato agenda[70];
    char parametro, inicial;
    char nome_lido[150];
    bool ordenado = False; // Inicialmente a agenda n�o est� ordenada
        
    do{
        parametro = getchar();
        switch(parametro){
        case('i'): // Insere um novo contato na agenda
                getchar();
                scanf("%d", &(agenda[n_contatos].telefone));
                getchar();
                scanf("%[^\n]", agenda[n_contatos].nome);
                getchar();
                n_contatos++;
                ordenado = False;
                break;
            
        case('n'): // Busca um nome na agenda
                if(ordenado == False){
                    ordenaNome(agenda, n_contatos);
                    ordenado = True;
                }
                getchar();
                scanf("%[^\n]", nome_lido);
                getchar();
                resp = buscaNome(agenda, nome_lido, n_contatos);
                
                if(resp == -1)
                    printf("Contato nao encontrado!\n\n");
                else
                    printf("%-40s %d\n\n", agenda[resp].nome, agenda[resp].telefone);
                
                break;
                
        case('t'): // Busca um telefone na agenda
                getchar();
                scanf("%d", &telefone_lido);
                getchar();
                resp = buscaTelefone(agenda, telefone_lido, n_contatos);
                
                if(resp == -1)
                    printf("Contato nao encontrado!\n\n");
                else
                    printf("%-40s %d\n\n", agenda[resp].nome, agenda[resp].telefone);
                
                break;
                
        case('p'): // Faz a impress�o de todos os contatos em ordem alfab�tica
                if(ordenado == False){
                    ordenaNome(agenda, n_contatos);
                    ordenado = True;
                }
                if(n_contatos > 0){ // Se n�o existem contatos na agenda ent�o n�o � necess�rio imprimir
                    inicial = agenda[0].nome[0];
                    printf("----%c----\n", inicial);
                    for(i = 0; i < n_contatos; i++){
                        if(agenda[i].nome[0] == inicial)
                            printf("%-40s %d\n", agenda[i].nome, agenda[i].telefone);
                        else{
                            printf("----%c----\n", agenda[i].nome[0]);
                            inicial = agenda[i].nome[0];
                            printf("%-40s %d\n", agenda[i].nome, agenda[i].telefone);
                        }
                    }
                putchar('\n');
                }
                else
                    printf("\n");
                break;
        }
    } while(parametro != 'f');
    
    system("pause");
    
    return 0;
}
