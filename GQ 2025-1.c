#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

typedef struct {
    int codigo;
    char nome[50];
} Categoria;

typedef struct {
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria;
    int preco;
} Produto;

char* buscarNomeCategoria(int codProduto, Categoria vc[], int qtdCategorias) {
    int i;
    for (i = 0; i < qtdCategorias; i++) {
        if (vc[i].codigo == codProduto) {
            return vc[i].nome;
        }
    }
    return "Nao encontrada";
}

void cadastrarCategoria(Categoria v[], int *qtd) {
    int novo_codigo;
    int i;

    if (*qtd >= TAM) {
        printf("ERRO: Vetor de categorias cheio. Cadastro nao realizado.\n");
        return; 
    }

    printf("Digite o codigo da nova categoria: ");
    scanf("%d", &novo_codigo);

    for (i = 0; i < *qtd; i++) {
        if (v[i].codigo == novo_codigo) {
            printf("ERRO: Codigo de categoria ja existe. Cadastro nao realizado.\n");
            return;
        }
    }

    v[*qtd].codigo = novo_codigo;
    
    printf("Digite o nome da categoria: ");
    scanf("%s", v[*qtd].nome);

    (*qtd)++;
    printf("Categoria cadastrada com sucesso.\n");
}

void imprimirCategorias(Categoria v[], int qtd) {
    int i;
    
    if (qtd == 0) {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }

    printf("\n--- CATEGORIAS CADASTRADAS ---\n");
    printf("CODIGO | NOME\n");
    
    for (i = 0; i < qtd; i++) {
        printf("%6d | %s\n", v[i].codigo, v[i].nome);
    }
    printf("------------------------------\n");
}

void imprimirProdutos(Produto vP[], int qtdProdutos, Categoria vc[], int qtdCategorias) {
    int i;
    char* nomeCategoria;
    double precoFormatado;

    printf("\n--- PRODUTOS CADASTRADOS ---\n");

    for (i = 0; i < qtdProdutos; i++) {
        nomeCategoria = buscarNomeCategoria(vP[i].categoria, vc, qtdCategorias);

        precoFormatado = (double)vP[i].preco / 100.0;

        printf("\nCODIGO: %d\n", vP[i].codigo);
        printf("TITULO: %s\n", vP[i].titulo);
        printf("DESCRICAO: %s\n", vP[i].descricao);
        printf("CATEGORIA: %s\n", nomeCategoria);
        printf("PRECO: R$%.2f\n", precoFormatado); 
    }
}

void selectionSortPorDescricao(Produto v[], int qtd) {
    int i, j, min_idx;
    Produto temp;

    for (i = 0; i < qtd - 1; i++) {
        min_idx = i;
        
        for (j = i + 1; j < qtd; j++) {
            if (strcmp(v[j].descricao, v[min_idx].descricao) < 0) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            temp = v[i];
            v[i] = v[min_idx];
            v[min_idx] = temp;
        }
    }
    printf("Ordenacao por descricao concluida.\n");
}

int buscaBinariaPorDescricao(Produto v[], int qtd, char *x) {
    int inicio = 0;
    int fim = qtd - 1;
    int meio;
    int comparacao;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        
        comparacao = strcmp(v[meio].descricao, x);

        if (comparacao == 0) {
            return meio;
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return -1;
}

int main() {
    Categoria categorias[TAM];
    int qtdCategorias = 0;
    Produto produtos[TAM];
    int qtdProdutos = 0;
    int resultadoBusca;
    
    printf("--- Simulacao de Cadastro ---\n");

    categorias[qtdCategorias].codigo = 100;
    strcpy(categorias[qtdCategorias].nome, "Eletronicos");
    qtdCategorias++;
    
    categorias[qtdCategorias].codigo = 200;
    strcpy(categorias[qtdCategorias].nome, "Livros");
    qtdCategorias++;

    produtos[qtdProdutos].codigo = 1;
    strcpy(produtos[qtdProdutos].titulo, "Smartphone X");
    strcpy(produtos[qtdProdutos].descricao, "Dispositivo movel");
    produtos[qtdProdutos].categoria = 100;
    produtos[qtdProdutos].preco = 150099;
    qtdProdutos++;

    produtos[qtdProdutos].codigo = 2;
    strcpy(produtos[qtdProdutos].titulo, "O Senhor dos Aneis");
    strcpy(produtos[qtdProdutos].descricao, "Fantasia epica");
    produtos[qtdProdutos].categoria = 200;
    produtos[qtdProdutos].preco = 8000;
    qtdProdutos++;

    produtos[qtdProdutos].codigo = 3;
    strcpy(produtos[qtdProdutos].titulo, "Fone Bluetooth");
    strcpy(produtos[qtdProdutos].descricao, "Acessorio de audio");
    produtos[qtdProdutos].categoria = 100;
    produtos[qtdProdutos].preco = 30000;
    qtdProdutos++;

    imprimirCategorias(categorias, qtdCategorias);
    
    imprimirProdutos(produtos, qtdProdutos, categorias, qtdCategorias);

    selectionSortPorDescricao(produtos, qtdProdutos);
    printf("\nProdutos apos a ordenacao:\n");
    imprimirProdutos(produtos, qtdProdutos, categorias, qtdCategorias);

    printf("\n--- BUSCA BINARIA ---\n");
    char busca1[] = "Fantasia epica";
    resultadoBusca = buscaBinariaPorDescricao(produtos, qtdProdutos, busca1);
    if (resultadoBusca != -1) {
        printf("Busca por '%s' encontrada na posicao: %d\n", busca1, resultadoBusca);
    } else {
        printf("Busca por '%s' nao encontrada.\n", busca1);
    }
    
    char busca2[] = "Produto inexistente";
    resultadoBusca = buscaBinariaPorDescricao(produtos, qtdProdutos, busca2);
    if (resultadoBusca != -1) {
        printf("Busca por '%s' encontrada na posicao: %d\n", busca2, resultadoBusca);
    } else {
        printf("Busca por '%s' nao encontrada.\n", busca2);
    }

    return 0;
}
