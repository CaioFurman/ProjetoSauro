#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

//Projeto SAURO
typedef struct aluno{
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
  No *primeiro = NULL;
  No *ultimo = NULL;
} Lista;

void cadastrarAluno(Lista *listaAlunos, int matriculaNova){
	// Alocação de memória
	No *novoNo = (No *) malloc(sizeof(No));
	if (novoNo == NULL) {
		printf("\n\nErro: Memoria insuficiente!\n\n");
		exit(1);
		
	} else {
		fflush(stdin);
		printf("==========\n Cadastro de aluno.\n\n");
		printf("Nome: ");
		scanf("%[^\n]", &novoNo->aluno.nome); 
		
		novoNo->aluno.matricula = matriculaNova;
		novoNo->aluno.idCurso = 0;
		novoNo->aluno.pagamento = false;
	
		// Inserir o novo nó no final da lista
		if (listaAlunos->primeiro == NULL) {
	    	listaAlunos->primeiro = novoNo;
	    	listaAlunos->ultimo = novoNo;
		} else {
	    	listaAlunos->ultimo->proximo = novoNo;
			listaAlunos->ultimo = novoNo;
		}
	  
		printf("\n Aluno cadastrado com sucesso!\n -> Nome: %s, Matricula: %d\n\n", novoNo->aluno.nome, novoNo->aluno.matricula);
		
		printf("Pressione qualquer tecla para continuar...");
		getch();  
		system("cls");
	}
}

void cadastrarCurso(Lista *listaCursos, int cursoNovo){
	// Alocação de memória
	No *novoNo = (No *) malloc(sizeof(No));
	if (novoNo == NULL) {
		printf("\n\nErro: Memoria insuficiente!\n\n");
		exit(1);
		
	} else {
		fflush(stdin);
		printf("==========\n Cadastro de curso.\n\n");
		printf("Nome do curso: ");
		scanf("%[^\n]", &novoNo->curso.nome); 
		
		fflush(stdin);
		printf("Turno: ");
  		scanf("%s", &novoNo->curso.turno);
  				
		fflush(stdin);
		printf("Mensalidade: ");
  		scanf("%f", &novoNo->curso.mensalidade);

		novoNo->curso.idCurso = cursoNovo;

	
		// Inserir o novo nó no final da lista
		if (listaCursos->primeiro == NULL) {
	    	listaCursos->primeiro = novoNo;
	    	listaCursos->ultimo = novoNo;
		} else {
	    	listaCursos->ultimo->proximo = novoNo;
			listaCursos->ultimo = novoNo;
		}
	  
		printf("\n Curso cadastrado com sucesso!\n -> Nome do curso: %s, Turno: %s, Mensalidade: R$ %.2f\n", novoNo->curso.nome, novoNo->curso.turno, novoNo->curso.mensalidade);
		
		printf("Pressione qualquer tecla para continuar...");
		getch();  
		system("cls");
	}
}

//  ------  Funções reservadas -----
/*
void removerAluno(Lista *lista, int matricula);
void alterarAluno(Lista *lista, int matricula);

void matricularAluno(Lista *listaAlunos, Curso *curso, int matricula);
void removerMatricula(Lista *listaAlunos, int matricula);

void gerarRelatorioMatriculas(Lista *listaAlunos);
void gerarRelatorioDebitos(Lista *listaAlunos);

void registrarPagamento(Lista *listaAlunos, int matricula);
void gerarAvisoVencimento(Lista *listaAlunos);
*/

int main(void){
	int matriculaNova = 1;
	int cursoNovo = 1;
	bool continuar = true;
	int escolha, i;
	Lista listaAlunos;
	Lista listaCursos;
	
	while(continuar){
		fflush(stdin);
		printf("==========\n Escolha uma das opcoes a seguir.\n\n  1. Cadastro\n  2. Matricula e pagamento\n  3. Controle financeiro\n  4. Emitir relatorios de matriculas\n  5. Gerenciamento\n  6. Sair\n\nOpcao selecionada: ");
		scanf("%d", &escolha);
		system("cls");
		
		switch(escolha){
			case 1: 
				fflush(stdin);
				printf("==========\n Escolha uma das opcoes a seguir.\n\n  1. Cadastrar aluno\n  2. Cadastrar curso\n\nOpcao selecionada: ");
				scanf("%d", &escolha);
				system("cls");
				
				switch(escolha){
					case 1: 
						cadastrarAluno(&listaAlunos, matriculaNova);
						matriculaNova++;
						break;
						
					case 2: 
						cadastrarCurso(&listaCursos, cursoNovo);
						cursoNovo++;
						break;
				}
				break;
				
			case 2: 
				fflush(stdin);
				printf("==========\n Escolha uma das opcoes a seguir.\n\n  1. Matricular aluno\n  2. Efetuar pagamento\n\nOpcao selecionada: ");
				scanf("%d", &escolha);
				system("cls");
								
				switch(escolha){
					case 1: 
						printf("==========\n matricula\n\n");
						printf("Pressione qualquer tecla para continuar...");
						getch();  
						system("cls");
						break;
						
					case 2: 
						printf("==========\n pagamento\n\n");
						printf("Pressione qualquer tecla para continuar...");
						getch();  
						system("cls");
						break;
				}
				break;
				
			case 3: 
				printf("==========\n controle financeiro\n\n");
				printf("Pressione qualquer tecla para continuar...");
				getch();  
				system("cls");
				break;
				
			case 4: 
				printf("==========\n emitir relatorios\n\n");
				printf("Pressione qualquer tecla para continuar...");
				getch();  
				system("cls");
				break;
				
			case 5: 
				printf("==========\n gerenciamento\n\n");
				printf("Pressione qualquer tecla para continuar...");
				getch();  
				system("cls");
				break;
				
			case 6: 
				continuar = false;
				break;
		}
	}
}



