#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ESTADOS 26

typedef struct {
    char nome[30];
    int numVeiculos;
    int numAcidentes;
} Estado;

void ColetarDados(Estado cadastro[]) {
    int i;
    printf("--- Coleta de Dados dos %d Estados ---\n", NUM_ESTADOS);
    for (i = 0; i < NUM_ESTADOS; i++) {
        printf("\n--- Estado %d/%d ---\n", i + 1, NUM_ESTADOS);
        printf("Nome do estado (sem espacos): ");
        scanf("%s", cadastro[i].nome);
        printf("Numero de veiculos (2007): ");
        scanf("%d", &cadastro[i].numVeiculos);
        printf("Numero de acidentes de transito (2007): ");
        scanf("%d", &cadastro[i].numAcidentes);
    }
}

void EncontrarExtremos(Estado cadastro[], int *posMaior, int *posMenor) {
    int i;
    int maior = cadastro[0].numAcidentes;
    int menor = cadastro[0].numAcidentes;
    *posMaior = 0;
    *posMenor = 0;

    for (i = 1; i < NUM_ESTADOS; i++) {
        if (cadastro[i].numAcidentes > maior) {
            maior = cadastro[i].numAcidentes;
            *posMaior = i;
        }
        if (cadastro[i].numAcidentes < menor) {
            menor = cadastro[i].numAcidentes;
            *posMenor = i;
        }
    }
}

float CalcularPercentual(Estado estado) {
    if (estado.numVeiculos > 0) {
        return ((float)estado.numAcidentes / estado.numVeiculos) * 100.0;
    }
    return 0.0;
}

float CalcularMediaAcidentes(Estado cadastro[]) {
    int i;
    long long somaAcidentes = 0;
    for (i = 0; i < NUM_ESTADOS; i++) {
        somaAcidentes += cadastro[i].numAcidentes;
    }
    return (float)somaAcidentes / NUM_ESTADOS;
}

void ExibirAcimaDaMedia(Estado cadastro[], float mediaPais) {
    int i;
    printf("\n Estados com acidentes acima da media do pais (%.2f):\n", mediaPais);
    for (i = 0; i < NUM_ESTADOS; i++) {
        if (cadastro[i].numAcidentes > mediaPais) {
            printf("- %s (Acidentes: %d)\n", cadastro[i].nome, cadastro[i].numAcidentes);
        }
    }
}

int main() {
    Estado cadastro[NUM_ESTADOS];
    int posMaior, posMenor;
    float mediaPais;
    int i;
    
    int current_num = NUM_ESTADOS;
    Estado *current_cadastro = cadastro;
    
    ColetarDados(current_cadastro); 

    printf("\n=================================================\n");
    printf("======== RESULTADOS DA ANALISE DE TRANSITO =======\n");
    printf("=================================================\n");

    EncontrarExtremos(current_cadastro, &posMaior, &posMenor);

    printf("Maior numero de acidentes: %d no estado de %s\n", 
           current_cadastro[posMaior].numAcidentes, current_cadastro[posMaior].nome);
    printf("📉 Menor numero de acidentes: %d no estado de %s\n", 
           current_cadastro[posMenor].numAcidentes, current_cadastro[posMenor].nome);

    printf("\n-------------------------------------------------\n");

    printf("Percentual de Veiculos Envolvidos em Acidentes:\n");
    for (i = 0; i < current_num; i++) {
        printf("- %s: %.4f%%\n", current_cadastro[i].nome, CalcularPercentual(current_cadastro[i]));
    }

    printf("\n-------------------------------------------------\n");

    mediaPais = CalcularMediaAcidentes(current_cadastro);
    printf("Media de acidentes do país (exibicao no main): %.2f\n", mediaPais);

    ExibirAcimaDaMedia(current_cadastro, mediaPais);

    return 0;
}
