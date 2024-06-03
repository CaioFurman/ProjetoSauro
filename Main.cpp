#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>


//Projeto SAURO

int totalAlunos = 0;

typedef struct aluno {
    int matricula;
    char nome[50];
    int idCurso;
    bool pagamento;
} Aluno;

typedef struct curso {
    int idCurso;
    char nome[50];
    char turno[10];
    float mensalidade;
} Curso;

typedef struct no {
    Aluno aluno;
    Curso curso;
    struct no *proximo;
} No;

typedef struct lista {
    No *primeiro;
    No *ultimo;
} Lista;

// Protótipos de funções
void cadastrarAluno(Lista *listaAlunos, int *matriculaNova);
void cadastrarCurso(Lista *listaCursos, int *cursoNovo);
void listarAlunos(Lista *listaAlunos);
bool loginAdmin();
bool loginAluno(Lista *listaAlunos);
void salvarMatriculas(Lista *listaAlunos);

int main(void) {
    int matriculaNova = 1;
    int cursoNovo = 1;
    bool continuar = true;
    int escolha;

    // Inicialização das listas
    Lista listaAlunos = {NULL, NULL};
    Lista listaCursos = {NULL, NULL};

    while (continuar) {
        printf("==========\n Bem-vindo ao Sistema de Gestao Academica\n\n");
        printf(" Escolha uma das opcoes a seguir:\n");
        printf("  1. Login de Administrador\n");
        printf("  2. Login de Aluno\n");
        printf("  3. Sair\n\n");
        printf("Opcao selecionada: ");
        scanf("%d", &escolha);
        system("cls");

        switch (escolha) {
            case 1:
                if (loginAdmin()) {
                    // Menu do administrador
                    while (1) {
                        printf("==========\n Menu do Administrador\n\n");
                        printf(" Escolha uma das opcoes a seguir:\n");
                        printf("  1. Cadastrar aluno\n");
                        printf("  2. Cadastrar curso\n");
                        printf("  3. Listar alunos\n");
                        printf("  4. Sair \n\n");
                        printf("Opcao selecionada: ");
                        scanf("%d", &escolha);
                        system("cls");

                        switch (escolha) {
                            case 1:
                                cadastrarAluno(&listaAlunos, &matriculaNova);
                                break;

                            case 2:
                                cadastrarCurso(&listaCursos, &cursoNovo);
                                break;

                            case 3:
                                listarAlunos(&listaAlunos);
                                break;

                            case 4:
                                salvarMatriculas(&listaAlunos);
    							break;
                            case 5:
                                break;
                        }

                        if (escolha == 5) {
                            break;
                        }
                    }
                }
                break;

            case 2:
                if (loginAluno(&listaAlunos)) {
                    // Menu do aluno
                    printf("==========\n Menu do Aluno\n\n");
                    // Implemente aqui as opções do menu do aluno
                }
                break;

            case 3:
                continuar = false;
                break;

            default:
                printf("Opcao invalida.\n\n");
                break;
        }
    }

    return 0;
}

// Função para cadastrar aluno (exclusivo do administrador)
void cadastrarAluno(Lista *listaAlunos, int *matriculaNova) {
    printf("==========\n Cadastro de Aluno\n\n");
    printf("Nome: ");
    char nome[50];
    scanf("%s", nome);

    // Verifica se o aluno já está cadastrado
    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->aluno.nome, nome) == 0) {
            printf("\nEste aluno ja esta cadastrado.\n");
            return;
        }
        atual = atual->proximo;
    }

    // Caso o aluno não esteja cadastrado, cria um novo registro
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\nErro: Memoria insuficiente!\n");
        exit(1);
    }

    strcpy(novoNo->aluno.nome, nome);
    novoNo->aluno.matricula = (*matriculaNova)++;
    novoNo->aluno.idCurso = 0;
    novoNo->aluno.pagamento = false;
    novoNo->proximo = NULL;

    // Insere o novo nó na lista de alunos
    if (listaAlunos->primeiro == NULL) {
        listaAlunos->primeiro = novoNo;
        listaAlunos->ultimo = novoNo;
    } else {
        listaAlunos->ultimo->proximo = novoNo;
        listaAlunos->ultimo = novoNo;
    }

    totalAlunos++; // Incrementa o total de alunos cadastrados
    printf("\nAluno cadastrado com sucesso!\n");
}

// Função para cadastrar curso (exclusivo do administrador)
void cadastrarCurso(Lista *listaCursos, int *cursoNovo) {
    // Implementação da função de cadastro de curso
}

// Função para listar alunos (exclusivo do administrador)
void listarAlunos(Lista *listaAlunos) {
    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    printf("Lista de Alunos:\n");
    int matriculaArquivo;
    char nomeArquivo[50];
    while (fscanf(arquivo, "%d %s", &matriculaArquivo, nomeArquivo) != EOF) {
        printf("Matricula: %d, Nome: %s\n", matriculaArquivo, nomeArquivo);
    }

    fclose(arquivo);
}

// autenticar administrador
bool loginAdmin() {
    char username[20];
    char password[20];

    printf("==========\n Login de Administrador\n\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // autenticação
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("\nLogin de administrador bem-sucedido!\n");
        return true;
    } else {
        printf("\nCredenciais inválidas. Tente novamente.\n");
        return false;
    }
}

// autenticar aluno
bool loginAluno(Lista *listaAlunos) {
    int matricula;
    char nome[50];

    printf("==========\n Login de Aluno\n\n");
    printf("Matricula: ");
    scanf("%d", &matricula);
    printf("Nome: ");
    scanf("%s", nome);

    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return false;
    }

    int matriculaArquivo;
    char nomeArquivo[50];
    bool encontrado = false;
    while (fscanf(arquivo, "%d %s", &matriculaArquivo, nomeArquivo) != EOF) {
        if (matriculaArquivo == matricula && strcmp(nomeArquivo, nome) == 0) {
            encontrado = true;
            break;
        }
    }

    fclose(arquivo);

    if (encontrado) {
        printf("\nLogin de aluno bem-sucedido!\n");
        return true;
    } else {
        printf("\nAluno nao cadastrado ou credenciais incorretas. Entre em contato com o administrador.\n");
        return false;
    }
}

// Função para salvar as matrículas dos alunos em um arquivo TXT
void salvarMatriculas(Lista *listaAlunos) {
    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "a"); // Modo de adição ao invés de escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "%d %s\n", atual->aluno.matricula, atual->aluno.nome);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Matriculas dos alunos salvas com sucesso!\n");
}
