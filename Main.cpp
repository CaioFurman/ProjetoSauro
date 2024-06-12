#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
void carregarCursosSalvos(Lista *listaCursos);
bool verificarMatriculaSalva(int matricula);
void adicionarMatriculaSalva(int matricula);
int carregarUltimaMatricula();
void salvarUltimaMatricula(int matricula);

// Função principal
int main(void) {
    bool continuar = true;
    int escolha;

    // Inicialização das listas
    Lista listaAlunos = {NULL, NULL};
    Lista listaCursos = {NULL, NULL};

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
                        printf("  4. Listar cursos\n"); // Adicionando a opção de listar cursos
                        printf("  5. Salvar ultimas matriculas feitas.\n");
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
                                listarCursos(&listaCursos); // Adicionando a chamada para listar cursos
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
    getchar(); // Limpar o buffer de entrada

    printf("==========\n Login de Aluno\n\n");
    printf("Matricula: ");
    scanf("%d", &matricula);

    printf("Nome: ");
    getchar(); // Limpar o buffer de entrada
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remover o caractere de nova linha

    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de matriculas.\n");
        return false;
    }

    int matriculaArquivo;
    char nomeArquivo[50];
    bool encontrado = false;

    while (fscanf(arquivo, "%d %s\n", &matriculaArquivo, nomeArquivo) == 2) {
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


// Função para salvar matrículas
void salvarMatriculas(Lista *listaAlunos) {
    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "a");
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

// Função para salvar cursos
void salvarCursos(Lista *listaCursos) {
    FILE *arquivo;
    arquivo = fopen("cursos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    No *atual = listaCursos->primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "%d \"%s\" \"%s\" %.2f\n", atual->curso.idCurso, atual->curso.nome, atual->curso.turno, atual->curso.mensalidade);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Cursos cadastrados salvos com sucesso!\n");
}

// Função para carregar cursos salvos
void carregarCursosSalvos(Lista *listaCursos) {
    FILE *arquivo;
    arquivo = fopen("cursos.txt", "r");
    if (arquivo == NULL) {
        return;
    }

    Curso novoCurso;
    while (fscanf(arquivo, "%d \"%[^\"]\" \"%[^\"]\" %f\n", &novoCurso.idCurso, novoCurso.nome, novoCurso.turno, &novoCurso.mensalidade) == 4) {
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
    }

    fclose(arquivo);
    printf("Cursos cadastrados carregados com sucesso!\n");
}

// Função para verificar se uma matrícula já foi salva
bool verificarMatriculaSalva(int matricula) {
    // Implemente aqui a lógica para verificar se a matrícula já foi salva
}

// Função para adicionar uma matrícula à lista de matrículas salvas
void adicionarMatriculaSalva(int matricula) {
    // Implemente aqui a lógica para adicionar a matrícula à lista de matrículas salvas
}

// Função para carregar a última matrícula salva
int carregarUltimaMatricula() {
    // Implemente aqui a lógica para carregar a última matrícula salva
}

// Função para salvar a última matrícula utilizada
void salvarUltimaMatricula(int matricula) {
    // Implemente aqui a lógica para salvar a última matrícula utilizada
}

