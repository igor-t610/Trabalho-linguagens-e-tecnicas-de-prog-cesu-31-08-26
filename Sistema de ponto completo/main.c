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
case 4:
                printf("\n=== REGISTRAR ENTRADA ===\n");
                if (total_pontos >= 200) {
                    printf("\nErro: Limite de registros atingido!\n");
                    break;
                }

                printf("Digite o ID do funcionario: ");
                scanf("%d", &id_digitado);

                // Verifica se o funcionario existe
                existe = 0;
                for (i = 0; i < total_func; i++) {
                    if (id_func[i] == id_digitado) {
                        existe = 1;
                    }
                }

                if (existe == 0) {
                    printf("\nErro: Funcionario nao encontrado!\n");
                    break;
                }

                // Verifica se ja tem ponto aberto para este ID
                encontrou = 0;
                for (i = 0; i < total_pontos; i++) {
                    if (ponto_id_func[i] == id_digitado && ponto_aberto[i] == 1) {
                        encontrou = 1;
                    }
                }

                if (encontrou == 1) {
                    printf("\nErro: Este funcionario ja possui uma entrada em aberto!\n");
                } else {
                    ponto_id_func[total_pontos] = id_digitado;

                    printf("Digite a data (DD/MM/AAAA): ");
                    scanf(" %14s", ponto_data[total_pontos]);

                    printf("Digite a HORA de entrada (0 a 23): ");
                    scanf("%d", &ponto_horarios[total_pontos][0]);

                    printf("Digite o MINUTO de entrada (0 a 59): ");
                    scanf("%d", &ponto_horarios[total_pontos][1]);

                    // Zera os dados de saida na matriz ate o funcionario encerrar o turno
                    ponto_horarios[total_pontos][2] = 0;
                    ponto_horarios[total_pontos][3] = 0;
                    ponto_horas[total_pontos][0] = 0.0f;
                    ponto_horas[total_pontos][1] = 0.0f;
                    ponto_aberto[total_pontos] = 1;

                    total_pontos++;
                    printf("\nEntrada registrada com sucesso! (Registro #%d aberto)\n", total_pontos);
                }
                break;

case 5:
                printf("\n=== REGISTRAR SAIDA ===\n");
                printf("Digite o ID do funcionario: ");
                scanf("%d", &id_digitado);

                // Procura a jornada diaria do funcionario
                jornada_atual = 8.0f;
                for (i = 0; i < total_func; i++) {
                    if (id_func[i] == id_digitado) {
                        jornada_atual = jornada_func[i];
                    }
                }

                // Procura o ponto em aberto desse funcionario
                encontrou = 0;
                for (i = 0; i < total_pontos; i++) {
                    if (ponto_id_func[i] == id_digitado && ponto_aberto[i] == 1) {
                        encontrou = 1;
                        printf("Entrada encontrada na data %s as %02d:%02d\n",
                               ponto_data[i], ponto_horarios[i][0], ponto_horarios[i][1]);

                        printf("Digite a HORA de saida (0 a 23): ");
                        scanf("%d", &ponto_horarios[i][2]);

                        printf("Digite o MINUTO de saida (0 a 59): ");
                        scanf("%d", &ponto_horarios[i][3]);

                        // Converte horas para minutos e calcula o total trabalhado
                        min_entrada = (ponto_horarios[i][0] * 60) + ponto_horarios[i][1];
                        min_saida = (ponto_horarios[i][2] * 60) + ponto_horarios[i][3];
                        diferenca_min = min_saida - min_entrada;

                        if (diferenca_min < 0) {
                            diferenca_min = diferenca_min + (24 * 60);
                        }

                        horas_trab = diferenca_min / 60.0f;
                        ponto_horas[i][0] = horas_trab;

                        // Calcula horas extras na coluna 1 da matriz
                        if (horas_trab > jornada_atual) {
                            ponto_horas[i][1] = horas_trab - jornada_atual;
                        } else {
                            ponto_horas[i][1] = 0.0f;
                        }

                        ponto_aberto[i] = 0; // Fecha o registro

                        printf("\nSaida registrada com sucesso!\n");
                        printf("Total trabalhado: %.2f h | Horas extras: %.2f h\n",
                               ponto_horas[i][0], ponto_horas[i][1]);
                        break;
                    }
                }

                if (encontrou == 0) {
                    printf("\nAviso: Nenhum registro de entrada em aberto para este ID.\n");
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
