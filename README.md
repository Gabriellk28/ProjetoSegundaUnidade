## ProjetoSegundaUnidade

**Estrutura dos dados:**

* **Pessoa:** Essa estrutura define um tipo de dado chamado "Pessoa", que possui três campos:
    * **nome:** Uma string que armazena o nome da pessoa (até 30 caracteres).
    * **telefone:** Uma string que armazena o número de telefone da pessoa (até 20 caracteres).
    * **email:** Uma string que armazena o endereço de email da pessoa (até 40 caracteres).

* **Tabela Hash:** A tabela hash é um vetor de ponteiros para "Pessoa". Cada índice do vetor representa uma posição na tabela hash. O código usa sondagem quadrática para lidar com colisões.

**Funções:**

* **inicializarTabelaHash:** Esta função inicializa a tabela hash com `NULL` em todas as posições.

* **hash:** Esta função calcula o índice da tabela hash para uma string usando um algoritmo de soma simples.

* **sondagemQuadratica:** Esta função gera uma sequência de índices para sondagem quadrática. A sequência é calculada com a fórmula `(indice + i * i) % N`, onde `i` é a tentativa atual e `N` é o tamanho da tabela hash.

* **inserirNaTabelaHash:** Esta função insere uma nova "Pessoa" na tabela hash. A função primeiro calcula o índice da tabela hash para o nome da pessoa. Se a posição estiver vazia, a nova "Pessoa" é alocada e inserida na posição. Se a posição estiver ocupada, a função usa sondagem quadrática para encontrar a próxima posição vazia.

* **extrairDadosArquivo:** Esta função lê dados de um arquivo texto chamado "todosOsContatos.txt". O arquivo deve conter informações sobre cada contato, uma por linha, no seguinte formato:

```
Nome: <nome>
Telefone: <telefone>
Email: <email>
```

A função lê cada linha do arquivo e insere os dados na tabela hash.

* **contarContatos:** Esta função percorre a tabela hash e conta o número de posições que não são `NULL`.

* **imprimirTabelaHash:** Esta função percorre a tabela hash e imprime as informações de cada "Pessoa" que não seja `NULL`.

* **buscarNaTabelaHash:** Esta função busca uma "Pessoa" na tabela hash pelo seu número de telefone. A função calcula o índice da tabela hash para o telefone e percorre a sequência de sondagem quadrática até encontrar a "Pessoa" com o telefone especificado ou até chegar a um `NULL`.

* **inserirContato:** Esta função pede ao usuário o nome, telefone e email de um novo contato e o insere na tabela hash.

* **verificaNumeros:** Esta função verifica se uma string contém apenas números. A função é usada para validar o telefone.
  
* `removerContato(Pessoa *tabela[N], char *string)`: Remove um contato da tabela hash pelo nome (a implementar).

**Menu de opções:**

O programa apresenta um menu de opções ao usuário, permitindo que ele realize as seguintes ações:

* **Ver Total de Contatos:** Mostra a quantidade de contatos armazenados na tabela hash.

* **Imprimir Contatos:** Imprime as informações de todos os contatos na tabela hash.

* **Buscar Contato:** Permite que o usuário digite um número de telefone e, se encontrado, exibe as informações do contato.

* **Inserir Contato:** Permite que o usuário digite os dados de um novo contato e o insere na tabela hash.

* **Remover Contato:** 

* **Sair:** Encerra o programa.

**Observações:**



