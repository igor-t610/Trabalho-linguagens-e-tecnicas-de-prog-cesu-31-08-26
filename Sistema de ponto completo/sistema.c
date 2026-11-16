#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"

int funcionarioExiste(int id) {
    FILE *arquivo;
    Funcionario f;

    arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) {
        return 0;
    }

    while (fread(&f, sizeof(Funcionario), 1, arquivo) == 1) {
        if (f.id == id && f.ativo == 1) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

float obterJornadaFuncionario(int id) {
    FILE *arquivo;
    Funcionario f;

    arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) {
        return 8.0f;
    }

    while (fread(&f, sizeof(Funcionario), 1, arquivo) == 1) {
        if (f.id == id && f.ativo == 1) {
            fclose(arquivo);
            return f.jornada_diaria;
        }
    }

    fclose(arquivo);
    return 8.0f;
}

void cadastrarFuncionario() {
    FILE *arquivo;
    Funcionario funcionario;

    printf("\n=== CADASTRO DE FUNCIONARIO ===\n");
    printf("Digite o ID: ");
    scanf("%d", &funcionario.id);

    if (funcionarioExiste(funcionario.id)) {
        printf("\nErro: Ja existe um funcionario ativo com este ID!\n");
        return;
    }

    printf("Digite o nome: ");
    scanf(" %99[^\n]", funcionario.nome);

    printf("Digite a jornada diaria (em horas, ex: 8.0): ");
    scanf("%f", &funcionario.jornada_diaria);

    funcionario.ativo = 1;

    arquivo = fopen("funcionarios.dat", "ab");
    if (arquivo == NULL) {
        printf("\nErro ao abrir ou criar o arquivo de funcionarios.\n");
        return;
    }

    fwrite(&funcionario, sizeof(Funcionario), 1, arquivo);
    fclose(arquivo);

    printf("\nFuncionario cadastrado com sucesso!\n");
}

void listarFuncionarios() {
    FILE *arquivo;
    Funcionario f;
    int encontrou = 0;

    arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("\nErro: Arquivo de funcionarios ainda nao existe ou nao pode ser aberto.\n");
        return;
    }

    printf("\n=== LISTA DE FUNCIONARIOS ===\n");
    while (fread(&f, sizeof(Funcionario), 1, arquivo) == 1) {
        if (f.ativo == 1) {
            printf("ID: %d | Nome: %s | Jornada Diaria: %.2f h\n", f.id, f.nome, f.jornada_diaria);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum funcionario ativo encontrado.\n");
    }

    fclose(arquivo);
}
