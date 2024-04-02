#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 10007// Tamanho da tabela hash
#define M 7500// Número máximo de contatos a serem extraídos

typedef struct pessoa // Estrutura para armazenar os dados de um contato
{
    char nome[31];// Nome do contato
    char telefone[21];// Telefone do contato
    char email[41];// Email do contato
} Pessoa;

void inicializarTabelaHash(Pessoa *tabela[N])// Função para inicializar a tabela hash
{
    for(int i = 0; i < N; i++){ // Percorre todos os índices da tabela e seta para NULL
        tabela[i] = NULL;
    }
}

//Função hash para calcular o índice da chave
int hash(char *chave)
{
    int soma = 0, i = 0;
    while (chave[i] != '\0') { // Enquanto não chegarmos ao final da chave
        int parte = 0;
        // Somamos os próximos dígitos ASCII da chave para formar uma parte
        for (int j = 0; j < 4 && chave[i] != '\0'; j++, i++) {
            parte += chave[i];
        }
        // Adicionamos a parte à soma
        soma += parte;
    }
    return soma % N; // Retorna o módulo da soma pelo tamanho da tabela
}

int sondagemQuadratica(int indice, int i) // Função de sondagem quadrática para resolver colisões
{
    return(indice + i * i) % N;// Retorna o índice original + i^2 (i elevado ao quadrado)
}

void inserirNaTabelaHash(Pessoa *tabela[N], char *nome, char *telefone, char *email) // Função para inserir um novo contato na tabela hash
{
    int indice = hash(nome);// Calcula o índice inicial usando a função hash
    int i = 0;

    while(tabela[indice] != NULL && i < N){// Loop para encontrar um índice disponível na tabela
        indice = sondagemQuadratica(indice, i);// Se o índice estiver ocupado, tenta o próximo usando sondagem quadrática
        i++;
    }

    if(i == N){
        fprintf(stderr, "Erro: Tabela hash cheia.\n");// Se a tabela estiver cheia, exibe uma mensagem de erro
        exit(1);
    }

    tabela[indice] = (Pessoa *)malloc(sizeof(Pessoa)); // Aloca memória para o novo contato
    if(tabela[indice] == NULL){
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }

    strcpy(tabela[indice]->nome, nome); // Copia os dados para o novo contato
    strcpy(tabela[indice]->telefone, telefone);
    strcpy(tabela[indice]->email, email);
}

void extrairDadosArquivo(char *nome_arquivo, Pessoa *tabela[N]) // Função para extrair dados de um arquivo e inserir na tabela hash
{
    // Variáveis para armazenar temporariamente os dados
    char nome[31], telefone[21], email[41];
    // Variável para armazenar a linha lida do arquivo
    char linha[100];
    int linhasExtraias = 0;

    // Abrindo o arquivo
    FILE *arquivo = fopen(nome_arquivo, "r");

    // Verificando se houve erro ao abrir o arquivo
    if(arquivo == NULL){
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Loop para ler cada linha do arquivo até o final ou extrair 75%
    while(fgets(linha, sizeof(linha), arquivo) != NULL && linhasExtraias < M){
        // Verificando se a linha começa com "Nome: "
        if (strstr(linha, "Nome: ") != NULL) {
            sscanf(linha, "Nome: %[^\n]", nome);
        }
        // Verificando se a linha começa com "Telefone: "
        else if (strstr(linha, "Telefone: ") != NULL) {
            sscanf(linha, "Telefone: %[^\n]", telefone);
        }
        // Verificando se a linha começa com "Email: "
        else if (strstr(linha, "Email: ") != NULL) {
            sscanf(linha, "Email: %[^\n]", email);
            inserirNaTabelaHash(tabela, nome, telefone, email);
            linhasExtraias++;
        }
    }

    // Fechando o arquivo
    fclose(arquivo);
}

//Função para contar o total de contatos na tabela
void contarContatos(Pessoa *tabela[N]){
    int quantidade = 0;

    for(int i = 0; i < N; i++){// Percorre todos os índices da tabela
        if(tabela[i] != NULL){// Se o índice não está vazio
            quantidade++;// Incrementa o contador
        }
    }

    printf("Quantidade de Contatos: %d\n", quantidade); // Exibe a quantidade de contatos
}

//Função para imprimir a tabela
void imprimirTabelaHash(Pessoa *tabela[N]) // Imprime todos os contatos da tabela hash
{
    for(int i = 0; i < N; i++){// Percorre todos os índices da tabela
        if(tabela[i] != NULL){// Se o índice não está vazio
            printf("Índice %d:\n", i); // Exibe o índice e os dados do contato
            printf("Nome: %s\n", tabela[i]->nome);
            printf("Telefone: %s\n", tabela[i]->telefone);
            printf("Email: %s\n", tabela[i]->email);
            printf("\n");
        }
    }
}

Pessoa *buscarContato(Pessoa *tabela[N], int opcao, char *string) // Busca um contato na tabela hash por nome, telefone ou email
{
    switch(opcao)
    {
    case 1: // Buscar pelo nome
        for(int i = 0; i < N; i++) {
            if(tabela[i] != NULL && strcmp(tabela[i]->nome, string) == 0) {
                printf("Pessoa encontrada:\n");
                printf("Nome: %s\n", tabela[i]->nome);
                printf("Telefone: %s\n", tabela[i]->telefone);
                printf("Email: %s\n", tabela[i]->email);
                return tabela[i];
            }
        }
        break;

    case 2: // Buscar pelo telefone
        for(int i = 0; i < N; i++) {
            if(tabela[i] != NULL && strcmp(tabela[i]->telefone, string) == 0) {
                printf("Pessoa encontrada:\n");
                printf("Nome: %s\n", tabela[i]->nome);
                printf("Telefone: %s\n", tabela[i]->telefone);
                printf("Email: %s\n", tabela[i]->email);
                return tabela[i];
            }
        }
        break;

    case 3: // Buscar pelo email
        for(int i = 0; i < N; i++) {
            if(tabela[i] != NULL && strcmp(tabela[i]->email, string) == 0) {
                printf("Pessoa encontrada:\n");
                printf("Nome: %s\n", tabela[i]->nome);
                printf("Telefone: %s\n", tabela[i]->telefone);
                printf("Email: %s\n", tabela[i]->email);
                return tabela[i];
            }
        }
        break;

    default:
        printf("Opção inválida.\n");
        return NULL;
    }

    printf("Contato não encontrado.\n");
    return NULL;
}


// Função para inserir um novo contato na tabela
void inserirContato(Pessoa *tabela[N])
{
    char nome[31], telefone[21], email[41];

    printf("Informe o Nome: "); // Lê os dados do novo contato
    scanf(" %[^\n]", nome);
    printf("Informe o Telefone: ");
    scanf(" %[^\n]", telefone);
    printf("Informe o e-mail: ");
    scanf(" %[^\n]", email);

    inserirNaTabelaHash(tabela, nome, telefone, email);// Insere o contato na tabela hash
}

void removerContato(Pessoa *tabela[N], char *string)// Remove um contato da tabela hash
{
    for(int i = 0; i < N; i++) {// Percorre todos os índices da tabela
        if(tabela[i] != NULL && strcmp(tabela[i]->nome, string) == 0) { // Se o nome do contato na posição atual for igual ao nome buscado
            free(tabela[i]); // Libera a memória alocada para o contato
            tabela[i] = NULL;// Seta o ponteiro da tabela para NULL
            printf("Contato removido com sucesso.\n");
            return;
        }
    }
    printf("Contato não encontrado para remoção.\n");// Se o contato não foi encontrado
}

int main(void)
{
    Pessoa *tabela[N];
    int opcao1, opcao2; // Variáveis para armazenar a opção do usuário

    inicializarTabelaHash(tabela);// Inicializa a tabela hash
    extrairDadosArquivo("todosOsContatos.txt", tabela);// Extrai dados de um arquivo e insere na tabela hash

    do // Loop principal do programa
    {
        // Menu de opções
        printf("Menu de Opções:\n");
        printf("[1] - Ver o Total de Contatos\n");
        printf("[2] - Imprimir Contatos\n");
        printf("[3] - Buscar Contato\n");
        printf("[4] - Inserir Contato\n");
        printf("[5] - Remover Contato\n");
        printf("[6] - Sair\n");
        scanf(" %d", &opcao1);// Lê a opção do usuário

        switch(opcao1) // Switch para tratar as opções do menu
        {
        case 1:// Opção para contar o total de contatos
            contarContatos(tabela);
            break;

        case 2:// Opção para imprimir a tabela hash
            imprimirTabelaHash(tabela);
            break;

        case 3:// Opção para buscar um contato
            char string[41]; // Variável para armazenar a string de busca
            printf("Digite uma opção:\n");
            printf("[1] - Buscar Pelo Nome\n");
            printf("[2] - Buscar Pelo Telefone\n");
            printf("[3] - Buscar Pelo Email\n");
            scanf(" %d", &opcao2);
            printf("Digite a string de busca: ");
            scanf(" %[^\n]", string); 
            buscarContato(tabela, opcao2, string);
            break;

        case 4: // Opção para inserir um novo contato
            inserirContato(tabela);
            break;

        case 5:// Opção para remover um contato
            break;

        case 6: // Opção para sair do programa
            printf("Programa Finalizado.\n");
            break;

        default:
            if(opcao1 != 6){
                printf("Entrada Inválida.\n\n");
            }
        } // fim do switch
    } while (opcao1 != 6); // fim do do-while

    return 0;
}
