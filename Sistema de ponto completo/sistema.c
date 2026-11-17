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

float calcularHoras(char *entrada, char *saida) {
    int h_ent = 0, m_ent = 0, h_sai = 0, m_sai = 0;
    int total_min_entrada, total_min_saida, diferenca_minutos;

    sscanf(entrada, "%d:%d", &h_ent, &m_ent);
    sscanf(saida, "%d:%d", &h_sai, &m_sai);

    total_min_entrada = (h_ent * 60) + m_ent;
    total_min_saida = (h_sai * 60) + m_sai;

    diferenca_minutos = total_min_saida - total_min_entrada;
    if (diferenca_minutos < 0) {
        diferenca_minutos += 24 * 60;
    }

    return diferenca_minutos / 60.0f;
}

void registrarEntrada() {
    Registroponto reg, temp;
    FILE *arquivo;
    int ultimo_id = 0;

    printf("\n=== REGISTRAR ENTRADA ===\n");
    printf("Digite o ID do funcionario: ");
    scanf("%d", &reg.id_funcionario);

    if (!funcionarioExiste(reg.id_funcionario)) {
        printf("\nErro: Funcionario nao encontrado ou inativo!\n");
        return;
    }

    arquivo = fopen("pontos.dat", "rb");
    if (arquivo != NULL) {
        while (fread(&temp, sizeof(Registroponto), 1, arquivo) == 1) {
            if (temp.id_funcionario == reg.id_funcionario && temp.ativo == 1) {
                printf("\nErro: Este funcionario ja possui uma entrada em aberto (Registro #%d)!\n", temp.id_registro);
                fclose(arquivo);
                return;
            }
            if (temp.id_registro > ultimo_id) {
                ultimo_id = temp.id_registro;
            }
        }
        fclose(arquivo);
    }

    reg.id_registro = ultimo_id + 1;

    printf("Digite a data (DD/MM/AAAA): ");
    scanf(" %10s", reg.data);

    printf("Digite a hora de entrada (HH:MM): ");
    scanf(" %5s", reg.hora_entrada);

    strcpy(reg.hora_saida, "--:--");
    reg.total_horas_trabalhadas = 0.0f;
    reg.horas_extras = 0.0f;
    reg.ativo = 1;

    arquivo = fopen("pontos.dat", "ab");
    if (arquivo == NULL) {
        printf("\nErro ao abrir ou criar o arquivo de pontos.\n");
        return;
    }

    fwrite(&reg, sizeof(Registroponto), 1, arquivo);
    fclose(arquivo);

    printf("\nEntrada registrada com sucesso! (Registro #%d aberto)\n", reg.id_registro);
}

void registrarSaida() {
    int id_func;
    Registroponto reg;
    int encontrou = 0;
    float jornada;
    FILE *arquivo;

    printf("\n=== REGISTRAR SAIDA ===\n");
    printf("Digite o ID do funcionario: ");
    scanf("%d", &id_func);

    if (!funcionarioExiste(id_func)) {
        printf("\nErro: Funcionario nao encontrado!\n");
        return;
    }

    arquivo = fopen("pontos.dat", "rb+");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo de pontos. Nenhum registro de entrada foi feito ainda.\n");
        return;
    }

    while (fread(&reg, sizeof(Registroponto), 1, arquivo) == 1) {
        if (reg.id_funcionario == id_func && reg.ativo == 1) {
            encontrou = 1;
            printf("Registro aberto encontrado -> Data: %s | Entrada: %s\n", reg.data, reg.hora_entrada);
            printf("Digite a hora de saida (HH:MM): ");
            scanf(" %5s", reg.hora_saida);

            reg.total_horas_trabalhadas = calcularHoras(reg.hora_entrada, reg.hora_saida);
            jornada = obterJornadaFuncionario(id_func);

            if (reg.total_horas_trabalhadas > jornada) {
                reg.horas_extras = reg.total_horas_trabalhadas - jornada;
            } else {
                reg.horas_extras = 0.0f;
            }

            reg.ativo = 0;

            fseek(arquivo, -(long)sizeof(Registroponto), SEEK_CUR);
            fwrite(&reg, sizeof(Registroponto), 1, arquivo);
            break;
        }
    }

    fclose(arquivo);

    if (encontrou) {
        printf("\nSaida registrada com sucesso!\n");
        printf("Total trabalhado: %.2f h | Horas extras: %.2f h\n", reg.total_horas_trabalhadas, reg.horas_extras);
    } else {
        printf("\nAviso: Nenhum registro de ponto em aberto foi encontrado para este funcionario.\n");
    }
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
