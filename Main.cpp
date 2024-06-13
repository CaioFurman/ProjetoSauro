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
    int totalAlunos;
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
void listarCursos(Lista *listaCursos, Lista *listaAlunos);
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
void infoUsuario(Lista *listaCursos, Lista *listaAlunos, int matricula);
bool verificaVencimento(int dia, int mes, int ano);
void contarAlunosPorCurso(Lista *listaCursos, Lista *listaAlunos);
void editarCursoPorId(Lista *listaCursos, int id);
void deletarCursoPorId(Lista *listaCursos, int id);
void editarAlunoPorId(Lista *listaAlunos, int id);
void deletarAlunoPorId(Lista *listaAlunos, int id);
void selectionSortTotal(Lista *listaCursos);
void selectionSortID(Lista *listaCursos);
void listarInadimplentes(Lista *listaAlunos);
No* encontrarCurso(Lista *listaCursos, int id);
No* encontrarAluno(Lista *listaAlunos, int matricula);

// Função principal
int main(void) {
    bool continuar = true;
    int escolha;
    int matricula = 0;
    int id = 0;

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
                        printf("  5. Listar inadimplentes\n");
                        printf("  6. Sair como admin\n\n");
                        printf("Opcao selecionada: ");
                        scanf("%d", &escolha);
                        getchar();
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
                                printf("==========\n Quer modificar algum Aluno?\n\n");
		                        printf(" Escolha uma das opcoes a seguir:\n");
		                        printf("  1. Deletar por ID\n");
		                        printf("  2. Editar por ID\n");
		                        printf("  3. Sair \n");
		                        printf("Opcao selecionada: ");
		                        scanf("%d", &escolha);
		                        switch (escolha) {
		                        	case 1:
		                        		fflush(stdin);
		                        		printf("\n\nInsira o ID: ");
		                        		scanf("%d", &id);
		                        		deletarAlunoPorId(&listaAlunos, id);
		                        		break;
		                        	case 2:
		                        		fflush(stdin);
		                        		printf("\n\nInsira o ID: ");
		                        		scanf("%d", &id);
		                        		editarAlunoPorId(&listaAlunos, id);
		                        		break;
		                        	case 3:
		                        		system("cls");
		                        		break;
		                    	}
                                break;

                            case 4:
                                listarCursos(&listaCursos, &listaAlunos);
                                printf("==========\n Quer modificar algum curso?\n\n");
		                        printf(" Escolha uma das opcoes a seguir:\n");
		                        printf("  1. Deletar por ID\n");
		                        printf("  2. Editar por ID\n");
		                        printf("  3. Visualizacao ordenada\n");
		                        printf("  4. Sair \n");
		                        printf("Opcao selecionada: ");
		                        scanf("%d", &escolha);
		                        switch (escolha) {
		                        	case 1:
		                        		fflush(stdin);
		                        		printf("\n\nInsira o ID: ");
		                        		scanf("%d", &id);
		                        		deletarCursoPorId(&listaCursos, id);
		                        		break;
		                        	case 2:
		                        		fflush(stdin);
		                        		printf("\n\nInsira o ID: ");
		                        		scanf("%d", &id);
		                        		editarCursoPorId(&listaCursos, id);
		                        		break;
		                        	case 3:
		                        		system("cls");
		                        		selectionSortTotal(&listaCursos);
		                        		listarCursos(&listaCursos, &listaAlunos);
		                        		break;
		                        	case 4:
		                        		selectionSortID(&listaCursos);
		                        		system("cls");
		                        		break;
		                        }
                                break;

                            case 5:
                            	listarInadimplentes(&listaAlunos);
                                break;
                            
                            case 6:
                            	system("cls");
                            	break;
                        }

                        if (escolha == 6) {
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
                    	infoUsuario(&listaCursos, &listaAlunos, matricula);
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
                                listarCursos(&listaCursos, &listaAlunos);
                                int idCurso;
                                
                                printf("\nEscolha um curso para matricular pelo id: ");
                                scanf("%d", &idCurso);
                                matricularAluno(&listaCursos, &listaAlunos, matricula, idCurso);
                                break;

                            case 2:
                            	efetuarPagamento(&listaAlunos, &listaCursos, matricula);
                                break;

                            case 3:
                            	system("cls");
                                break;
                        }

                        if (escolha == 3) {
                            break;
                        }
                    }
                }
                break;

            case 3:
            	salvarMatriculas(&listaAlunos);
				salvarCursos(&listaCursos);
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
    novoNo->aluno.pagamento = true;
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
        printf("Matricula: %d Nome: %s IdCurso: %d Pagamento vencido: %d Data Mensalidade: %02d-%02d-%04d\n", atual->aluno.matricula, atual->aluno.nome, atual->aluno.idCurso, atual->aluno.pagamento, atual->aluno.dataMensalidade.tm_mday, atual->aluno.dataMensalidade.tm_mon+ 1, atual->aluno.dataMensalidade.tm_year + 1900);
        atual = atual->proximo;
    }
}

// Função para listar cursos (exclusivo do administrador)
void listarCursos(Lista *listaCursos, Lista *listaAlunos) {
	contarAlunosPorCurso(listaCursos, listaAlunos);
    printf("Lista de Cursos:\n");
    No *atual = listaCursos->primeiro;
    while (atual != NULL) {
        printf("ID: %d, Nome: %s, Turno: %s, Mensalidade: R$%d Alunos matriculados: %d\n", atual->curso.idCurso, atual->curso.nome, atual->curso.turno, atual->curso.mensalidade, atual->curso.totalAlunos);
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
    	system("cls");
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
			system("cls");
            printf("Login de aluno bem-sucedido!\n");
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
        fprintf(arquivo, "%d %s %d %02d-%02d-%04d %d\n", atual->aluno.matricula, atual->aluno.nome, atual->aluno.idCurso, atual->aluno.dataMensalidade.tm_mday, atual->aluno.dataMensalidade.tm_mon, atual->aluno.dataMensalidade.tm_year, atual->aluno.pagamento);
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
    int dia;
    int mes;
    int ano;

    while (fscanf(arquivo, "%d %s %d %02d-%02d-%04d %d\n", &matricula, &nome, &idCurso, &dia, &mes, &ano,  &pagamento) != EOF) {
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL) {
            printf("\nErro: Memoria insuficiente!\n");
            exit(1);
        }
        novoNo->aluno.matricula = matricula;
        strcpy(novoNo->aluno.nome, nome);
        novoNo->aluno.idCurso = idCurso;
        novoNo->aluno.pagamento = pagamento; 
        novoNo->aluno.dataMensalidade.tm_mday = dia;
		novoNo->aluno.dataMensalidade.tm_mon = mes; 
		novoNo->aluno.dataMensalidade.tm_year = ano;
        novoNo->proximo = NULL;

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
        	if (atual->aluno.dataMensalidade.tm_year == 1900){
        		atual->aluno.dataMensalidade = *localtime(&current_time);
			}
            atual->aluno.pagamento = false;
            No *cursoNode = encontrarCurso(listaCursos, atual->aluno.idCurso);
        	system("cls");
            printf("Pagamento de R$%d realizado - %02d-%02d-%04d \n\n", cursoNode->curso.mensalidade, atual->aluno.dataMensalidade.tm_mday, atual->aluno.dataMensalidade.tm_mon+ 1, atual->aluno.dataMensalidade.tm_year + 1900);
            atual->aluno.dataMensalidade.tm_mon++;
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
		system("cls");
		printf("Aluno matriculado em %s\n\n", cursoNode->curso.nome);
		return true;
	}
	
	return false;
}

No* encontrarCurso(Lista *listaCursos, int id) {
    No *atual = listaCursos->primeiro;
    while (atual != NULL) {
        if (atual->curso.idCurso == id) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL; 
}

No* encontrarAluno(Lista *listaAlunos, int matricula) {
    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
        if (atual->aluno.matricula == matricula) {
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
		        return 1; 
		    }
		
		    while (atual->proximo != NULL) {
		        atual = atual->proximo;
		    }
		    return atual->aluno.matricula + 1;
		
		case 2: //curso
		    if (atual == NULL) {
		        return 1; 
		    }
		
		    while (atual->proximo != NULL) {
		        atual = atual->proximo;
		    }
		    return atual->curso.idCurso + 1;
	}
	return -1;
}

void infoUsuario(Lista *listaCursos, Lista *listaAlunos, int matricula){
	    No *usuario = encontrarAluno(listaAlunos, matricula);
        No *cursoNode = encontrarCurso(listaCursos, usuario->aluno.idCurso);
        int diaVencimento = usuario->aluno.dataMensalidade.tm_mday;
		int mesVencimento = usuario->aluno.dataMensalidade.tm_mon + 1;
		int anoVencimento = usuario->aluno.dataMensalidade.tm_year + 1900;
    	char cursoNome[50] = "Sem curso";
    	if (cursoNode != NULL) {
    		strcpy(cursoNome, cursoNode->curso.nome);
    		if (verificaVencimento(diaVencimento, mesVencimento, anoVencimento)){
    			usuario->aluno.pagamento = true;
			}
    		printf("Aluno: %s, Curso: %s, Data vencimento: %02d/%02d/%04d, pagamento vencido: %d\n\n", usuario->aluno.nome, cursoNome, diaVencimento, mesVencimento, anoVencimento, usuario->aluno.pagamento);
		} else{
			printf("Aluno: %s, Curso: %s\n\n", usuario->aluno.nome, cursoNome);
		}
}

bool verificaVencimento(int dia, int mes, int ano){
	time_t t = time(NULL);
    struct tm tm_atual = *localtime(&t);

    int diaAtual = tm_atual.tm_mday;
    int mesAtual = tm_atual.tm_mon + 1; 
    int anoAtual = tm_atual.tm_year + 1900; 

    // Verifica se a data atual é posterior ao último dia do mês de vencimento
    if (anoAtual > ano) {
        return true;
    } else if (anoAtual == ano) {
        if (mesAtual > mes) {
            return true;
        } else if (mesAtual == mes) {
            if (diaAtual > mes) {
                return true;
            }
        }
    }
    return false;
}

void deletarCursoPorId(Lista *listaCursos, int id) {
    if (listaCursos == NULL || listaCursos->primeiro == NULL) {
        printf("Lista de cursos vazia.\n");
        return;
    }

    No *anterior = NULL;
    No *atual = listaCursos->primeiro;

    while (atual != NULL) {
        if (atual->curso.idCurso == id) {
            // Found the course with the given ID
            if (anterior == NULL) {
                // If the course is the first node
                listaCursos->primeiro = atual->proximo;
            } else {
                // If the course is not the first node
                anterior->proximo = atual->proximo;
            }
            free(atual); // Free memory allocated to the deleted node
            system("cls");
            printf("Curso com ID %d deletado com sucesso.\n", id);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Curso com ID %d não encontrado.\n", id);
}

void editarCursoPorId(Lista *listaCursos, int id) {
    if (listaCursos == NULL || listaCursos->primeiro == NULL) {
        printf("Lista de cursos vazia.\n");
        return;
    }

    No *atual = listaCursos->primeiro;

    while (atual != NULL) {
        if (atual->curso.idCurso == id) {
        	system("cls");
        	printf("Curso: %s Turno: %s Mensalidade: %d\n\n", atual->curso.nome, atual->curso.turno, atual->curso.mensalidade);
            printf("Digite o novo nome do curso: ");
            scanf("%s", &atual->curso.nome); 
            printf("Digite o novo turno do curso: ");
            scanf("%s", &atual->curso.turno); 
            printf("Digite a nova mensalidade do curso: ");
            scanf("%d", &atual->curso.mensalidade);
            printf("Curso com ID %d editado com sucesso.\n", id);
            return;
        }
        atual = atual->proximo;
    }

    printf("Curso com ID %d não encontrado.\n", id);
}

void deletarAlunoPorId(Lista *listaAlunos, int id) {
    if (listaAlunos == NULL || listaAlunos->primeiro == NULL) {
        printf("Lista de cursos vazia.\n");
        return;
    }

    No *anterior = NULL;
    No *atual = listaAlunos->primeiro;

    while (atual != NULL) {
        if (atual->aluno.matricula == id) {
            // Found the course with the given ID
            if (anterior == NULL) {
                // If the course is the first node
                listaAlunos->primeiro = atual->proximo;
            } else {
                // If the course is not the first node
                anterior->proximo = atual->proximo;
            }
            free(atual); // Free memory allocated to the deleted node
            system("cls");
            printf("Aluno com ID %d deletado com sucesso.\n", id);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Aluno com ID %d não encontrado.\n", id);
}

void editarAlunoPorId(Lista *listaAlunos, int id) {
    if (listaAlunos == NULL || listaAlunos->primeiro == NULL) {
        printf("Lista de cursos vazia.\n");
        return;
    }

    No *atual = listaAlunos->primeiro;

    while (atual != NULL) {
        if (atual->aluno.matricula == id) {
        	system("cls");
        	printf("Aluno: %s idCurso: %s Pagamento vencido: %d\n\n", atual->aluno.nome, atual->aluno.idCurso, atual->aluno.pagamento);
            printf("Digite o novo nome do Aluno: ");
            scanf("%s", &atual->aluno.nome); 
            printf("Digite o novo idCurso: ");
            scanf("%s", &atual->aluno.idCurso); 
            printf("Digite o novo status de pagamento: ");
            scanf("%d", &atual->aluno.pagamento);
            printf("Aluno com ID %d editado com sucesso.\n", id);
            return;
        }
        atual = atual->proximo;
    }

    printf("Aluno com ID %d não encontrado.\n", id);
}

void contarAlunosPorCurso(Lista *listaCursos, Lista *listaAlunos) {
    if (listaCursos == NULL || listaAlunos == NULL || listaCursos->primeiro == NULL || listaAlunos->primeiro == NULL) {
        printf("Lista de cursos ou lista de alunos vazia.\n");
        return;
    }

    No *cursoAtual = listaCursos->primeiro;

    // Loop through each course
    while (cursoAtual != NULL) {
        int count = 0; // Initialize count for current course

        No *alunoAtual = listaAlunos->primeiro;

        // Loop through each student
        while (alunoAtual != NULL) {

            // Check if the student's course ID matches the current course's ID
            if (alunoAtual->aluno.idCurso == cursoAtual->curso.idCurso) {
                count++; // Increment count if the student is enrolled in the current course
            }

            alunoAtual = alunoAtual->proximo;
        }

        // Update the count of students for the current course
        cursoAtual->curso.totalAlunos = count;

        cursoAtual = cursoAtual->proximo;
    }
}

void swap(Curso *a, Curso *b) {
    Curso temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSortTotal(Lista *listaCursos) {
    No *i, *j;
    Curso *curso_i, *curso_j;
    
    for (i = listaCursos->primeiro; i != NULL; i = i->proximo) {
        curso_i = &(i->curso);
        for (j = i->proximo; j != NULL; j = j->proximo) {
            curso_j = &(j->curso);
            if (curso_i->totalAlunos < curso_j->totalAlunos) {
                swap(curso_i, curso_j);
            }
        }
    }
}

void selectionSortID(Lista *listaCursos) {
    No *i, *j;
    Curso *curso_i, *curso_j;
    
    for (i = listaCursos->primeiro; i != NULL; i = i->proximo) {
        curso_i = &(i->curso);
        for (j = i->proximo; j != NULL; j = j->proximo) {
            curso_j = &(j->curso);
            if (curso_i->idCurso < curso_j->idCurso) {
                swap(curso_i, curso_j);
            }
        }
    }
}

void listarInadimplentes(Lista *listaAlunos) {
    printf("Lista de Inadimplentes:\n");
    No *atual = listaAlunos->primeiro;
    while (atual != NULL) {
    	if (atual->aluno.pagamento == 1) {
            printf("Matricula: %d Nome: %s IdCurso: %d Data Mensalidade: %02d-%02d-%04d\n", atual->aluno.matricula, atual->aluno.nome, atual->aluno.idCurso, atual->aluno.pagamento, atual->aluno.dataMensalidade.tm_mday, atual->aluno.dataMensalidade.tm_mon+ 1, atual->aluno.dataMensalidade.tm_year + 1900);
        }
        atual = atual->proximo;
    }
}