#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Variaveis de controle e contadores
    int opcao;
    int i;
    int total_func = 0;
    int total_pontos = 0;

    // Vetores e Matriz para Funcionarios (ate 100 funcionarios)
    int id_func[100];
    char nome_func[100][100]; // Matriz de caracteres: 100 linhas por 100 colunas
    float jornada_func[100];

    // Vetores e Matrizes para Registros de Ponto (ate 200 registros)
    int ponto_id_func[200];
    char ponto_data[200][15];   // Matriz para guardar as datas (DD/MM/AAAA)
    int ponto_horarios[200][4]; // Matriz 200x4 -> [0]Hora Ent, [1]Min Ent, [2]Hora Sai, [3]Min Sai
    float ponto_horas[200][2];  // Matriz 200x2 -> [0]Total Trabalhado, [1]Horas Extras
    int ponto_aberto[200];      // Vetor de status: 1 = Aberto, 0 = Encerrado

    // Variaveis auxiliares para buscas e leituras
    int id_digitado, existe, indice_func, encontrou;
    char termo_busca[100];
    int min_entrada, min_saida, diferenca_min;
    float horas_trab, jornada_atual;

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

            // ---> COLAR AQUI O CODIGO DO INTEGRANTE 2 (case 1 e case 2)

            // ---> COLAR AQUI O CODIGO DO INTEGRANTE 3 (case 3 e case 6)

            // ---> COLAR AQUI O CODIGO DO INTEGRANTE 4 (case 4)

            // ---> COLAR AQUI O CODIGO DO INTEGRANTE 5 (case 5)

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    system("pause");
    return 0;
}
