#include <stdio.h>
#include <mysql.h>

// Defini��o da struct Aluno
typedef struct {
    char nome[255];
    int matricula;
    int anoIngresso;
    char curso[100];
} Aluno;

// Fun��o para exibir o menu
void exibir_menu() {
    printf("\n---- Menu de Op��es ----\n");
    printf("1. Inserir Aluno\n");
    printf("2. Atualizar Aluno\n");
    printf("3. Deletar Aluno\n");
    printf("4. Listar Alunos\n");
    printf("5. Sair\n");
    printf("Escolha uma op��o: ");
}

// Fun��o para inserir aluno no banco de dados
void inserir_aluno(MYSQL *conexao) {
    Aluno aluno;
    char query[512];

    // Coleta de dados do aluno
    printf("Nome do aluno: ");
    scanf(" %[^\n]", aluno.nome);
    printf("Matr�cula: ");
    scanf("%d", &aluno.matricula);
    printf("Ano de ingresso: ");
    scanf("%d", &aluno.anoIngresso);
    printf("Curso: ");
    scanf(" %[^\n]", aluno.curso);

    // Montando a query SQL para inserir o aluno
    sprintf(query, "INSERT INTO Aluno (nome, matricula, anoIngresso, curso) VALUES ('%s', %d, %d, '%s')", 
            aluno.nome, aluno.matricula, aluno.anoIngresso, aluno.curso);

    // Executando a query no banco de dados
    if (mysql_query(conexao, query)) {
        printf("Erro ao inserir aluno: %s\n", mysql_error(conexao));
    } else {
        printf("Aluno inserido com sucesso!\n");
    }
}

// Fun��o para atualizar um aluno no banco de dados
void atualizar_aluno(MYSQL *conexao) {
    int id;
    Aluno aluno;
    char query[512];

    // Coleta do ID do aluno que ser� atualizado
    printf("ID do aluno a ser atualizado: ");
    scanf("%d", &id);

    // Coleta dos novos dados do aluno
    printf("Novo nome do aluno: ");
    scanf(" %[^\n]", aluno.nome);
    printf("Nova matr�cula: ");
    scanf("%d", &aluno.matricula);
    printf("Novo ano de ingresso: ");
    scanf("%d", &aluno.anoIngresso);
    printf("Novo curso: ");
    scanf(" %[^\n]", aluno.curso);

    // Montando a query SQL para atualizar o aluno
    sprintf(query, "UPDATE Aluno SET nome='%s', matricula=%d, anoIngresso=%d, curso='%s' WHERE id=%d", 
            aluno.nome, aluno.matricula, aluno.anoIngresso, aluno.curso, id);

    // Executando a query no banco de dados
    if (mysql_query(conexao, query)) {
        printf("Erro ao atualizar aluno: %s\n", mysql_error(conexao));
    } else {
        printf("Aluno atualizado com sucesso!\n");
    }
}

// Fun��o para deletar um aluno do banco de dados
void deletar_aluno(MYSQL *conexao) {
    int id;
    char query[256];

    // Coleta do ID do aluno que ser� deletado
    printf("ID do aluno a ser deletado: ");
    scanf("%d", &id);

    // Montando a query SQL para deletar o aluno
    sprintf(query, "DELETE FROM Aluno WHERE id=%d", id);

    // Executando a query no banco de dados
    if (mysql_query(conexao, query)) {
        printf("Erro ao deletar aluno: %s\n", mysql_error(conexao));
    } else {
        printf("Aluno deletado com sucesso!\n");
    }
}

// Fun��o para listar todos os alunos do banco de dados
void listar_alunos(MYSQL *conexao) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[256];

    // Montando a query SQL para listar todos os alunos
    sprintf(query, "SELECT * FROM Aluno");

    // Executando a query no banco de dados
    if (mysql_query(conexao, query)) {
        printf("Erro ao listar alunos: %s\n", mysql_error(conexao));
        return;
    }

    // Pegando o resultado da query
    result = mysql_store_result(conexao);

    if (result == NULL) {
        printf("Erro ao obter os resultados: %s\n", mysql_error(conexao));
        return;
    }

    // Exibindo os dados dos alunos
    printf("\n--- Lista de Alunos ---\n");
    printf("ID\tNome\tMatr�cula\tAno de Ingresso\tCurso\n");

    while ((row = mysql_fetch_row(result))) {
        printf("%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
    }

    // Liberando o resultado
    mysql_free_result(result);
}

int main() {
    MYSQL conexao;
    int opcao;

    // Inicializando conex�o com o MySQL
    mysql_init(&conexao);

    // Tentando estabelecer conex�o com o banco de dados
    if (mysql_real_connect(&conexao, "localhost", "root", "Gabibi89*", "alunodb", 3306, NULL, 0)) {
        printf("\nConexao ao banco realizada com sucesso!\n");
    } else {
        printf("Falha de conexao: %s\n", mysql_error(&conexao));
        return 1; // Saindo do programa em caso de falha na conex�o
    }

    // La�o principal do programa, exibindo o menu at� o usu�rio optar por sair
    do {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Inserir Aluno foi selecionado.\n");
                inserir_aluno(&conexao);  // Chama a fun��o de inserir aluno
                break;

            case 2:
                printf("Atualizar Aluno foi selecionado.\n");
                atualizar_aluno(&conexao);  // Chama a fun��o de atualizar aluno
                break;

            case 3:
                printf("Deletar Aluno foi selecionado.\n");
                deletar_aluno(&conexao);  // Chama a fun��o de deletar aluno
                break;

            case 4:
                printf("Listar Alunos foi selecionado.\n");
                listar_alunos(&conexao);  // Chama a fun��o de listar alunos
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Op��o inv�lida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);  // O programa continuar� executando at� o usu�rio escolher a op��o "Sair"

    // Fechar a conex�o com o banco de dados
    mysql_close(&conexao);

    return 0;
}

