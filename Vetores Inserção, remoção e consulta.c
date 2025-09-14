#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

// Função para encontrar a posição correta para inserção ordenada
int encontrarPosicaoOrdenada(int arr[], int size, int valor) {
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] > valor) {
            return i;
        }
    }
    return size;
}

// Função para inserir um valor de forma ordenada
void inserirOrdenado(int arr[], int *size, int valor) {
    if (*size >= MAX_SIZE) {
        printf("\n\t>>> O vetor esta cheio. Nao e possivel inserir mais elementos.\n");
        return;
    }
    int pos = encontrarPosicaoOrdenada(arr, *size, valor);
    for (int i = *size; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = valor;
    (*size)++;
}

// Função de busca binária
int buscaBinaria(int arr[], int size, int alvo) {
    int esquerda = 0, direita = size - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (arr[meio] == alvo) {
            return meio;
        }
        if (arr[meio] < alvo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

// Função para imprimir o vetor
void imprimirVetor(int arr[], int size) {
    if (size == 0) {
        printf("\n\t>>> O vetor esta vazio.\n");
        return;
    }
    printf("\n\t--- Conteudo do vetor (tamanho %d) ---\n", size);
    for (int i = 0; i < size; i++) {
        printf("\t%d", arr[i]);
    }
    printf("\n\t--------------------------------------\n");
}

// Função para remover um elemento
void removerElemento(int arr[], int *size, int alvo) {
    int indice = buscaBinaria(arr, *size, alvo);
    if (indice != -1) {
        for (int i = indice; i < (*size) - 1; i++) {
            arr[i] = arr[i + 1];
        }
        (*size)--;
        printf("\n\t>>> Elemento %d removido com sucesso.\n", alvo);
    } else {
        printf("\n\t>>> Elemento %d nao encontrado.\n", alvo);
    }
}

// Função principal
int main() {
    int vetor[MAX_SIZE];
    int tamanhoAtual;
    int escolha, valor, numElementos;

    do {
        printf("Digite o tamanho do vetor (entre 3 e %d): ", MAX_SIZE);
        scanf("%d", &tamanhoAtual);
        if (tamanhoAtual < 3 || tamanhoAtual > MAX_SIZE) {
            printf("\n\t>>> Tamanho invalido. Tente novamente.\n\n");
        }
    } while (tamanhoAtual < 3 || tamanhoAtual > MAX_SIZE);
    
    do {
        printf("Digite a quantidade de valores inteiros para preencher o vetor (max %d): ", tamanhoAtual);
        scanf("%d", &numElementos);
        if (numElementos > tamanhoAtual) {
            printf("\n\t>>> A quantidade nao pode ser maior que o tamanho inicial do vetor.\n\n");
        }
    } while (numElementos > tamanhoAtual);
    
    int tempValor;
    int tamanhoInicial = 0;
    for (int i = 0; i < numElementos; i++) {
        printf("Digite o valor #%d: ", i + 1);
        scanf("%d", &tempValor);
        inserirOrdenado(vetor, &tamanhoInicial, tempValor);
    }
    tamanhoAtual = tamanhoInicial;
    printf("\n--- Vetor populado com sucesso. ---\n");

    do {
        printf("\n--- MENU DE OPCOES ---\n");
        printf("1. Imprimir todo o vetor\n");
        printf("2. Consultar um elemento (via busca binaria)\n");
        printf("3. Remover um elemento\n");
        printf("4. Inserir 1 valor no vetor\n");
        printf("0. Sair\n");
        printf("------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                imprimirVetor(vetor, tamanhoAtual);
                break;
            case 2:
                printf("\nDigite o valor que deseja buscar: ");
                scanf("%d", &valor);
                int indice = buscaBinaria(vetor, tamanhoAtual, valor);
                if (indice != -1) {
                    printf("\n\t>>> O elemento %d se encontra na posicao %d (indice %d).\n", valor, indice + 1, indice);
                } else {
                    printf("\n\t>>> O elemento %d nao foi encontrado.\n", valor);
                }
                break;
            case 3:
                printf("\nDigite o valor que deseja remover: ");
                scanf("%d", &valor);
                removerElemento(vetor, &tamanhoAtual, valor);
                break;
            case 4:
                printf("\nDigite o valor que deseja inserir: ");
                scanf("%d", &valor);
                inserirOrdenado(vetor, &tamanhoAtual, valor);
                break;
            case 0:
                printf("\nSaindo do programa. Ate mais!\n");
                break;
            default:
                printf("\n\t>>> Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}
