#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTAS 100

typedef enum {
    CORRENTE,
    POUPANCA
} TipoConta;

typedef struct {
    int numConta;
    TipoConta tipo;
    float saldo;
    char numCpf[15];
    char nome[50];
    char telefone[15];
    char contato[15];
} Conta;

int Buscar(Conta cadastro[], int numContasCadastradas, int contaProcurada) {
    int i;
    for (i = 0; i < numContasCadastradas; i++) {
        if (cadastro[i].numConta == contaProcurada) {
            return i;
        }
    }
    return -2;
}

void CadastrarConta(Conta cadastro[], int *numContasCadastradas) {
    int novaConta;
    int posicao;
    char tipoStr[5];

    if (*numContasCadastradas >= MAX_CONTAS) {
        printf("ERRO: Limite maximo de %d contas atingido.\n", MAX_CONTAS);
        return;
    }

    printf("\nDigite o numero da nova conta: ");
    scanf("%d", &novaConta);

    posicao = Buscar(cadastro, *numContasCadastradas, novaConta);

    if (posicao != -2) {
        printf("ATENCAO: A conta %d ja esta cadastrada. Cadastro abortado.\n", novaConta);
    } else {
        int idx = *numContasCadastradas; 

        cadastro[idx].numConta = novaConta;

        printf("Nome do cliente (sem espacos): ");
        scanf("%s", cadastro[idx].nome);
        printf("CPF do cliente: ");
        scanf("%s", cadastro[idx].numCpf);
        printf("Telefone do cliente: ");
        scanf("%s", cadastro[idx].telefone);
        printf("Telefone do contato: ");
        scanf("%s", cadastro[idx].contato);

        printf("Tipo de conta (C para Corrente, P para Poupanca): ");
        scanf("%s", tipoStr);

        if (tipoStr[0] == 'C' || tipoStr[0] == 'c') {
            cadastro[idx].tipo = CORRENTE;
        } else {
            cadastro[idx].tipo = POUPANCA; 
        }

        cadastro[idx].saldo = 0.0;
        (*numContasCadastradas)++; 

        printf("SUCESSO: Conta %d cadastrada com saldo inicial de R$%.2f.\n", novaConta, cadastro[idx].saldo);
    }
}

void ConsultarSaldo(Conta cadastro[], int numContasCadastradas) {
    int contaConsulta;
    int posicao;

    printf("\nDigite o numero da conta para consulta: ");
    scanf("%d", &contaConsulta);

    posicao = Buscar(cadastro, numContasCadastradas, contaConsulta);

    if (posicao != -2) {
        printf("--- Saldo da Conta %d ---\n", contaConsulta);
        printf("Titular: %s\n", cadastro[posicao].nome);
        printf("Saldo: R$%.2f\n", cadastro[posicao].saldo);
    } else {
        printf("ERRO: Conta %d nao esta cadastrada.\n", contaConsulta);
    }
}

void FazerDeposito(Conta cadastro[], int numContasCadastradas) {
    int contaDeposito;
    int posicao;
    float valor;

    printf("\nDigite o numero da conta para deposito: ");
    scanf("%d", &contaDeposito);
    posicao = Buscar(cadastro, numContasCadastradas, contaDeposito);

    if (posicao != -2) {
        printf("Digite o valor do deposito: R$");
        scanf("%f", &valor);

        if (valor > 0) {
            cadastro[posicao].saldo += valor;
            printf("SUCESSO: Depositado R$%.2f na conta %d.\n", valor, contaDeposito);
            printf("Novo Saldo: R$%.2f\n", cadastro[posicao].saldo);
        } else {
            printf("ATENCAO: O valor do deposito deve ser positivo.\n");
        }
    } else {
        printf("ERRO: Conta %d nao esta cadastrada. Deposito nao efetuado.\n", contaDeposito);
    }
}

void FazerSaque(Conta cadastro[], int numContasCadastradas) {
    int contaSaque;
    int posicao;
    float valor;

    printf("\nDigite o numero da conta para saque: ");
    scanf("%d", &contaSaque);
    posicao = Buscar(cadastro, numContasCadastradas, contaSaque);

    if (posicao != -2) {
        printf("Digite o valor do saque: R$");
        scanf("%f", &valor);

        if (valor <= 0) {
            printf("ERRO: O valor do saque deve ser positivo.\n");
            return;
        }

        if (cadastro[posicao].saldo >= valor) {
            cadastro[posicao].saldo -= valor;
            printf("SUCESSO: Sacado R$%.2f da conta %d.\n", valor, contaSaque);
            printf("Novo Saldo: R$%.2f\n", cadastro[posicao].saldo);
        } else {
            printf("ERRO: Saldo insuficiente. Saldo atual: R$%.2f\n", cadastro[posicao].saldo);
        }
    } else {
        printf("ERRO: Conta %d nao esta cadastrada. Saque nao efetuado.\n", contaSaque);
    }
}

void ExibirContato(Conta cadastro[], int numContasCadastradas) {
    int contaConsulta;
    int posicao;

    printf("\nDigite o numero da conta para ver os dados de contato: ");
    scanf("%d", &contaConsulta);
    posicao = Buscar(cadastro, numContasCadastradas, contaConsulta);

    if (posicao != -2) {
        printf("--- Dados de Contato da Conta %d ---\n", contaConsulta);
        printf("Titular: %s\n", cadastro[posicao].nome);
        printf("Telefone do Titular: %s\n", cadastro[posicao].telefone);
        printf("Telefone de Contato: %s\n", cadastro[posicao].contato);
    } else {
        printf("ERRO: Conta %d nao esta cadastrada.\n", contaConsulta);
    }
}

int main() {
    Conta cadastro[MAX_CONTAS];
    int numContasCadastradas = 0;
    int opcao;

    do {
        printf("\n========== MENU DO BANCO ==========\n");
        printf("1 - Cadastrar Nova Conta\n");
        printf("2 - Consultar Saldo\n");
        printf("3 - Fazer Deposito\n");
        printf("4 - Fazer Saque\n");
        printf("5 - Exibir Contato\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) { 
            while (getchar() != '\n'); 
            opcao = -1; 
        }

        switch (opcao) {
            case 1:
                CadastrarConta(cadastro, &numContasCadastradas);
                break;
            case 2:
                ConsultarSaldo(cadastro, numContasCadastradas);
                break;
            case 3:
                FazerDeposito(cadastro, numContasCadastradas);
                break;
            case 4:
                FazerSaque(cadastro, numContasCadastradas);
                break;
            case 5:
                ExibirContato(cadastro, numContasCadastradas);
                break;
            case 0:
                printf("\nEncerrando o sistema. Obrigado!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
