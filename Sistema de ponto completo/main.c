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

            case 1:
                printf("\n=== CADASTRO DE FUNCIONARIO ===\n");
                if (total_func >= 100) {
                    printf("\nErro: Limite maximo de funcionarios atingido!\n");
                    break;
                }

                printf("Digite o ID: ");
                scanf("%d", &id_digitado);

                // Laço para verificar se o ID ja existe no vetor
                existe = 0;
                for (i = 0; i < total_func; i++) {
                    if (id_func[i] == id_digitado) {
                        existe = 1;
                    }
                }

                if (existe == 1) {
                    printf("\nErro: Ja existe um funcionario com este ID!\n");
                } else {
                    id_func[total_func] = id_digitado;

                    printf("Digite o nome: ");
                    scanf(" %99[^\n]", nome_func[total_func]);

                    printf("Digite a jornada diaria (em horas, ex: 8.0): ");
                    scanf("%f", &jornada_func[total_func]);

                    total_func++;
                    printf("\nFuncionario cadastrado com sucesso!\n");
                }
                break;

            case 2:
                printf("\n=== LISTA DE FUNCIONARIOS ===\n");
                if (total_func == 0) {
                    printf("Nenhum funcionario cadastrado ainda.\n");
                } else {
                    for (i = 0; i < total_func; i++) {
                        printf("ID: %d | Nome: %s | Jornada Diaria: %.2f h\n",
                               id_func[i], nome_func[i], jornada_func[i]);
                    }
                }
                break;

            case 3:
                printf("\n=== BUSCAR FUNCIONARIO POR NOME ===\n");
                if (total_func == 0) {
                    printf("Erro: Nenhum funcionario cadastrado para buscar.\n");
                    break;
                }

                printf("Digite o nome exato para buscar: ");
                scanf(" %99[^\n]", termo_busca);

                encontrou = 0;
                for (i = 0; i < total_func; i++) {
                    if (strcmp(nome_func[i], termo_busca) == 0) {
                        printf("ID: %d | Nome: %s | Jornada: %.2f h\n",
                               id_func[i], nome_func[i], jornada_func[i]);
                        encontrou = 1;
                    }
                }

                if (encontrou == 0) {
                    printf("A busca por '%s' nao retornou resultados.\n", termo_busca);
                }
                break;

            case 6:
                printf("\n=== HISTORICO DE PONTOS ===\n");
                if (total_pontos == 0) {
                    printf("Nenhum registro de ponto encontrado.\n");
                } else {
                    for (i = 0; i < total_pontos; i++) {
                        if (ponto_aberto[i] == 1) {
                            printf("Reg #%d | Func ID: %d | Data: %s | Entrada: %02d:%02d | Saida: --:-- | Status: ABERTO\n",
                                   i + 1, ponto_id_func[i], ponto_data[i],
                                   ponto_horarios[i][0], ponto_horarios[i][1]);
                        } else {
                            printf("Reg #%d | Func ID: %d | Data: %s | Entrada: %02d:%02d | Saida: %02d:%02d | Total: %.2fh | Extras: %.2fh | Status: ENCERRADO\n",
                                   i + 1, ponto_id_func[i], ponto_data[i],
                                   ponto_horarios[i][0], ponto_horarios[i][1],
                                   ponto_horarios[i][2], ponto_horarios[i][3],
                                   ponto_horas[i][0], ponto_horas[i][1]);
                        }
                    }
                }
                break;

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
