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
void buscarFuncionarioPorNome() {
    FILE *arquivo;
    Funcionario f;
    char termo[100];
    int encontrou = 0;

    arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo de funcionarios. Cadastre alguem primeiro.\n");
        return;
    }

    printf("\nDigite o nome (ou parte do nome) para buscar: ");
    scanf(" %99[^\n]", termo);

    printf("\n=== RESULTADO DA BUSCA ===\n");
    while (fread(&f, sizeof(Funcionario), 1, arquivo) == 1) {
        if (f.ativo == 1 && strstr(f.nome, termo) != NULL) {
            printf("ID: %d | Nome: %s | Jornada: %.2f h\n", f.id, f.nome, f.jornada_diaria);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("A busca por '%s' nao teve resultados.\n", termo);
    }

    fclose(arquivo);
}
void listarRegistrosPonto() {
    FILE *arquivo;
    Registroponto reg;
    int encontrou = 0;

    arquivo = fopen("pontos.dat", "rb");
    if (arquivo == NULL) {
        printf("\nErro: Nenhum registro de ponto encontrado (arquivo inexistente).\n");
        return;
    }

    printf("\n=== HISTORICO DE PONTOS ===\n");
    while (fread(&reg, sizeof(Registroponto), 1, arquivo) == 1) {
        printf("Reg #%d | Func ID: %d | Data: %s | Entrada: %s | Saida: %s | Total: %.2fh | Extras: %.2fh | Status: %s\n",
               reg.id_registro, reg.id_funcionario, reg.data, reg.hora_entrada, reg.hora_saida,
               reg.total_horas_trabalhadas, reg.horas_extras,
               reg.ativo == 1 ? "ABERTO" : "ENCERRADO");
        encontrou = 1;
    }

    if (!encontrou) {
        printf("A busca nao retornou nenhum registro de ponto.\n");
    }

    fclose(arquivo);
}
