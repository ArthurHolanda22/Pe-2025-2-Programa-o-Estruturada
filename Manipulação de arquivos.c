#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 256
#define NOME_ARQ_TEMP "temp_arq.dat" 

void lerStr(char str[], int tam);
void inserirFinalArquivo(char nomeArq[]);
void listarArquivo(char nomeArq[]);
void lerPosicaoEspecifica(char nomeArq[]);


void buscarNumero(char nomeArq[]);
void substituirNumero(char nomeArq[]);
void excluirNumero(char nomeArq[]);

int main() {
  char nomeArq[TAM];
  int opcao;
  printf("Digite o nome do arquivo: ");
  lerStr(nomeArq, TAM);
  while(strlen(nomeArq) == 0) {
    printf("Nome vazio é inválido!\n");
    printf("Digite o nome do arquivo: ");
    lerStr(nomeArq, TAM);
  }
  do {
    printf("\n\nMENU\n");
    printf("1 - Gravar um número no final do arquivo\n");
    printf("2 - Listar o conteúdo do arquivo\n");
    printf("3 - Imprimir valor específico (por posição)\n");
    printf("4 - Buscar se um número está ou não salvo no arquivo\n");         
    printf("5 - Substituir um número que está salvo no arquivo\n");          
    printf("6 - Excluir um número do arquivo\n");                           
    printf("Digite a sua opção (0 p/ finalizar): ");

    
    if (scanf("%d", &opcao) != 1) {
        while(getchar() != '\n'); 
        opcao = -1;
    } else {
        while(getchar() != '\n'); 
    }

    switch (opcao) {
      case 1:
        inserirFinalArquivo(nomeArq);
        break;
      case 2:
        printf("---------------- Listagem ----------------\n");
        listarArquivo(nomeArq);
        printf("------------------------------------------\n");
        break;
      case 3:
        lerPosicaoEspecifica(nomeArq);
        break;
      case 4:
        buscarNumero(nomeArq); 
        break;
      case 5:
        substituirNumero(nomeArq); 
        break;
      case 6:
        excluirNumero(nomeArq); 
        break;
      default:
        if (opcao != 0) {
          printf("Opção inválida!\n");
        }
      }
  } while (opcao != 0);
  return 0;
}

void lerStr(char str[], int tam) {
  fgets(str, tam, stdin);
  int tamDigitado = strlen(str);
  if (tamDigitado > 0 && str[tamDigitado - 1] == '\n') {
    str[tamDigitado - 1] = '\0';
  }
}

void inserirFinalArquivo(char nomeArq[]) {
  int status;
  double num;
  FILE *arq = fopen(nomeArq, "ab");
  if (arq == NULL) {
    printf("Não pode abrir o arquivo para escrita!\n");
    return;
  }
  printf("Digite um número real: ");
  if (scanf("%lf", &num) != 1) {
      printf("Entrada inválida!\n");
      while(getchar() != '\n');
      fclose(arq);
      return;
  }
  while(getchar() != '\n');

  status = fwrite(&num, sizeof(double), 1, arq);
  if (status == 1) {
    printf("Valor armazenado com sucesso!\n");
  } else {
    printf("Erro ao gravar o valor no arquivo!\n");
  }
  fclose(arq);
}

void listarArquivo(char nomeArq[]) {
  int status;
  double num;
  FILE *arq = fopen(nomeArq, "rb");
  if (arq == NULL) {
    printf("Não pode abrir o arquivo para leitura!\n");
    return;
  }
  long posicao = 1;
  while ((status = fread(&num, sizeof(double), 1, arq)) == 1) {
    printf("Posição %ld: %.3f\n", posicao++, num);
  }
  if (ferror(arq)) {
      printf("Erro na leitura do arquivo!\n");
  }
  fclose(arq);
}

void lerPosicaoEspecifica(char nomeArq[]) {
  int status, pos;
  double num;
  FILE *arq = fopen(nomeArq, "rb");
  if (arq == NULL) {
    printf("Não pode abrir o arquivo para leitura!\n");
    return;
  }

  printf("Você quer mover para que posição: ");
  if (scanf("%d", &pos) != 1 || pos <= 0) {
      printf("Posição inválida!\n");
      while(getchar() != '\n');
      fclose(arq);
      return;
  }
  while(getchar() != '\n');

  
  status = fseek(arq, (long)(pos - 1) * sizeof(double), SEEK_SET);

  if (status != 0) {
    printf("Erro ao posicionar no arquivo (posição pode ser inválida)!");
    fclose(arq);
    return;
  }

  status = fread(&num, sizeof(double), 1, arq);

  if (status != 1) {
    printf("Erro na leitura do registro ou posição inválida (além do final do arquivo).");
  } else {
    printf("Valor na posição %d: %.3f\n", pos, num);
  }
  fclose(arq);
}

void buscarNumero(char nomeArq[]) {
  double num_busca, num_arq;
  int status, encontrado = 0;
  long posicao = 1;

  printf("Digite o número real a ser buscado: ");
  if (scanf("%lf", &num_busca) != 1) {
      printf("Entrada inválida!\n");
      while(getchar() != '\n');
      return;
  }
  while(getchar() != '\n');

  FILE *arq = fopen(nomeArq, "rb");
  if (arq == NULL) {
    printf("Não pode abrir o arquivo para leitura!\n");
    return;
  }

  
  while ((status = fread(&num_arq, sizeof(double), 1, arq)) == 1) {
    if (num_arq == num_busca) {
      printf("Número %.3f encontrado na posição %ld do arquivo!\n", num_busca, posicao);
      encontrado = 1;
    
    }
    posicao++;
  }

  if (!encontrado) {
    printf("O número %.3f não foi encontrado no arquivo.\n", num_busca);
  }

  fclose(arq);
}

void substituirNumero(char nomeArq[]) {
  double num_antigo, num_novo, num_arq;
  int status;
  long posicao = 1;
  int substituido = 0;

  printf("Digite o número real que você deseja substituir: ");
  if (scanf("%lf", &num_antigo) != 1) {
      printf("Entrada inválida!\n");
      while(getchar() != '\n');
      return;
  }
  printf("Digite o novo número real: ");
  if (scanf("%lf", &num_novo) != 1) {
      printf("Entrada inválida!\n");
      while(getchar() != '\n');
      return;
  }
  while(getchar() != '\n');

  FILE *arq = fopen(nomeArq, "rb+");
  if (arq == NULL) {
    printf("Não pode abrir o arquivo para leitura e escrita (rb+)!\n");
    return;
  }

  
  while ((status = fread(&num_arq, sizeof(double), 1, arq)) == 1) {
    if (num_arq == num_antigo) {

      fseek(arq, -(long)sizeof(double), SEEK_CUR);

     
      if (fwrite(&num_novo, sizeof(double), 1, arq) == 1) {
        printf("Substituído %.3f por %.3f na posição %ld.\n", num_antigo, num_novo, posicao);
        substituido = 1;
        break; 
      } else {
        printf("Erro ao escrever o novo número.\n");
        break;
      }
    }
    posicao++;
  }

  if (!substituido) {
    printf("O número %.3f não foi encontrado para substituição.\n", num_antigo);
  }

  fclose(arq);
}

void excluirNumero(char nomeArq[]) {
  double num_excluir, num_arq;
  int status;
  int excluido = 0;

  printf("Digite o número real a ser excluído (todas as ocorrências): ");
  if (scanf("%lf", &num_excluir) != 1) {
      printf("Entrada inválida!\n");
      while(getchar() != '\n');
      return;
  }
  while(getchar() != '\n');

  FILE *arq_original = fopen(nomeArq, "rb");
  if (arq_original == NULL) {
    printf("Não pode abrir o arquivo original para leitura!\n");
    return;
  }

  FILE *arq_temp = fopen(NOME_ARQ_TEMP, "wb");
  if (arq_temp == NULL) {
    printf("Não pode criar o arquivo temporário!\n");
    fclose(arq_original);
    return;
  }

  
  while ((status = fread(&num_arq, sizeof(double), 1, arq_original)) == 1) {
    if (num_arq != num_excluir) {
      fwrite(&num_arq, sizeof(double), 1, arq_temp);
    } else {
      excluido++;
    }
  }

  fclose(arq_original);
  fclose(arq_temp);

  if (excluido == 0) {
    printf("O número %.3f não foi encontrado para exclusão. Nenhuma alteração feita.\n", num_excluir);
    remove(NOME_ARQ_TEMP); 
    return;
  }

  if (remove(nomeArq) != 0) {
    printf("Erro ao apagar o arquivo original! A exclusão falhou, novo arquivo em '%s'.\n", NOME_ARQ_TEMP);
    return;
  }

  if (rename(NOME_ARQ_TEMP, nomeArq) != 0) {
    printf("Erro ao renomear o arquivo temporário para o nome original! O novo arquivo está salvo como '%s'.\n", NOME_ARQ_TEMP);
    return;
  }

  printf("Total de %d ocorrência(s) de %.3f excluída(s) com sucesso.\n", excluido, num_excluir);
}
