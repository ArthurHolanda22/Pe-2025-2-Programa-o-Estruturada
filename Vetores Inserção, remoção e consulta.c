#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

void imprimir_vetor(int vetor[], int tamanho);
int busca_binaria(int vetor[], int tamanho, int valor);
void remover_elemento(int vetor[], int *tamanho, int valor);
void inserir_ordenado(int vetor[], int *tamanho, int valor);

int main() {
    int vetor[MAX_SIZE];
    int tamanho_atual = 0;
    int opcao, valor;

    do {
        printf("Digite o tamanho do vetor (entre 3 e %d elementos): ", MAX_SIZE);
        scanf("%d", &tamanho_atual);
    } while (tamanho_atual < 3 || tamanho_atual > MAX_SIZE);

    printf("\nDigite os %d valores inteiros para preencher o vetor (um de cada vez):\n", tamanho_atual);
    for (int i = 0; i < tamanho_atual; i++) {
        printf("Valor %d: ", i + 1);
        scanf("%d", &valor);
        inserir_ordenado(vetor, &i, valor);
    }
    printf("\nVetor inicial preenchido:\n");
    imprimir_vetor(vetor, tamanho_atual);

    do {
        printf("\n--- MENU DE OPCOES ---\n");
        printf("1. Imprimir todo o vetor\n");
        printf("2. Consultar um elemento (busca binaria)\n");
        printf("3. Remover um elemento\n");
        printf("4. Inserir 1 valor no vetor\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprimir_vetor(vetor, tamanho_atual);
                break;
            case 2:
                printf("Digite o valor a ser consultado: ");
                scanf("%d", &valor);
                int posicao = busca_binaria(vetor, tamanho_atual, valor);
                if (posicao != -1) {
                    printf("O valor %d se encontra na posicao %d.\n", valor, posicao);
                } else {
                    printf("O valor %d nao foi encontrado.\n", valor);
                }
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                remover_elemento(vetor, &tamanho_atual, valor);
                break;
            case 4:
                if (tamanho_atual < MAX_SIZE) {
                    printf("Digite o valor a ser inserido: ");
                    scanf("%d", &valor);
                    inserir_ordenado(vetor, &tamanho_atual, valor);
                    printf("Valor %d inserido com sucesso.\n", valor);
                } else {
                    printf("O vetor esta cheio. Nao e possivel inserir mais elementos.\n");
                }
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}

void imprimir_vetor(int vetor[], int tamanho) {
    if (tamanho == 0) {
        printf("O vetor esta vazio.\n");
        return;
    }
    printf("Vetor: [ ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("]\n");
}

int busca_binaria(int vetor[], int tamanho, int valor) {
    int inicio = 0;
    int fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (vetor[meio] == valor) {
            return meio;
        }
        if (vetor[meio] < valor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

void remover_elemento(int vetor[], int *tamanho, int valor) {
    int posicao = busca_binaria(vetor, *tamanho, valor);
    if (posicao == -1) {
        printf("Valor %d nao encontrado no vetor. Nenhuma acao foi realizada.\n", valor);
        return;
    }
    for (int i = posicao; i < *tamanho - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    (*tamanho)--;
    printf("Valor %d removido com sucesso.\n", valor);
}

void inserir_ordenado(int vetor[], int *tamanho, int valor) {
    int i;
    for (i = *tamanho - 1; i >= 0 && vetor[i] > valor; i--) {
        vetor[i + 1] = vetor[i];
    }
    vetor[i + 1] = valor;
    (*tamanho)++;
}
