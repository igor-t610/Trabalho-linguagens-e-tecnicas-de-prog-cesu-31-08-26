#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"

int main() {
    int opcao;

    do {
        printf("\n========================================\n");
        printf("       SISTEMA DE CONTROLE DE PONTO     \n");
        printf("========================================\n");
        printf("1. Cadastrar Funcionario\n");
        printf("2. Listar Funcionarios\n");
        printf("3. Buscar Funcionario por Nome\n");
        printf("4. Bater Ponto - Entrada\n");
        printf("5. Bater Ponto - Saida\n");
        printf("6. Listar Registros de Ponto\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFuncionario();
                break;
            case 2:
                listarFuncionarios();
                break;
            case 3:
                buscarFuncionarioPorNome();
                break;
            case 6:
                listarRegistrosPonto();
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida ou em implementacao!\n");

            case 4:
                registrarEntrada();
                break;
            case 5:
                registrarSaida();
                break;
        }
    } while (opcao != 0);

    system("pause");
    return 0;
}
