#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

// Estrutura do produto
typedef struct {
    int codigo;
    char nome[51];
    float quantidade;
    char unidade[6];
    float valor;
    int posicaox;
    int posicaoy;
} Produto;

// Função para inserir um novo produto
void inserir_produto(Produto produtos[], int *total) {
    if (*total >= MAX_PRODUTOS) {
        printf("\nLimite maximo de produtos atingido!\n");
        return;
    }

    Produto novo;
    printf("\nDigite o codigo do produto (999 para encerrar): ");
    scanf("%d", &novo.codigo);

    if (novo.codigo == 999) return;

    printf("Digite o nome do produto: ");
    //scanf(" %50[^"]", novo.nome);
    
   //scanf(" %50[^\"]", novo.nome);

	scanf("%f", novo.nome);
    printf("Digite a quantidade: ");
    scanf("%f", &novo.quantidade);

    printf("Digite a unidade de medida: ");
    scanf("%5s", novo.unidade);

    printf("Digite o valor unitario: ");
    scanf("%f", &novo.valor);

    // Preenchimento automatico das posicoes
    novo.posicaox = (*total / 7) % 5; // Garantir limite de 0 a 4
    novo.posicaoy = (*total % 7);     // Garantir limite de 0 a 6

    produtos[*total] = novo;
    (*total)++;
}

// Função para exibir os produtos cadastrados
void exibir_produtos(Produto produtos[], int total) {
    printf("\nProdutos cadastrados:\n");
    for (int i = 0; i < total; i++) {
        printf("\nProduto %d:\n", i + 1);
        printf("  Codigo: %d\n", produtos[i].codigo);
        printf("  Nome: %s\n", produtos[i].nome);
        printf("  Quantidade: %.2f\n", produtos[i].quantidade);
        printf("  Unidade: %s\n", produtos[i].unidade);
        printf("  Valor: %.2f\n", produtos[i].valor);
        printf("  Posicao: Armario %d, Prateleira %d\n", produtos[i].posicaox, produtos[i].posicaoy);
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int total = 0;

    printf("\nBem-vindo ao sistema de gerenciamento de produtos!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir novo produto\n");
        printf("2. Exibir produtos cadastrados\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");

        int opcao;
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserir_produto(produtos, &total);
                break;
            case 2:
                exibir_produtos(produtos, total);
                break;
            case 3:
                printf("\nSaindo do sistema. Ate logo!\n");
                return 0;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}

