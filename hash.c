#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 10007
#define M 7500
#define MAX_TENTATIVAS 1000 // Número máximo de tentativas de sondagem

typedef struct pessoa
{
    char nome[31];
    char telefone[21];
    char email[41];
} Pessoa;

//Função para bloquear caracteres estranhos no menu de opções
int verificaNumeros(char string[2])
{
    int i;
    for(i = 0; i < strlen(string); i++){
        if (!isdigit(string[i])) {
            printf("Entrada Inválida\n");
            return 0;
        }
    }
    return 1;
}

void inicializarTabelaHash(Pessoa *tabela[N])
{
    for (int i = 0; i < N; i++)
    {
        tabela[i] = NULL;
    }
}

int hash(char *chave)
{
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++)
    {
        soma += chave[i];
    }
    return soma % N;
}

int sondagemQuadratica(int indice, int i)
{
    return (indice + i * i) % N;
}

void inserirNaTabelaHash(Pessoa *tabela[N], char *nome, char *telefone, char *email)
{
    int indice = hash(nome);
    int i = 0;

    while (tabela[indice] != NULL && i < N)
    {
        indice = sondagemQuadratica(indice, i);
        i++;
    }

    if (i == N)
    {
        fprintf(stderr, "Erro: Tabela hash cheia.\n");
        exit(1);
    }

    tabela[indice] = (Pessoa *)malloc(sizeof(Pessoa));
    if (tabela[indice] == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }
    strcpy(tabela[indice]->nome, nome);
    strcpy(tabela[indice]->telefone, telefone);
    strcpy(tabela[indice]->email, email);
}

void extrairDadosArquivo(char *nome_arquivo, Pessoa *tabela[N])
{
    // Variáveis para armazenar temporariamente os dados
    char nome[31], telefone[21], email[41];
    // Variável para armazenar a linha lida do arquivo
    char linha[100];
    int linhas_extraias = 0;

    // Abrindo o arquivo
    FILE *arquivo = fopen(nome_arquivo, "r");

    // Verificando se houve erro ao abrir o arquivo
    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Loop para ler cada linha do arquivo até o final ou extrair 75%
    while (fgets(linha, sizeof(linha), arquivo) != NULL && linhas_extraias < M)
    {
        // Verificando se a linha começa com "Nome: "
        if (strstr(linha, "Nome: ") != NULL)
        {
            sscanf(linha, "Nome: %[^\n]", nome);
        }
        // Verificando se a linha começa com "Telefone: "
        else if (strstr(linha, "Telefone: ") != NULL)
        {
            sscanf(linha, "Telefone: %[^\n]", telefone);
        }
        // Verificando se a linha começa com "Email: "
        else if (strstr(linha, "Email: ") != NULL)
        {
            sscanf(linha, "Email: %[^\n]", email);
            // Inserindo na tabela hash
            inserirNaTabelaHash(tabela, nome, telefone, email);
            linhas_extraias++;
        }
    }

    // Fechando o arquivo
    fclose(arquivo);
}

// Função para contar o total de contatos na tabela
void contarContatos(Pessoa *tabela[N])
{
    int quantidade = 0;

    for (int i = 0; i < N; i++)
    {
        if (tabela[i] != NULL)
        {
            quantidade++;
        }
    }

    printf("Quantidade de Contatos: %d\n", quantidade);
}

// Função para imprimir a tabela
void imprimirTabelaHash(Pessoa *tabela[N])
{
    for (int i = 0; i < N; i++)
    {
        if (tabela[i] != NULL)
        {
            printf("Índice %d:\n", i);
            printf("Nome: %s\n", tabela[i]->nome);
            printf("Telefone: %s\n", tabela[i]->telefone);
            printf("Email: %s\n", tabela[i]->email);
            printf("\n");
        }
    }
}

Pessoa *buscarNaTabelaHash(Pessoa *tabela[N], char pesquisa)
{
  int indice = hash(pesquisa.chave);

  while (indice < N && tabela[indice] != NULL)
  {
    switch (pesquisa.tipo) {
      case NOME:
        if (strcmp(tabela[indice]->nome, (char *)pesquisa.chave) == 0) {
          return tabela[indice];
        }
        break;
      case TELEFONE:
        if (strcmp(tabela[indice]->telefone, (char *)pesquisa.chave) == 0) {
          return tabela[indice];
        }
        break;
      case EMAIL:
        if (strcmp(tabela[indice]->email, (char *)pesquisa.chave) == 0) {
          return tabela[indice];
        }
        break;
    }

    indice++;
  }

  return NULL;
}

// Função para inserir um novo contato na tabela
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
}

int main(void)
{
    Pessoa *tabela[N];
    int opcao;
    char veirificacao[2];

    inicializarTabelaHash(tabela);
    extrairDadosArquivo("todosOsContatos.txt", tabela);

    do
    {
        // Menu de opções
        printf("Menu de Opções:\n");
        printf("[1] - Ver Total de Contatos\n");
        printf("[2] - Imprimir Contatos\n");
        printf("[3] - Buscar Contato\n");
        printf("[4] - Inserir Contato\n");
        printf("[5] - Remover Contato\n");
        printf("[6] - Sair\n");
        
        scanf("%c", &veirificacao);


        switch (opcao)
        {
        case 1:
            contarContatos(tabela);
            break;

        case 2:
            imprimirTabelaHash(tabela);
            break;

        case 3:
            char telefone[21];

            printf("Digite o telefone do contato a ser buscado: ");
            scanf("%s", telefone);

            Pessoa *contato = buscarNaTabelaHash(tabela, telefone);

            if (contato != NULL)
            {
                printf("Nome: %s\n", contato->nome);
                printf("Telefone: %s\n", contato->telefone);
                printf("Email: %s\n", contato->email);
            }
            else
            {
                printf("Contato não encontrado.\n");
            }
            break;

        case 4:
            printf("Inserir Contato...\n");
            inserirContato(tabela);
            break;

        case 5:
            printf("Remover Contato...\n");
            // Adicione aqui a lógica para remover um contato existente
            break;

        case 6:
            printf("Programa Finalizado.\n");
            break;

        default:
            // Informa o usuário sobre a entrada errada
            if (opcao != 6)
            {
                printf("Opção Inválida.\n");
            }
        } // fim do switch
    } while (opcao != 6); // fim do do-while

    return 0;
}
