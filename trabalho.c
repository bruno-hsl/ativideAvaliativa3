#include <stdio.h>
#include <stdlib.h>

typedef struct Produto {
    int codigo;
    char descricao[50];
    int quantidade;
    float valor;
    struct Produto* prox;
} Produto;

Produto* inicializarLista() {
    return NULL;
}

Produto* criarProduto() {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    if (novoProduto == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    novoProduto->prox = NULL;
    return novoProduto;
}

Produto* adicionarProduto(Produto* estoque) {
    Produto* novoProduto = criarProduto();

    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto->codigo);

    printf("Digite a descricao do produto: ");
    scanf("%s", novoProduto->descricao);

    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Digite o valor do produto: ");
    scanf("%f", &novoProduto->valor);

    novoProduto->prox = estoque;
    return novoProduto;
}

void imprimirRelatorio(Produto* estoque) {
    if (estoque == NULL) {
        printf("Estoque vazio.\n");
        return;
    }

    Produto* atual = estoque;
    while (atual != NULL) {
        printf("Codigo: %d\n", atual->codigo);
        printf("Descricao: %s\n", atual->descricao);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Valor: %.2f\n\n", atual->valor);
        atual = atual->prox;
    }
}

Produto* pesquisarProduto(Produto* estoque, int codigo) {
    Produto* atual = estoque;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

Produto* removerProduto(Produto* estoque, int codigo) {
    Produto *anterior = NULL, *atual = estoque;

    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior != NULL) {
            anterior->prox = atual->prox;
        } else {
            estoque = atual->prox;
        }
        free(atual);
        printf("Produto removido com sucesso.\n");
    } else {
        printf("Produto nao encontrado.\n");
    }

    return estoque;
}

void liberarEstoque(Produto* estoque) {
    Produto* atual = estoque;
    Produto* proximoProduto;

    while (atual != NULL) {
        proximoProduto = atual->prox;
        free(atual);
        atual = proximoProduto;
    }
}

int main() {
    int opcao, codigoBusca;
    Produto* estoque = inicializarLista();
    Produto* encontrado;

    do {
        printf("\n1 - Cadastrar Produto\n");
        printf("2 - Imprimir Relatorio\n");
        printf("3 - Pesquisar Produto\n");
        printf("4 - Remover Produto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                estoque = adicionarProduto(estoque);
                break;
            case 2:
                imprimirRelatorio(estoque);
                break;
            case 3:
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigoBusca);
                encontrado = pesquisarProduto(estoque, codigoBusca);
                if (encontrado != NULL) {
                    printf("Produto encontrado:\n");
                    printf("Descricao: %s\n", encontrado->descricao);
                    printf("Quantidade: %d\n", encontrado->quantidade);
                    printf("Valor: %.2f\n", encontrado->valor);
                } else {
                    printf("Produto nao encontrado.\n");
                }
                break;
            case 4:
                printf("Digite o codigo do produto a ser removido: ");
                scanf("%d", &codigoBusca);
                estoque = removerProduto(estoque, codigoBusca);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarEstoque(estoque);

    return 0;
}
