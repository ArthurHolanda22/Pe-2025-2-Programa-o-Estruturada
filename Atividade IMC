#include <stdio.h>

int main() {
    float peso, altura, imc;
    char faixa[50];

    printf("Digite o peso da pessoa (em kg): ");
    scanf("%f", &peso);

    printf("Digite a altura da pessoa (em metros): ");
    scanf("%f", &altura);

    imc = peso / (altura * altura);
    if (imc < 18.5) {
        sprintf(faixa, "Abaixo do peso");
    } else if (imc >= 18.5 && imc < 24.9) {
        sprintf(faixa, "Peso normal");
    } else if (imc >= 25.0 && imc < 29.9) {
        sprintf(faixa, "Sobrepeso");
    } else if (imc >= 30.0 && imc < 34.9) {
        sprintf(faixa, "Obesidade Grau I");
    } else if (imc >= 35.0 && imc < 39.9) {
        sprintf(faixa, "Obesidade Grau II (severa)");
    } else {
        sprintf(faixa, "Obesidade Grau III (mórbida)");
    }
    printf("\nIMC calculado: %.2f\n", imc);
    printf("Faixa: %s\n", faixa);

    return 0;
}
