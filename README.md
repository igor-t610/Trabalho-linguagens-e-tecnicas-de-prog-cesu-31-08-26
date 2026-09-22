# Trabalho de integração
Respositorio para o trabalho da diciplina linguagens e tecnicas de progamação

Carlos Eduardo
Carlos Penso
Igor Toy
Matheus Roberto
Victor Gabriel 
# 1 - Descrição do sistema

O projeto consiste em um sistema de controle de ponto de funcionários desenvolvido em linguagem C. O sistema permitirá o cadastro prévio dos colaboradores e o registro diário e individualizado dos horários de entrada e saída de cada trabalhador. O programa utilizará arquivos binários para persistência de dados, garantindo que as informações de cadastro e os históricos de batidas de ponto não sejam perdidos ao fechar a aplicação. O foco principal é resolver a problemática do controle manual da jornada de trabalho (como o uso de planilhas ou livros de ponto em papel), automatizando o registro seguro dos horários e facilitando o acompanhamento das horas trabalhadas por cada funcionário.


# 2 - Fluxo de Utilização Esperado para o Sistema

Ao iniciar o programa, o usuário visualizará um menu principal com as opções:

1. Cadastrar Funcionário
2. Registrar Entrada
3. Registrar Saída
4. Consultar Registro de Ponto
5. Consultar Funcionários
6. Sair

Caso o usuário escolha a opção 1, o sistema solicitará os dados do funcionário, como nome e numero de identificação 

Se escolher a opção 2, o sistema solicitará a identificação do usuário e registrara data e hora da sua entrada 

Caso escolha a opção 3, o sistema solicitará a identificação do funcionário e registrará a data e o horário de sua saída.

Se escolher a opção 4, o sistema solicitará a identificação do funcionário e exibirá seus registros de entrada e saída.

Caso escolha a opção 5, o sistema exibirá a lista de funcionários cadastrados no sistema.

Se escolher a opção 6, o sistema encerrará o programa.

As operações de erro, como funcionário não cadastrado, identificação inválida ou tentativa de registrar uma saída sem uma entrada correspondente, exibirão mensagens claras ao usuário e retornarão ao menu principal.

# 3 - Fluxograma da Lógica do Sistema
![Fluxograma Principal](Imagens/fluxograma.png)]
# 4 - Estrutura de Dados

O sistema utilizará as seguintes estruturas heterogêneas para gerenciar as informações:
```c
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
```
