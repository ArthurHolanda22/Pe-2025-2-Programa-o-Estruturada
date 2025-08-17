#include <stdio.h>

int main() {
    float salario, imposto, percentual;
    printf("Digite o salário da pessoa (em R$): ");
    scanf("%f", &salario);
    if (salario <= 2112.00) {
        percentual = 0.0;
        imposto = 0.0;
    } else if (salario <= 2826.65) {
        percentual = 7.5;
        imposto = (salario * 0.075) - 158.40;
    } else if (salario <= 3751.05) {
        percentual = 15.0;
        imposto = (salario * 0.15) - 370.40;
    } else if (salario <= 4664.68) {
        percentual = 22.5;
        imposto = (salario * 0.225) - 651.73;
    } else {
        percentual = 27.5;
        imposto = (salario * 0.275) - 884.96;
    }
    printf("\nSalário informado: R$ %.2f\n", salario);
    printf("Percentual do Imposto de Renda Retido: %.1f%%\n", percentual);
    printf("Valor do Imposto de Renda Retido: R$ %.2f\n", imposto);
    return 0;
}
