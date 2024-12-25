#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char nome[50];
    float quantidade;
    char unidade[10];
    float valor;
    int posicaox;
    int posicaoy;
} Produto;
/*
void salvarProdutosCSV(Produto *produtos, int total, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo CSV");
        return;
    }

    fprintf(arquivo, "codigo,nome,quantidade,unidade,valor,posicaox,posicaoy\n");
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%d,%s,%.2f,%s,%.2f,%d,%d\n", 
                produtos[i].codigo, produtos[i].nome, produtos[i].quantidade, 
                produtos[i].unidade, produtos[i].valor, 
                produtos[i].posicaox, produtos[i].posicaoy);
    }
    fclose(arquivo);*/
}
