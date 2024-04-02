#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 10007
#define M 7500

typedef struct pessoa 
{
    char nome[31];
    char telefone[21];
    char email[41];
} Pessoa;

void inicializarTabelaHash(Pessoa *tabela[N]) 
{
    for(int i = 0; i < N; i++){
        tabela[i] = NULL;
    }
}

int hash(char *chave) 
{
    int soma = 0;
    for(int i = 0; chave[i] != '\0'; i++){
        soma += chave[i];
    }
    return soma % N;
}

int sondagemQuadratica(int indice, int i){
    return (indice + i * i) % N;
}

void inserirNaTabelaHash(Pessoa *tabela[N], char *nome, char *telefone, char *email) 
{
    int indice = hash(nome);
    int i = 0;

    while(tabela[indice] != NULL && i < N){
        indice = sondagemQuadratica(indice, i);
        i++;
    }

    if(i == N){
        fprintf(stderr, "Erro: Tabela hash cheia.\n\n");
        exit(1);
    }

    tabela[indice] = (Pessoa *)malloc(sizeof(Pessoa));
    if(tabela[indice] == NULL){
        fprintf(stderr, "Erro ao alocar memória.\n\n");
        exit(1);
    }

    strcpy(tabela[indice]->nome, nome);
    strcpy(tabela[indice]->telefone, telefone);
    strcpy(tabela[indice]->email, email);
}

void extrairDadosArquivo(char *nome_arquivo, Pessoa *tabela[N]) 
{
    char nome[31], telefone[21], email[41];
    char linha[100];
    int linhas_extraias = 0;

    FILE *arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        fprintf(stderr, "Erro ao abrir o arquivo.\n\n");
        exit(1);
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL && linhas_extraias < M){
        if(strstr(linha, "Nome: ") != NULL){
            sscanf(linha, "Nome: %[^\n]", nome);
        }
        else if(strstr(linha, "Telefone: ") != NULL){
            sscanf(linha, "Telefone: %[^\n]", telefone);
        }
        else if(strstr(linha, "Email: ") != NULL){
            sscanf(linha, "Email: %[^\n]", email);
            inserirNaTabelaHash(tabela, nome, telefone, email);
            linhas_extraias++;
        }
    }

    fclose(arquivo);
}

void contarContatos(Pessoa *tabela[N]) 
{
    int quantidade = 0;

    for(int i = 0; i < N; i++){
        if (tabela[i] != NULL){
            quantidade++;
        }
    }

    printf("Quantidade de Contatos: %d\n\n", quantidade);
}

void imprimirTabelaHash(Pessoa *tabela[N])
{
    for(int i = 0; i < N; i++){
        if (tabela[i] != NULL) {
            printf("Índice %d:\n", i);
            printf("Nome: %s\n", tabela[i]->nome);
            printf("Telefone: %s\n", tabela[i]->telefone);
            printf("Email: %s\n", tabela[i]->email);
            printf("\n");
        }
    }
}

Pessoa *buscarContato(Pessoa *tabela[N], int opcao, char *string) 
{
    switch(opcao){
    case 1: // Buscar pelo nome
        for(int i = 0; i < N; i++){
            if(tabela[i] != NULL && strcmp(tabela[i]->nome, string) == 0){
                printf("Pessoa encontrada:\n");
                printf("Nome: %s\n", tabela[i]->nome);
                printf("Telefone: %s\n", tabela[i]->telefone);
                printf("Email: %s\n", tabela[i]->email);
                return tabela[i];
            }
        }
        break;

    case 2: // Buscar pelo telefone
        for(int i = 0; i < N; i++){
            if(tabela[i] != NULL && strcmp(tabela[i]->telefone, string) == 0){
                printf("Pessoa encontrada:\n");
                printf("Nome: %s\n", tabela[i]->nome);
                printf("Telefone: %s\n", tabela[i]->telefone);
                printf("Email: %s\n", tabela[i]->email);
                return tabela[i];
            }
        }
        break;

    case 3: // Buscar pelo email
        for(int i = 0; i < N; i++){
            if (tabela[i] != NULL && strcmp(tabela[i]->email, string) == 0){
                printf("Pessoa encontrada:\n");
                printf("Nome: %s\n", tabela[i]->nome);
                printf("Telefone: %s\n", tabela[i]->telefone);
                printf("Email: %s\n", tabela[i]->email);
                return tabela[i];
            }
        }
        break;

    default:
        printf("Opção inválida.\n\n");
        return NULL;
    }

    printf("Contato não encontrado.\n\n");
    return NULL;
}

void inserirContato(Pessoa *tabela[N]) 
{
    char nome[31], telefone[21], email[41];

    printf("Informe o Nome: ");
    scanf(" %[^\n]", nome);
    printf("Informe o Telefone: ");
    scanf(" %[^\n]", telefone);
    printf("Informe o e-mail: ");
    scanf(" %[^\n]", email);
    inserirNaTabelaHash(tabela, nome, telefone, email);
    printf("Contato Inserir com Sucesso.\n\n");
}

void removerContato(Pessoa *tabela[N], char *string)
{
    for(int i = 0; i < N; i++){
        if(tabela[i] != NULL && strcmp(tabela[i]->nome, string) == 0){
            free(tabela[i]);
            tabela[i] = NULL;
            printf("Contato removido com sucesso.\n\n");
            return;
        }
    }
    printf("Contato não encontrado para remoção.\n\n");
}

int verificaString(char string[])
{
    if(strlen(string) != 1 || !isdigit(string[0])){
        printf("Entrada Inválida.\n\n");
        return -1;
    }
    return atoi(string);
}

void imprimirMenu(int tipoMenu)
{
    if(tipoMenu == 1){
        printf("Menu de Opções:\n");
        printf("[1] - Ver o Total de Contatos\n");
        printf("[2] - Imprimir Contatos\n");
        printf("[3] - Buscar Contato\n");
        printf("[4] - Inserir Contato\n");
        printf("[5] - Remover Contato\n");
        printf("[6] - Sair\n");
    } else if(tipoMenu == 2){
        printf("Digite uma opção:\n");
        printf("[1] - Buscar Pelo Nome\n");
        printf("[2] - Buscar Pelo Telefone\n");
        printf("[3] - Buscar Pelo Email\n");
    }
}


int main(void)
{
    Pessoa *tabela[N];
    int opcao1 = 0, opcao2 = 0;
    char entrada[100], busca[100];

    inicializarTabelaHash(tabela);
    extrairDadosArquivo("todosOsContatos.txt", tabela);

    do{
        imprimirMenu(1);

        do{
            scanf(" %[^\n]", entrada);
            opcao1 = verificaString(entrada);
            if(opcao1 == -1){
                imprimirMenu(1);
            }
        }while(opcao1 == -1);

        switch(opcao1){
            case 1:
                contarContatos(tabela);
                break;

            case 2:
                imprimirTabelaHash(tabela);
                break;

            case 3:
                imprimirMenu(2);

                do{
                    scanf(" %[^\n]", busca);
                    opcao2 = verificaString(busca);
                    if(opcao1 == -1){
                        imprimirMenu(1);
                    }
                }while(opcao2 == -1);

                switch(opcao2){
                    case 1:
                        printf("Digite a informação a ser buscada: ");
                        scanf(" %[^\n]", entrada);
                        buscarContato(tabela, opcao2, entrada);
                    case 2:
                        printf("Digite a informação a ser buscada: ");
                        scanf(" %[^\n]", entrada);
                        buscarContato(tabela, opcao2, entrada);
                    case 3:
                        printf("Digite a informação a ser buscada: ");
                        scanf(" %[^\n]", entrada);
                        buscarContato(tabela, opcao2, entrada);
                        break;
                    default:
                        if(opcao2 != 1 && opcao2 != 2 && opcao2 != 3){
                            printf("Entrada Inválida.\n\n");
                        }
                }
                break;

            case 4:
                inserirContato(tabela);
                break;

            case 5:
                printf("Informe o nome do contato a ser removido: ");
                scanf(" %[^\n]", entrada);
                removerContato(tabela, entrada);
                break;

            case 6:
                printf("Programa Finalizado.\n");
                break;

            default:
                if(opcao1 != 6){
                    printf("Entrada Inválida.\n\n");
                }
        }
    } while (opcao1 != 6);

    return 0;
}
