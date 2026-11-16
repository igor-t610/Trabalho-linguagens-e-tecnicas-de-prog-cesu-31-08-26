#ifndef SISTEMA_H
#define SISTEMA_H

typedef struct {
    int id;
    char nome[100];
    float jornada_diaria; 
    int ativo;
} Funcionario;

typedef struct {
    int id_funcionario;
    int id_registro;
    char data[11];
    char hora_entrada[6];
    char hora_saida[6];
    float total_horas_trabalhadas; 
    float horas_extras;          
    int ativo;
} Registroponto;

void cadastrarFuncionario();
int funcionarioExiste(int id);
float obterJornadaFuncionario(int id);
void listarFuncionarios();
void buscarFuncionarioPorNome();

void registrarEntrada();
void registrarSaida();
void listarRegistrosPonto();
float calcularHoras(char *entrada, char *saida);

#endif
