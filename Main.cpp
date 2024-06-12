#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//PROJETO SAURO

// Definições das estruturas
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
void cadastrarAluno(Lista *listaAlunos);
void cadastrarCurso(Lista *listaCursos);
void listarAlunos(Lista *listaAlunos);
void listarCursos(Lista *listaCursos);
bool loginAdmin();
bool loginAluno(Lista *listaAlunos);
void salvarMatriculas(Lista *listaAlunos);
void salvarCursos(Lista *listaCursos);
bool verificarMatriculaSalva(int matricula);
void adicionarMatriculaSalva(int matricula);
int carregarUltimaMatricula();
void salvarUltimaMatricula(int matricula);
void carregarMatriculasSalvas(Lista *listaAlunos);
void carregarCursosSalvos(Lista *listaCursos);

// Função principal
int main(void) {
    bool continuar = true;
    int escolha;

    // Inicialização das listas
    Lista listaAlunos = {NULL, NULL};
    Lista listaCursos = {NULL, NULL};

    // Carregar matrículas salvas
    carregarMatriculasSalvas(&listaAlunos);
    
     // Carregar cursos salvos
    carregarCursosSalvos(&listaCursos);


    int matriculaNova = carregarUltimaMatricula() + 1;

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
                        printf("  4. Listar cursos\n");
                        printf("  5. Salvar ultimos alunos cadastrados.\n");
                        printf("  6. Salvar cursos cadastrados.\n");
                        printf("  7. Sair como admin\n\n");
                        printf("Opcao selecionada: ");
                        scanf("%d", &escolha);
                        system("cls");

                        switch (escolha) {
                            case 1:
                                cadastrarAluno(&listaAlunos);
                                break;

                            case 2:
                                cadastrarCurso(&listaCursos);
                                break;

                            case 3:
                                listarAlunos(&listaAlunos);
                                break;

                            case 4:
                                listarCursos(&listaCursos);
                                break;

                            case 5:
                                salvarMatriculas(&listaAlunos);
                                break;

                            case 6:
                                salvarCursos(&listaCursos);
                                break;

                            case 7:
                                continuar = false; // Sair do loop do administrador e voltar ao menu principal
                                break;
                        }

                        if (escolha == 7) {
                            break;
                        }
                    }
                }
                break;

            case 2:
                if (loginAluno(&listaAlunos)) {
                    // Menu do aluno
                    while (1) {
                        printf("==========\n Menu do Aluno\n\n");
                        printf(" Escolha uma das opcoes a seguir:\n");
                        printf("  1. Visualizar cursos disponiveis\n");
                        printf("  2. Escolher curso e pagar mensalidade\n");
                        printf("  3. Sair como aluno\n\n");
                        printf("Opcao selecionada: ");
                        scanf("%d", &escolha);
                        system("cls");

                        switch (escolha) {
                            case 1:
                                listarCursos(&listaCursos);
                                break;

                            case 2:
                                // Implemente aqui a lógica para escolher um curso e pagar a mensalidade
                                break;

                            case 3:
                                continuar = false; // Sair do loop do aluno e voltar ao menu principal
                                break;
                        }

                        if (escolha == 3) {
                            break;
                        }
                    }
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
void cadastrarAluno(Lista *listaAlunos) {
    printf("==========\n Cadastro de Aluno\n\n");
    printf("Nome: ");
    char nome[50];
    scanf("%s", nome);

    // Caso o aluno não esteja cadastrado, cria um novo registro
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\nErro: Memoria insuficiente!\n");
        exit(1);
    }

    strcpy(novoNo->aluno.nome, nome);
    novoNo->aluno.matricula = carregarUltimaMatricula();
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

    printf("\nAluno cadastrado com sucesso!\n");

    // Incrementa a matrícula
    salvarUltimaMatricula(novoNo->aluno.matricula + 1);
}

// Função para cadastrar curso (exclusivo do administrador)
void cadastrarCurso(Lista *listaCursos) {
    Curso novoCurso;

    printf("==========\n Cadastro de Curso\n\n");
    printf("Nome do curso: ");
    getchar(); // Limpar o buffer de entrada antes de usar fgets()
    fgets(novoCurso.nome, sizeof(novoCurso.nome), stdin);
    novoCurso.nome[strcspn(novoCurso.nome, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Turno do curso: ");
    scanf("%s", novoCurso.turno);

    printf("Valor da mensalidade: ");
    scanf("%f", &novoCurso.mensalidade);

    novoCurso.idCurso = listaCursos->ultimo != NULL ? listaCursos->ultimo->curso.idCurso + 1 : 1;
    
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\nErro: Memoria insuficiente!\n");
        exit(1);
    }
    
    novoNo->curso = novoCurso;
    novoNo->proximo = NULL;

    if (listaCursos->primeiro == NULL) {
        listaCursos->primeiro = novoNo;
        listaCursos->ultimo = novoNo;
    } else {
        listaCursos->ultimo->proximo = novoNo;
        listaCursos->ultimo = novoNo;
    }

    printf("\nCurso cadastrado com sucesso!\n");
}

// Função para listar alunos (exclusivo do administrador)
void listarAlunos(Lista *listaAlunos) {
    printf("Lista de Alunos:\n");
    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
        printf("Matricula: %d, Nome: %s\n", atual->aluno.matricula, atual->aluno.nome);
        atual = atual->proximo;
    }
}

// Função para listar cursos (exclusivo do administrador)
void listarCursos(Lista *listaCursos) {
    printf("Lista de Cursos:\n");
    No *atual = listaCursos->primeiro;
    while (atual != NULL) {
        printf("ID: %d, Nome: %s, Turno: %s, Mensalidade: %.2f\n", atual->curso.idCurso, atual->curso.nome, atual->curso.turno, atual->curso.mensalidade);
        atual = atual->proximo;
    }
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

    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
        if (atual->aluno.matricula == matricula && strcmp(atual->aluno.nome, nome) == 0) {
            printf("\nLogin de aluno bem-sucedido!\n");
            return true;
        }
        atual = atual->proximo;
    }

    printf("\nAluno nao cadastrado ou credenciais incorretas. Entre em contato com o administrador.\n");
    return false;
}

// Lista para armazenar as matrículas já salvas
Lista matriculasSalvas = {NULL, NULL};

void salvarMatriculas(Lista *listaAlunos) {
    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "a"); // Modo de adição ao invés de escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
        // Verifica se a matrícula atual já foi salva
        if (!verificarMatriculaSalva(atual->aluno.matricula)) {
            fprintf(arquivo, "%d %s\n", atual->aluno.matricula, atual->aluno.nome);
            // Adiciona a matrícula à lista de matrículas salvas
            adicionarMatriculaSalva(atual->aluno.matricula);
        }
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Matriculas dos alunos salvas com sucesso!\n");
}

// Função para salvar cursos cadastrados
void salvarCursos(Lista *listaCursos) {
    FILE *arquivo;
    arquivo = fopen("cursos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    No *atual = listaCursos->primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "%d %s %s %.2f\n", atual->curso.idCurso, atual->curso.nome, atual->curso.turno, atual->curso.mensalidade);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Cursos cadastrados salvos com sucesso!\n");
}

// Função para verificar se uma matrícula já foi salva
bool verificarMatriculaSalva(int matricula) {
    No *atual = matriculasSalvas.primeiro;
    while (atual != NULL) {
        if (atual->aluno.matricula == matricula) {
            return true; // Matrícula já foi salva
        }
        atual = atual->proximo;
    }
    return false; // Matrícula ainda não foi salva
}

// Função para adicionar uma matrícula à lista de matrículas salvas
void adicionarMatriculaSalva(int matricula) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\nErro: Memoria insuficiente!\n");
        exit(1);
    }
    novoNo->aluno.matricula = matricula;
    novoNo->proximo = NULL;

    if (matriculasSalvas.primeiro == NULL) {
        matriculasSalvas.primeiro = novoNo;
        matriculasSalvas.ultimo = novoNo;
    } else {
        matriculasSalvas.ultimo->proximo = novoNo;
        matriculasSalvas.ultimo = novoNo;
    }
}

// Função para carregar a última matrícula salva
int carregarUltimaMatricula() {
    FILE *arquivo;
    arquivo = fopen("ultima_matricula.txt", "r");
    if (arquivo == NULL) {
        return 0; // Se o arquivo não existir, retorna 0
    }

    int ultimaMatricula;
    fscanf(arquivo, "%d", &ultimaMatricula);
    fclose(arquivo);

    return ultimaMatricula;
}

// Função para salvar a última matrícula utilizada
void salvarUltimaMatricula(int matricula) {
    FILE *arquivo;
    arquivo = fopen("ultima_matricula.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "%d", matricula);
    fclose(arquivo);
}

// Função para carregar as matrículas salvas
void carregarMatriculasSalvas(Lista *listaAlunos) {
    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    int matricula;
    char nome[50];

    while (fscanf(arquivo, "%d %s", &matricula, nome) != EOF) {
        // Criar novo nó com os dados carregados
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL) {
            printf("\nErro: Memoria insuficiente!\n");
            exit(1);
        }

        novoNo->aluno.matricula = matricula;
        strcpy(novoNo->aluno.nome, nome);
        novoNo->aluno.idCurso = 0; // Atribui 0 como id do curso inicialmente
        novoNo->aluno.pagamento = false; // Atribui false como pagamento inicialmente
        novoNo->proximo = NULL;

        // Insere o novo nó na lista de alunos
        if (listaAlunos->primeiro == NULL) {
            listaAlunos->primeiro = novoNo;
            listaAlunos->ultimo = novoNo;
        } else {
            listaAlunos->ultimo->proximo = novoNo;
            listaAlunos->ultimo = novoNo;
        }
    }

    fclose(arquivo);
}

void carregarCursosSalvos(Lista *listaCursos) {
// criar depois função para carregar automaticamnete cursos que foram salvos anteriormente.
}

