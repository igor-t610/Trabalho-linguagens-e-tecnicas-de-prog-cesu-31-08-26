// Estrutura para armazenamento dos funcionarios
typedef struct {
    int id;
    char nome[100];
    float jornada_diaria; 
    int ativo;            // 1 = ativo, 0 = inativo
} Funcionario;

// Estrutura para armazenamento dos registros de ponto
typedef struct {
    int id_funcionario;
    int id_registro;
    char data[11];                 // DD/MM/AAAA
    char hora_entrada[6];          // HH:MM
    char hora_saida[6];            // HH:MM
    float total_horas_trabalhadas; 
    float horas_extras;          
    int ativo;                     // 1 = registro aberto, 0 = registro encerrado
} Registroponto;
