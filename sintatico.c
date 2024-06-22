//#define ident 
//0: erro
//1: certo

#include "msgnsErro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msgnsErro.h"
#include "automato.h"
#include "sintatico.h"
#include "lista.h"
#define MAX_CLASSE_LENGHT 32

#define programa_index 0
#define bloco_index 1
#define declaracao_index 2 
#define constante_index 3
#define mais_const_index 4
#define variavel_index 5
#define mais_var_index 6
#define procedimento_index 7
#define comando_index 8
#define mais_cmd_index 9
#define expressao_index 10 
#define operador_unario_index 11 
#define termo_index 12
#define mais_termos_index 13
#define fator_index 14
#define mais_fatores_index 15
#define condicao_index 16
#define relacional_index 17

void obter_token(char **token, char *classe, FILE *source_file, int *linha) {

	automato(token, classe, source_file, linha);
	if(!strcmp(classe, "<comentario>")) {

		automato(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<ERRO_LEXICO_1>")) {

		ERRO_LEXICO_1
		automato(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<ERRO_LEXICO_2>")) {

		ERRO_LEXICO_2
		automato(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<ERRO_LEXICO_3>")) {

		ERRO_LEXICO_3
		automato(token, classe, source_file, linha);

	}

}

void mais_const(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_const", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<simb_igual>")) {

			obter_token(token, classe, source_file, linha);
			if(!strcmp(classe, "<numero>")) {

				obter_token(token, classe, source_file, linha);
				if(!strcmp(classe, "<virgula>")) {

					obter_token(token, classe, source_file, linha);
					mais_const(token, classe, source_file, linha, simb_sincr, pilhaRegras);

				} 
				
			}
		}
	}

	desempilharRegra(pilhaRegras);

}

void constante(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("constante", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);
	if(!strcmp(classe, "<CONST>")) {

		obter_token(token, classe, source_file, linha);
		mais_const(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {

			obter_token(token, classe, source_file, linha);
			
		}
		
	}
	desempilharRegra(pilhaRegras);
		
}

void mais_var(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_var", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<virgula>")) {

			obter_token(token, classe, source_file, linha);
			mais_var(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		} 
			
		
		
	}

	desempilharRegra(pilhaRegras);

}

void variavel(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("variavel", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<VAR>")) {

		obter_token(token, classe, source_file, linha);
		mais_var(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {

			obter_token(token, classe, source_file, linha);
			if(!strcmp(classe, "<identificador>")) {

			}
			
		}
		
	}

	desempilharRegra(pilhaRegras);

}

void expressao(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("expressao", pilhaRegras);
	empilharRegra("operador_unario", pilhaRegras);
	empilharRegra("termo", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<simb_soma>") || !strcmp(classe, "<simb_subtracao>")) {

		obter_token(token, classe, source_file, linha);

	}
	fator(token, classe, source_file, linha, simb_sincr, pilhaRegras);
	mais_fatores(token, classe, source_file, linha, simb_sincr, pilhaRegras);
	mais_termos(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	desempilharRegra(pilhaRegras);
	desempilharRegra(pilhaRegras);
	desempilharRegra(pilhaRegras);

}

void fator(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("fator", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<numero>")) {

		obter_token(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<abre_parenteses>")) {

			obter_token(token, classe, source_file, linha);
			expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
			if(!strcmp(classe, "<fecha_parenteses>")) {

				obter_token(token, classe, source_file, linha);

			}

		}
		
	}

	desempilharRegra(pilhaRegras);

}

void mais_fatores(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_fatores", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<simb_multiplicacao>") || !strcmp(classe, "<simb_divisao>")) {

		obter_token(token, classe, source_file, linha);
		fator(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		mais_fatores(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	}

	desempilharRegra(pilhaRegras);

}

void mais_termos(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_termos", pilhaRegras);
	empilharRegra("termo", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<simb_soma>") || !strcmp(classe, "<simb_subtracao>")) {

		obter_token(token, classe, source_file, linha);
		fator(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		mais_fatores(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		mais_termos(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	}

	desempilharRegra(pilhaRegras);
	desempilharRegra(pilhaRegras);

}

void condicao(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("condicao", pilhaRegras);
	empilharRegra("relacional", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<ODD>")) {

		obter_token(token, classe, source_file, linha);
		expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	}

	expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
	if(!strcmp(classe, "<simb_diferente>") 
	|| !strcmp(classe, "<simb_menor>")
	|| !strcmp(classe, "<simb_menor_igual>")
	|| !strcmp(classe, "<simb_maior>")
	|| !strcmp(classe, "<simb_maior_igual>")) {

		obter_token(token, classe, source_file, linha);

	}
	expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	desempilharRegra(pilhaRegras);
	desempilharRegra(pilhaRegras);

}

void comando(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("comando", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<simb_atribuicao>")) {

			obter_token(token, classe, source_file, linha);
			expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}

	}else if(!strcmp(classe, "<CALL>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<identificador>")) {

			obter_token(token, classe, source_file, linha);

		}

	}else if(!strcmp(classe, "<BEGIN>")) {

		obter_token(token, classe, source_file, linha);
		comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		mais_cmd(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<END>")) {

			obter_token(token, classe, source_file, linha);

		}
		

	}else if(!strcmp(classe, "<IF>")) {

		obter_token(token, classe, source_file, linha);
		condicao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<THEN>")) {

			obter_token(token, classe, source_file, linha);
			comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}

	}else if(!strcmp(classe, "<WHILE>")) {

		obter_token(token, classe, source_file, linha);
		condicao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<DO>")) {

			obter_token(token, classe, source_file, linha);
			comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);
			
		}

	}

	desempilharRegra(pilhaRegras);

}

void mais_cmd(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_cmd", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<simb_ponto_virgula>")) {

		obter_token(token, classe, source_file, linha);
		comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);	
		mais_cmd(token, classe, source_file, linha, simb_sincr, pilhaRegras);	

	}

	desempilharRegra(pilhaRegras);

}

void procedimento(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("procedimento", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<PROCEDURE>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<identificador>")) {

			obter_token(token, classe, source_file, linha);
			if(!strcmp(classe, "<simb_ponto_virgula>")) {

				obter_token(token, classe, source_file, linha);
				constante(token, classe, source_file, linha, simb_sincr, pilhaRegras);
				variavel(token, classe, source_file, linha, simb_sincr, pilhaRegras);
				procedimento(token, classe, source_file, linha, simb_sincr, pilhaRegras);
				comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);

				obter_token(token, classe, source_file, linha);
				if(!strcmp(classe, "<simb_ponto_virgula>")) {

					obter_token(token, classe, source_file, linha);
					procedimento(token, classe, source_file, linha, simb_sincr, pilhaRegras);

				}
			}


		}

	} 

	desempilharRegra(pilhaRegras);

}

void printError(int codigo, char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras){

	switch (codigo)	{

		case 1:
			ERRO_SINTATICO_1
			break;

		default:
			break;

	}

}

void erro(int codigo, char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras) {

	printError(codigo, token, classe, source_file, linha, simb_sincr, pilhaRegras);

	while(containsElement(simb_sincr, classe)) 
		obter_token(token, classe, source_file, linha);

}

void desempilharRegra(int *pilhaRegras) {

	int i = 0;
	while (pilhaRegras != -1)
		i++;

	pilhaRegras[i-1] = -1;	
	
}

void empilharRegra(char *regra, int *pilhaRegras) {

	int regra_index = 0;

	if(!strcmp("programa", regra)) 
		regra_index = programa_index;

	else if(!strcmp("bloco", regra)) 	
		regra_index = bloco_index;

	else if(!strcmp("declaracao", regra)) 	
		regra_index = declaracao_index;

	else if(!strcmp("constante", regra)) 	
		regra_index = constante_index;

	else if(!strcmp("mais_const", regra)) 	
		regra_index = mais_const_index;

	else if(!strcmp("variavel", regra)) 	
		regra_index = variavel_index;

	else if(!strcmp("mais_var", regra)) 	
		regra_index = mais_var_index;

	else if(!strcmp("procedimento", regra)) 	
		regra_index = procedimento_index;

	else if(!strcmp("comando", regra)) 	
		regra_index = comando_index;

	else if(!strcmp("mais_cmd", regra)) 	
		regra_index = mais_cmd_index;

	else if(!strcmp("expressao", regra)) 	
		regra_index = expressao_index;

	else if(!strcmp("operador_unario", regra)) 	
		regra_index = operador_unario_index;

	else if(!strcmp("termo", regra)) 	
		regra_index = termo_index;

	else if(!strcmp("mais_termos", regra)) 	
		regra_index = mais_termos_index;

	else if(!strcmp("fator", regra)) 	
		regra_index = fator_index;

	else if(!strcmp("mais_fatores", regra)) 	
		regra_index = mais_fatores_index;

	else if(!strcmp("condicao", regra)) 	
		regra_index = condicao_index;

	else if(!strcmp("relacional", regra))
		regra_index = relacional_index;

	int i = 0;
	while (pilhaRegras != -1)
		i++;

	pilhaRegras[i] = regra_index;	

}

void gerarSimSincr(int *pilhaRegras, LinkedList *simb_sincr ) {

	removeAllElements(simb_sincr);

	// ? representa o λ
	const FollowSet followSets[] = {
        {"<programa>", {"$", NULL}},
        {"<bloco>", {".", NULL}},
        {"<declaracao>", {"ident", "CALL", "BEGIN", "IF", "WHILE", "?", NULL}},
        {"<constante>", {"VAR", "PROCEDURE", "ident", "CALL", "BEGIN", "IF", "WHILE", "?", NULL}},
        {"<mais_const>", {";", NULL}},
        {"<variavel>", {"PROCEDURE", "ident", "CALL", "BEGIN", "IF", "WHILE", "?", NULL}},
        {"<mais_var>", {";", NULL}},
        {"<procedimento>", {"ident", "CALL", "BEGIN", "IF", "WHILE", "?", NULL}},
        {"<comando>", {"END", ";", NULL}},
        {"<mais_cmd>", {"END", NULL}},
        {"<expressao>", {"THEN", "DO", ")", ";", NULL}},
        {"<operador_unario>", {"ident", "numero", "(", NULL}},
        {"<termo>", {"-", "+", "THEN", "DO", ")", ";", NULL}},
        {"<mais_termos>", {"THEN", "DO", ")", ";", NULL}},
        {"<fator>", {"*", "/", "-", "+", "THEN", "DO", ")", ";", NULL}},
        {"<mais_fatores>", {"-", "+", "THEN", "DO", ")", ";", NULL}},
        {"<condicao>", {"THEN", "DO", NULL}},
        {"<relacional>", {"-", "+", "ident", "numero", "(", NULL}}
    };

	for (int i = 0; pilhaRegras[i] != -1; i++) {

		for (int j = 0; followSets[i].followers[j] != NULL; j++) 
			insertElement(simb_sincr, followSets[i].followers[j]);

	}
	
}

void analisador_sintatico(FILE* source_file) {

	int linha = 0;
	int pilhaRegras[18] = {-1};

	char *token;
    token = malloc(sizeof(char));
    *token = '\0';
    if(token == NULL) {//imprime uma mensagem de erro caso a alocação falhe
        ERRO_ALOCACAO
        exit(-1);//encerra o programa 
    }

    char *classe;
    classe = malloc(sizeof(char)*MAX_CLASSE_LENGHT);
    if(classe == NULL) {//imprime uma mensagem de erro caso a alocação falhe
        ERRO_ALOCACAO
        exit(-1);//encerra o programa 
    }

	LinkedList *simb_sincr;
    initializeList(simb_sincr);
	printList(simb_sincr);

	empilharRegra("programa", pilhaRegras);
	empilharRegra("bloco", pilhaRegras);
	empilharRegra("declaracao", pilhaRegras);
	obter_token(&token, classe, source_file,  &linha);
	constante(&token, classe, source_file,  &linha, simb_sincr, pilhaRegras);
	variavel(&token, classe, source_file,  &linha, simb_sincr, pilhaRegras);
	procedimento(&token, classe, source_file,  &linha, simb_sincr, pilhaRegras);
	desempilharRegra(pilhaRegras);
	comando(&token, classe, source_file,  &linha, simb_sincr, pilhaRegras);

	//verifica se chegou ao fim do arquivo
	if(automato(&token, classe, source_file, &linha)) {

		free(token);
    	free(classe);
		return;

	}

	//se não chegou ao fim do arquivo: ERRO
	ERRO_SINTATICO_1
	

	free(token);
    free(classe);

}