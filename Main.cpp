#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//PROJETO SAURO

// Definições das estruturas
typedef struct aluno {
    int matricula;
    char nome[50];
    int idCurso;
    bool pagamento;
    struct tm dataMensalidade;
} Aluno;

typedef struct curso {
    int idCurso;
    char nome[50];
    char turno[10];
    int mensalidade;
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
int loginAluno(Lista *listaAlunos, Lista *listaCursos);
void salvarMatriculas(Lista *listaAlunos);
void salvarCursos(Lista *listaCursos);
bool verificarMatriculaSalva(int matricula);
void adicionarMatriculaSalva(int matricula);
int carregarUltimoId(Lista *lista, int opcao);
void salvarUltimaMatricula(int matricula);
void carregarMatriculasSalvas(Lista *listaAlunos);
void carregarCursosSalvos(Lista *listaCursos);
void efetuarPagamento(Lista *listaAlunos, Lista *listaCursos, int matricula);
bool matricularAluno(Lista *listaCursos, Lista *listaAlunos, int matricula, int idCurso);
No* encontrarCurso(Lista *listaCursos, int id);
No* encontrarAluno(Lista *listaAlunos, int matricula);

// Função principal
int main(void) {
    bool continuar = true;
    int escolha;
    int matricula = 0;

    // Inicialização das listas
    Lista listaAlunos = {NULL, NULL};
    Lista listaCursos = {NULL, NULL};

    // Carregar matrículas salvas
    carregarMatriculasSalvas(&listaAlunos);
    
     // Carregar cursos salvos
    carregarCursosSalvos(&listaCursos);

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
                        printf("  5. Sair como admin\n\n");
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
								salvarCursos(&listaCursos);
                                continuar = false;
                                break;
                        }

                        if (escolha == 5) {
                            break;
                        }
                    }
                }
                break;

            case 2:
            	matricula = loginAluno(&listaAlunos, &listaCursos);
                if (matricula != 0) {
                    // Menu do aluno
                    while (1) {
                        printf("==========\n Menu do Aluno\n\n");
                        printf(" Escolha uma das opcoes a seguir:\n");
                        printf("  1. Cursos disponiveis\n");
                        printf("  2. Pagar mensalidade\n");
                        printf("  3. Sair como aluno\n\n");
                        printf("Opcao selecionada: ");
                        scanf("%d", &escolha);
                        system("cls");

                        switch (escolha) {
                            case 1:
                                listarCursos(&listaCursos);
                                int idCurso;
                                
                                printf("\nEscolha um curso para matricular pelo id: ");
                                scanf("%d", &idCurso);
                                matricularAluno(&listaCursos, &listaAlunos, matricula, idCurso);
                                break;

                            case 2:
                            	efetuarPagamento(&listaAlunos, &listaCursos, matricula);
                                break;

                            case 3:
                            	salvarMatriculas(&listaAlunos);
								salvarCursos(&listaCursos);
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
    novoNo->aluno.matricula = carregarUltimoId(listaAlunos, 1);
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
    //salvarUltimaMatricula(novoNo->aluno.matricula + 1);
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

    novoCurso.idCurso = carregarUltimoId(listaCursos, 2);
    
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
        printf("Matricula: %d, Nome: %s, Curso: %d, Pagamento: %d\n", atual->aluno.matricula, atual->aluno.nome, atual->aluno.idCurso, atual->aluno.pagamento);
        atual = atual->proximo;
    }
}

// Função para listar cursos (exclusivo do administrador)
void listarCursos(Lista *listaCursos) {
    printf("Lista de Cursos:\n");
    No *atual = listaCursos->primeiro;
    while (atual != NULL) {
        printf("ID: %d, Nome: %s, Turno: %s, Mensalidade: %d\n", atual->curso.idCurso, atual->curso.nome, atual->curso.turno, atual->curso.mensalidade);
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
        printf("\nCredenciais invalidas. Tente novamente.\n");
        return false;
    }
}

// autenticar aluno
int loginAluno(Lista *listaAlunos, Lista *listaCursos) {
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
        	No *cursoNode = encontrarCurso(listaCursos, atual->aluno.idCurso);
        	char cursoNome[50] = "Sem curso";
        	if (cursoNode != NULL) {
        		strcpy(cursoNome, cursoNode->curso.nome);
			}
            printf("\nLogin de aluno bem-sucedido!\n");
            printf("Aluno: %s, Curso: %s, Dias ate o vencimento da mensalidade: %d, pagamento em dia: %d\n\n", atual->aluno.nome, cursoNome, 0, atual->aluno.pagamento);
            return matricula;
        }
        atual = atual->proximo;
    }

    printf("\nAluno nao cadastrado ou credenciais incorretas. Entre em contato com o administrador.\n");
    return 0;
}

void salvarMatriculas(Lista *listaAlunos) {
    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "w"); // Modo de adição ao invés de escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "%d %s %d %d\n", atual->aluno.matricula, atual->aluno.nome, atual->aluno.idCurso, atual->aluno.pagamento);
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
        fprintf(arquivo, "%d %s %s %d\n", atual->curso.idCurso, atual->curso.nome, atual->curso.turno, atual->curso.mensalidade);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Cursos cadastrados salvos com sucesso!\n");
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
    int idCurso;
    bool pagamento;

    while (fscanf(arquivo, "%d %s %d %d", &matricula, &nome, &idCurso, &pagamento) != EOF) {
        // Criar novo nó com os dados carregados
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL) {
            printf("\nErro: Memoria insuficiente!\n");
            exit(1);
        }

        novoNo->aluno.matricula = matricula;
        strcpy(novoNo->aluno.nome, nome);
        novoNo->aluno.idCurso = idCurso; // Atribui 0 como id do curso inicialmente
        novoNo->aluno.pagamento = pagamento; // Atribui false como pagamento inicialmente
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
    FILE *arquivo;
    arquivo = fopen("cursos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    
    int idCurso;
    char nome[50];
    char turno[10];
    int mensalidade;
    
    while (fscanf(arquivo, "%d %s %s %d", &idCurso, &nome, &turno, &mensalidade) != EOF) {
        // Criar novo nó com os dados carregados
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL) {
            printf("\nErro: Memoria insuficiente!\n");
            exit(1);
        }

        novoNo->curso.idCurso = idCurso;
        strcpy(novoNo->curso.nome, nome);
        strcpy(novoNo->curso.turno, turno);
        novoNo->curso.mensalidade = mensalidade;
        novoNo->proximo = NULL;

        // Insere o novo nó na lista de alunos
        if (listaCursos->primeiro == NULL) {
            listaCursos->primeiro = novoNo;
            listaCursos->ultimo = novoNo;
        } else {
            listaCursos->ultimo->proximo = novoNo;
            listaCursos->ultimo = novoNo;
        }
    }

    fclose(arquivo);
}

void efetuarPagamento(Lista *listaAlunos, Lista *listaCursos, int matricula){
    time_t current_time = time(NULL);
    No *atual = listaAlunos->primeiro;
    
    while (atual != NULL) {
        if (atual->aluno.matricula == matricula) {
            atual->aluno.dataMensalidade = *localtime(&current_time);
            atual->aluno.pagamento = true;
            No *cursoNode = encontrarCurso(listaCursos, atual->aluno.idCurso);
            printf("Pagamento de R$%d realizado - %02d-%02d-%02d", cursoNode->curso.mensalidade, atual->aluno.dataMensalidade.tm_mday, atual->aluno.dataMensalidade.tm_mon, atual->aluno.dataMensalidade.tm_year);
            return;
        }
        atual = atual->proximo;
    }
}

bool matricularAluno(Lista *listaCursos, Lista *listaAlunos, int matricula, int idCurso){
	No *cursoNode = encontrarCurso(listaCursos, idCurso);
	if (cursoNode != NULL) {
		No *alunoNode = encontrarAluno(listaAlunos, matricula);
		alunoNode->aluno.idCurso = idCurso;
		printf("Aluno matriculado em %s", cursoNode->curso.nome);
		return true;
	}
	
	printf("Curso nao encontrado.");
	return false;
}

No* encontrarCurso(Lista *listaCursos, int id) {
    No *atual = listaCursos->primeiro;
    while (atual != NULL) {
        if (atual->curso.idCurso == id) {
            //printf("ID: %d, Nome: %s, Turno: %s, Mensalidade: %.2f\n", atual->curso.idCurso, atual->curso.nome, atual->curso.turno, atual->curso.mensalidade);
            return atual;
        }
        atual = atual->proximo;
    }
    printf("curso nao encontrado\n", id);
    return NULL; 
}

No* encontrarAluno(Lista *listaAlunos, int matricula) {
    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
        if (atual->aluno.matricula == matricula) {
            //printf("ID: %d, Nome: %s, Turno: %s, Mensalidade: %.2f\n", atual->curso.idCurso, atual->curso.nome, atual->curso.turno, atual->curso.mensalidade);
            return atual;
        }
        atual = atual->proximo;
    }
    printf("aluno nao encontrado\n", matricula);
    return NULL; 
}

int carregarUltimoId(Lista *lista, int opcao){
	No *atual = lista->primeiro;
	switch (opcao){
		case 1: // aluno
		    if (atual == NULL) {
		        return 1; // Se a lista estiver vazia, retorna -1 ou outro valor indicativo de erro
		    }
		
		    while (atual->proximo != NULL) {
		        atual = atual->proximo;
		    }
		    return atual->aluno.matricula + 1;
		
		case 2: //curso
		    if (atual == NULL) {
		        return 1; // Se a lista estiver vazia, retorna -1 ou outro valor indicativo de erro
		    }
		
		    while (atual->proximo != NULL) {
		        atual = atual->proximo;
		    }
		    return atual->curso.idCurso + 1;
	}
	return -1;
}