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
struct Item {
    char nome[30];      
    char tipo[20];      
    int quantidade;     
};


// Função inserirItem
// Adiciona um item na mochila, caso haja espaço disponível.
void inserirItem(struct Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia! (Máximo: %d itens)\n", MAX_ITENS);
        return;
    }

    struct Item novo;

    printf("\n=== Cadastro de Item ===\n");

    printf("Nome do item: ");
    scanf(" %29[^\n]", novo.nome);

    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    scanf(" %19[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*total] = novo;  
    (*total)++;

    printf("\nItem adicionado com sucesso!\n");
}


// Função removerItem
// Remove um item buscando pelo nome (busca sequencial).
void removerItem(struct Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nNome do item a remover: ");
    scanf(" %29[^\n]", nomeRemover);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // move os itens seguintes para "fechar o buraco"
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;

            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}


// Função listarItens
// Lista todos os itens cadastrados na mochila.
void listarItens(struct Item mochila[], int total) {
    printf("\n=== Itens na Mochila ===\n");

    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}


// Função buscarItem
// Busca sequencial por nome e mostra os dados do item.
void buscarItem(struct Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nITEM ENCONTRADO!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado.\n");
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
 struct Item mochila[MAX_ITENS];
    int totalItens = 0;

    int opcao;

    do {
        printf("\n===============================\n");
        printf("     MOCHILA DO JOGADOR\n");
        printf("===============================\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(mochila, &totalItens); break;
            case 2: removerItem(mochila, &totalItens); break;
            case 3: listarItens(mochila, totalItens); break;
            case 4: buscarItem(mochila, totalItens); break;
            case 0: printf("\nEncerrando...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);


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
