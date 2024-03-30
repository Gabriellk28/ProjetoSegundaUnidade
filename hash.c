#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10007
#define MAX_TENTATIVAS 1000 // Número máximo de tentativas de sondagem

typedef struct pessoa {
    char nome[31];
    char telefone[21];
    char email[41];
} Pessoa;

void inicializarTabelaHash(Pessoa *tabela[N]) {
    for (int i = 0; i < N; i++) {
        tabela[i] = NULL;
    }
}

int hash(char *chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % N;
}

int sondagemQuadratica(int indice, int i) {
    return (indice + i * i) % N;
}

void inserirNaTabelaHash(Pessoa *tabela[N], char *nome, char *telefone, char *email) {
    int indice = hash(nome);
    int i = 0;
    
    while (tabela[indice] != NULL && i < N) {
        indice = sondagemQuadratica(indice, i);
        i++;
    }

    if (i == N) {
        fprintf(stderr, "Erro: Tabela hash cheia.\n");
        exit(1);
    }

    tabela[indice] = (Pessoa *)malloc(sizeof(Pessoa));
    if (tabela[indice] == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }
    strcpy(tabela[indice]->nome, nome);
    strcpy(tabela[indice]->telefone, telefone);
    strcpy(tabela[indice]->email, email);
}


void extrairDadosArquivo(char *nome_arquivo, Pessoa *tabela[N]) {
    // Variáveis para armazenar temporariamente os dados
    char nome[31], telefone[21], email[41];
    // Variável para armazenar a linha lida do arquivo
    char linha[100];

    // Abrindo o arquivo
    FILE *arquivo = fopen(nome_arquivo, "r");

    // Verificando se houve erro ao abrir o arquivo
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Loop para ler cada linha do arquivo até o final
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
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
            // Inserindo na tabela hash
            inserirNaTabelaHash(tabela, nome, telefone, email);
        }
    }
    
    // Fechando o arquivo
    fclose(arquivo);
}

//Função para imprimir a tabela
void imprimirTabelaHash(Pessoa *tabela[N]) {
    for (int i = 0; i < N; i++) {
        if (tabela[i] != NULL) {
            printf("Índice %d:\n", i);
            printf("Nome: %s\n", tabela[i]->nome);
            printf("Telefone: %s\n", tabela[i]->telefone);
            printf("Email: %s\n", tabela[i]->email);
            printf("\n");
        }
    }
}

int main(void)
{
  Pessoa *tabela[N];
  int opcao;

  inicializarTabelaHash(tabela);

  do
  {
    // Menu de opções
    printf("1 - Extrair dados do arquivo\n");
    printf("2 - Imprimir tabela hash\n");
    printf("3 - Buscar contato\n");
    printf("4 - Sair\n");
    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);
  }
    switch (opcao)
    {
    case 1:
      extrairDadosArquivo("todosOsContatos.txt", tabela);
      break;
    case 2:
      imprimirTabelaHash(tabela);
      break;
    case 3:
      printf("Saindo do programa...\n");
      break;
    case 4:
      char telefone[21];
      printf("Digite o telefone do contato a ser buscado: ");
      scanf("%s", telefone);

      Pessoa *contato = buscarNaTabelaHash(tabela, telefone);

      if (contato != NULL) {
        printf("Nome: %s\n", contato->nome);
        printf("Telefone: %s\n", contato->telefone);
        printf("Email: %s\n", contato->email);
      } else {
        printf("Contato não encontrado.\n");
      }
      break;

  } while (opcao != 3);
}
   default:
    
gi
