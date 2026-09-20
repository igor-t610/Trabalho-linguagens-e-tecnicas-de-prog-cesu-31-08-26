// 1 - Cadastrar funcionario
void cadastrarFuncionario() {

    FILE *arquivo;
    Funcionario funcionario;

    printf("\n=== CADASTRO DE FUNCIONARIO ===\n");

    printf("Digite o ID: ");
    scanf("%d", &funcionario.id);

    printf("Digite o nome: ");
    scanf(" %[^\n]", funcionario.nome);

    funcionario.ativo = 1;

    arquivo = fopen("funcionarios.dat", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&funcionario, sizeof(Funcionario), 1, arquivo);
    fclose(arquivo);

    printf("\nFuncionario cadastrado com sucesso!\n");
}

// Verifica se o funcionario existe
int funcionarioExiste(int id) {

    FILE *arquivo;
    Funcionario funcionario;

    arquivo = fopen("funcionarios.dat", "rb");

    if (arquivo == NULL)
        return 0;

    while (fread(&funcionario, sizeof(Funcionario), 1, arquivo) == 1) {

        if (funcionario.id == id && funcionario.ativo == 1) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}
