/* Lista de Exercicios 6 - Lista Ligada - Problema 3 */

/* Para a resolucao deste exercicio adimitimos que Contato eh um registro que contem dois campos: nome e telefone***********
** "comeco" eh um apontador para minha lista de contatos; basicamente utilizamos a ideia de uma agenda telefonica (LAB08) */
typedef struct contato{
    char nome[40];
    int telefone;
    struct contato *prox;
} Contato;

/* Funcao que cria nos */
Contato* criaNo(char nome[], int telefone, Contato* prox){
    Contato* comeco;
    comeco = (Contato*)malloc(sizeof(Contato));
    strcpy(comeco->nome, nome);
    comeco->telefone = telefone;
    (*comeco).prox = prox;
    
    return comeco;
}

/* Funcao que insere um novo no em uma lista ligada ordenada em ordem decrescente */
void insereOrdenado(char novo_nome[], char novo_telefone, Contato** comeco){ /* A insercao pode ocorrer no comeco da lista */
    Contato *antes, *depois;
    depois = NULL; /* Inicializacao */

    if((*comeco) == NULL){ /* lista vazia */
        *comeco = criaNo(novo_nome, novo_telefone, *comeco);
        return;
    }
    else{
        depois = *comeco; /* A variavel "depois" tambem aponta para o inicio da lista */
        if(strcmp(novo_nome, (*comeco)->nome) > 0) /* Insere no comeco */
            *comeco = criaNo(novo_nome, novo_telefone, *comeco);
        
        else{ /* Insere no meio ou no final */
            while(depois != NULL && strcmp(novo_nome, (*depois).nome) < 0){
                antes = depois; /* "antes" apontara para o no que fica imediatamente antes do novo no */
                depois = depois->prox; /* "depois" apontara para o no que fica imediatamente depois do novo no */
            }
            ant->prox = criaNo(novo_nome, novo_telefone, depois);
        }
    }
}
