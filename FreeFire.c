#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_ITENS 10

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

//representa a mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;


//CONTADOR DE OPERAÇÕES
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;


// Função inserirItem
// Adiciona um item na mochila, caso haja espaço disponível.
void inserirItemVetor(Item vetor[], int *tamanho) {
    printf("\n--- Inserir Item (Vetor) ---\n");

    printf("Nome: ");
    scanf("%s", vetor[*tamanho].nome);

    printf("Tipo: ");
    scanf("%s", vetor[*tamanho].tipo);

    printf("Quantidade: ");
    scanf("%d", &vetor[*tamanho].quantidade);

    (*tamanho)++;
}


// Função removerItem
// Remove um item buscando pelo nome (busca sequencial).
void removerItemVetor(Item vetor[], int *tamanho) {
    char nomeBusca[30];
    printf("\n--- Remover Item (Vetor) ---\n");
    printf("Nome do item: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < *tamanho; i++) {
        if (strcmp(vetor[i].nome, nomeBusca) == 0) {
            vetor[i] = vetor[*tamanho - 1];
            (*tamanho)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}


// Função listarItens
// Lista todos os itens cadastrados na mochila.
void listarVetor(Item vetor[], int tamanho) {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %s - %s - %d\n", i, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}


// Ordenação por nome 
void ordenarVetor(Item vetor[], int tamanho) {
    Item temp;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (strcmp(vetor[j].nome, vetor[j+1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}



// Busca sequencial no vetor
int buscarSequencialVetor(Item vetor[], int tamanho, char nome[]) {
    comparacoesSequencial = 0;

    for (int i = 0; i < tamanho; i++) {
        comparacoesSequencial++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}


// Busca binária no vetor
int buscarBinariaVetor(Item vetor[], int tamanho, char nome[]) {
    int inicio = 0, fim = tamanho - 1, meio;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        if (strcmp(vetor[meio].nome, nome) == 0)
            return meio;

        if (strcmp(nome, vetor[meio].nome) > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}


// Insere item na lista ligada
void inserirItemLista(No **lista) {
    No* novo = (No*)malloc(sizeof(No));
    printf("\n--- Inserir Item (Lista) ---\n");

    printf("Nome: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *lista;
    *lista = novo;
}

// Remove item da lista ligada
void removerItemLista(No **lista) {
    char nomeBusca[30];
    printf("\n--- Remover Item (Lista) ---\n");
    printf("Nome do item: ");
    scanf("%s", nomeBusca);

    No *anterior = NULL, *atual = *lista;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL)
                *lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

// Lista a lista encadeada
void listarLista(No *lista) {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    while (lista != NULL) {
        printf("%s - %s - %d\n",
            lista->dados.nome,
            lista->dados.tipo,
            lista->dados.quantidade
        );
        lista = lista->proximo;
    }
}

// Busca sequencial na lista ligada
No* buscarSequencialLista(No *lista, char nome[]) {
    comparacoesSequencial = 0;

    while (lista != NULL) {
        comparacoesSequencial++;
        if (strcmp(lista->dados.nome, nome) == 0)
            return lista;
        lista = lista->proximo;
    }
    return NULL;
}



// MAIN
int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
  Item mochilaVetor[100];
    int tamanhoVetor = 0;

    No *mochilaLista = NULL;

    int opcaoEstrutura, opcao;
    char nomeBusca[30];

    while (1) {
        printf("\n====== SISTEMA DE MOCHILA ======\n");
        printf("1 - Usar VETOR\n");
        printf("2 - Usar LISTA ENCADEADA\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcaoEstrutura);

        if (opcaoEstrutura == 0) break;

        printf("\n--- MENU ---\n");
        printf("1 - Inserir Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Buscar Sequencial\n");
        if (opcaoEstrutura == 1)
            printf("5 - Ordenar Vetor\n6 - Busca Binaria\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            if (opcaoEstrutura == 1)
                inserirItemVetor(mochilaVetor, &tamanhoVetor);
            else
                inserirItemLista(&mochilaLista);
            break;

        case 2:
            if (opcaoEstrutura == 1)
                removerItemVetor(mochilaVetor, &tamanhoVetor);
            else
                removerItemLista(&mochilaLista);
            break;

        case 3:
            if (opcaoEstrutura == 1)
                listarVetor(mochilaVetor, tamanhoVetor);
            else
                listarLista(mochilaLista);
            break;

        case 4:
            printf("Nome: ");
            scanf("%s", nomeBusca);

            if (opcaoEstrutura == 1) {
                int pos = buscarSequencialVetor(mochilaVetor, tamanhoVetor, nomeBusca);
                printf("Comparacoes: %d\n", comparacoesSequencial);
                if (pos >= 0)
                    printf("Item encontrado no vetor.\n");
                else
                    printf("Nao encontrado.\n");
            } else {
                No *p = buscarSequencialLista(mochilaLista, nomeBusca);
                printf("Comparacoes: %d\n", comparacoesSequencial);
                if (p)
                    printf("Item encontrado na lista.\n");
                else
                    printf("Nao encontrado.\n");
            }
            break;

        case 5:
            if (opcaoEstrutura == 1) {
                ordenarVetor(mochilaVetor, tamanhoVetor);
                printf("Vetor ordenado!\n");
            }
            break;

        case 6:
            if (opcaoEstrutura == 1) {
                printf("Nome: ");
                scanf("%s", nomeBusca);

                int pos = buscarBinariaVetor(mochilaVetor, tamanhoVetor, nomeBusca);

                printf("Comparacoes (binaria): %d\n", comparacoesBinaria);

                if (pos >= 0)
                    printf("Item encontrado!\n");
                else
                    printf("Nao encontrado.\n");
            }
            break;
        }
    }

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
