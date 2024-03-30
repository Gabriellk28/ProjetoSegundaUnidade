#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100

// Estrutura para representar um contato
typedef struct {
    char nome[100];
    char telefone[20];
    char email[100];
} Contato;

// Estrutura para representar um nó na lista encadeada
typedef struct No {
    Contato contato;
    struct No *prox;
} No;

// Função de hash simples
unsigned int hash(const char *chave) {
    unsigned int hash = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        hash = 31 * hash + chave[i];
    }
    return hash % HASH_SIZE;
}

// Função para criar um novo nó
No* criarNo(Contato contato) {
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->contato = contato;
        novoNo->prox = NULL;
    }
    return novoNo;
}

// Função para inserir um contato na tabela de dispersão
void inserir(No* tabela[], Contato contato) {
    unsigned int indice = hash(contato.nome);
    No *novoNo = criarNo(contato);

    if (novoNo == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    // Inserir na cabeça da lista
    novoNo->prox = tabela[indice];
    tabela[indice] = novoNo;
}

// Função para liberar a memória alocada para a tabela de dispersão
void liberarTabela(No* tabela[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        No *atual = tabela[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

// Função para imprimir um contato
void imprimirContato(Contato contato) {
    printf("Nome: %s\n", contato.nome);
    printf("Telefone: %s\n", contato.telefone);
    printf("Email: %s\n", contato.email);
    printf("\n");
}

// Função para imprimir toda a tabela de dispersão
void imprimirTabela(No* tabela[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        No *atual = tabela[i];
        while (atual != NULL) {
            imprimirContato(atual->contato);
            atual = atual->prox;
        }
    }
}

// Função principal
int main() {
    // Inicializar a tabela de dispersão
    No* tabela[HASH_SIZE] = {NULL};

    // Ler os contatos do arquivo e inseri-los na tabela de dispersão
    FILE *arquivo = fopen("todosOsContatos.txt", "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    Contato contato;
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strncmp(linha, "Nome:", 5) == 0) {
            strcpy(contato.nome, linha + 6);
            fgets(linha, sizeof(linha), arquivo);
            strcpy(contato.telefone, linha + 10);
            fgets(linha, sizeof(linha), arquivo);
            strcpy(contato.email, linha + 7);
            inserir(tabela, contato);
        }
    }

    fclose(arquivo);

    // Imprimir toda a tabela de dispersão
    printf("Tabela de Contatos:\n");
    imprimirTabela(tabela);

    // Liberar a memória alocada para a tabela de dispersão
    liberarTabela(tabela);

    return 0;
}
