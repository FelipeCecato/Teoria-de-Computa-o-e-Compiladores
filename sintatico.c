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

//códigos de erro
#define unexpected_code 1 //funcionando
#define missing_equal_symbol 2 //funcionando
#define missing_value 3 //funcionando
#define missing_semicolon 4 //falhando em comando e mais_cmd e procedure
#define missing_atrib_symbol 5 // funciona
#define missing_ident 6 // nao funciona no comando
#define missing_END 7
#define missing_THEN 8 //funcionando
#define missing_DO 9 //funcionando
#define missing_ODD 10 //funcionando
#define missing_expression 11 // funciona
#define missing_close_brackets 12 // funciona
#define missing_relational_op 13 //funcionando
#define missing_condition 14 //funcionando
#define unexpected_ODD 15 //funcionando
// Conferir se abrir parenteses e nao fechar da erro
// Call sem ponto-virgula da problema


//index de cada regra no vetor "pilhaRegras"
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

void mais_const(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

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
				
			}else {

				erro( missing_value, token, classe, source_file, linha, simb_sincr, pilhaRegras);
				mais_const(token, classe, source_file, linha, simb_sincr, pilhaRegras);

			}

		}else {

			erro( missing_equal_symbol, token, classe, source_file, linha, simb_sincr, pilhaRegras);
			mais_const(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}

	}else {

		erro(missing_ident, token, classe, source_file, linha, simb_sincr,pilhaRegras);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {
			desempilharRegra("mais_const", pilhaRegras);
			return;
		}
		mais_const(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	}

	desempilharRegra("mais_const", pilhaRegras);

}

void constante(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("constante", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);
	if(!strcmp(classe, "<CONST>")) {

		obter_token(token, classe, source_file, linha);
		mais_const(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {

			obter_token(token, classe, source_file, linha);
			
		} else {

			erro(missing_semicolon, token, classe, source_file, linha, simb_sincr,pilhaRegras);

		}
		
	}
	desempilharRegra("constante", pilhaRegras);
		
}

void mais_var(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_var", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<virgula>")) {

			obter_token(token, classe, source_file, linha);
			mais_var(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		} 
			
		
		
	}else {

		erro(missing_ident, token, classe, source_file, linha, simb_sincr,pilhaRegras);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {
			desempilharRegra("mais_var", pilhaRegras);
			return;
		}
		mais_var(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	}

	desempilharRegra("mais_var", pilhaRegras);

}

void variavel(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("variavel", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<VAR>")) {

		obter_token(token, classe, source_file, linha);
		mais_var(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {

			obter_token(token, classe, source_file, linha);
			if(!strcmp(classe, "<identificador>")) {

			}
			
		}else {

			erro(missing_semicolon, token, classe, source_file, linha, simb_sincr,pilhaRegras);

		}
		
	}

	desempilharRegra("variavel", pilhaRegras);

}

void expressao(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

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

	desempilharRegra("expressao", pilhaRegras);
	desempilharRegra("operador_unario", pilhaRegras);
	desempilharRegra("termo", pilhaRegras);

}

void fator(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("fator", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<numero>")) {

		obter_token(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<abre_parenteses>")) {

		obter_token(token, classe, source_file, linha);
		expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<fecha_parenteses>")) {
		
			obter_token(token, classe, source_file, linha);
		
		}else {

			erro(missing_close_brackets, token, classe, source_file, linha, simb_sincr,pilhaRegras);

		}
		
	}else {

		erro(missing_expression, token, classe, source_file, linha, simb_sincr,pilhaRegras);
	
	}
	desempilharRegra("fator", pilhaRegras);

}

void mais_fatores(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_fatores", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<simb_multiplicacao>") || !strcmp(classe, "<simb_divisao>")) {

		obter_token(token, classe, source_file, linha);
		fator(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		mais_fatores(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	}

	desempilharRegra("mais_fatores", pilhaRegras);

}

void mais_termos(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_termos", pilhaRegras);
	empilharRegra("termo", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<simb_soma>") || !strcmp(classe, "<simb_subtracao>")) {

		obter_token(token, classe, source_file, linha);
		fator(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		mais_fatores(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		mais_termos(token, classe, source_file, linha, simb_sincr, pilhaRegras);

	}

	desempilharRegra("mais_termos", pilhaRegras);
	desempilharRegra("termo", pilhaRegras);

}

void condicao(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	int odd = 0;

	empilharRegra("condicao", pilhaRegras);
	empilharRegra("relacional", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<ODD>")) {

		obter_token(token, classe, source_file, linha);
		odd = 1;

	}

	if(!strcmp(classe, "<THEN>") || !strcmp(classe, "<DO>")) {

		erro(missing_condition, token, classe, source_file, linha, simb_sincr,pilhaRegras);
		desempilharRegra("condicao", pilhaRegras);
		desempilharRegra("relacional", pilhaRegras);
		return;
		
	}
	
	expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
	if(!strcmp(classe, "<simb_diferente>") 
	|| !strcmp(classe, "<simb_menor>")
	|| !strcmp(classe, "<simb_menor_igual>")
	|| !strcmp(classe, "<simb_maior>")
	|| !strcmp(classe, "<simb_maior_igual>")) {

		if(odd){

			erro(unexpected_ODD, token, classe, source_file, linha, simb_sincr,pilhaRegras);
			expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}else {

			obter_token(token, classe, source_file, linha);
			expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}


	}else {

		if(!strcmp(classe, "<THEN>") || !strcmp(classe, "<DO>")) {
			
			if(!odd)
				erro(missing_ODD, token, classe, source_file, linha, simb_sincr,pilhaRegras);

		} else {
			
			if(odd)
				erro(unexpected_ODD, token, classe, source_file, linha, simb_sincr,pilhaRegras);

			erro(missing_relational_op, token, classe, source_file, linha, simb_sincr,pilhaRegras);
			expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
			
		}
	
	}

	desempilharRegra("condicao", pilhaRegras);
	desempilharRegra("relacional", pilhaRegras);

}

void comando(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("comando", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<simb_atribuicao>")) {
			obter_token(token, classe, source_file, linha);
			expressao(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}else {

			// desempilharRegra("comando", pilhaRegras);
			// printList(simb_sincr);
			if(pilhaRegras[2] == 1) {
				desempilharRegra("declaracao", pilhaRegras);
				gerarSimSincr(pilhaRegras, simb_sincr);
				erro(missing_atrib_symbol, token, classe, source_file, linha, simb_sincr, pilhaRegras);
				empilharRegra("declaracao", pilhaRegras);
				gerarSimSincr(pilhaRegras, simb_sincr);
			}else {
				erro(missing_atrib_symbol, token, classe, source_file, linha, simb_sincr, pilhaRegras);
			}
		}

	}else if(!strcmp(classe, "<CALL>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<identificador>")) {

			obter_token(token, classe, source_file, linha);

		}else {

			erro(missing_ident, token, classe, source_file, linha, simb_sincr,pilhaRegras);

		}

	}else if(!strcmp(classe, "<BEGIN>")) {

		obter_token(token, classe, source_file, linha);
		comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		mais_cmd(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<END>")) {

			obter_token(token, classe, source_file, linha);

		}else {

			erro(missing_END, token, classe, source_file, linha, simb_sincr,pilhaRegras);

		}
		

	}else if(!strcmp(classe, "<IF>")) {

		obter_token(token, classe, source_file, linha);
		condicao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<THEN>")) {

			obter_token(token, classe, source_file, linha);
			comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}else {

			erro(missing_THEN, token, classe, source_file, linha, simb_sincr,pilhaRegras);
			comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}

	}else if(!strcmp(classe, "<WHILE>")) {

		obter_token(token, classe, source_file, linha);
		condicao(token, classe, source_file, linha, simb_sincr, pilhaRegras);
		if(!strcmp(classe, "<DO>")) {

			obter_token(token, classe, source_file, linha);
			comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);
			
		}else {

			erro(missing_DO, token, classe, source_file, linha, simb_sincr,pilhaRegras);
			comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);

		}

	}

	desempilharRegra("comando", pilhaRegras);

}

void mais_cmd(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("mais_cmd", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<simb_ponto_virgula>")) {

		obter_token(token, classe, source_file, linha);
		comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);	
		mais_cmd(token, classe, source_file, linha, simb_sincr, pilhaRegras);	

	}else if(!strcmp(classe, "<END>")) {
		desempilharRegra("mais_cmd", pilhaRegras);
		return;
		
	}else {

		erro(missing_semicolon, token, classe, source_file, linha, simb_sincr,pilhaRegras);
	
	}

	desempilharRegra("mais_cmd", pilhaRegras);

}

void analisa_procedimento(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {
	obter_token(token, classe, source_file, linha);
	constante(token, classe, source_file, linha, simb_sincr, pilhaRegras);
	variavel(token, classe, source_file, linha, simb_sincr, pilhaRegras);
	procedimento(token, classe, source_file, linha, simb_sincr, pilhaRegras);
	comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);
}

void procedimento(char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	empilharRegra("procedimento", pilhaRegras);
	gerarSimSincr(pilhaRegras, simb_sincr);

	if(!strcmp(classe, "<PROCEDURE>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<identificador>")) {

			obter_token(token, classe, source_file, linha);
			if(!strcmp(classe, "<simb_ponto_virgula>")) {
				
				analisa_procedimento(token, classe, source_file, linha, simb_sincr, pilhaRegras);

				if(!strcmp(classe, "<simb_ponto_virgula>")) {

					obter_token(token, classe, source_file, linha);
					procedimento(token, classe, source_file, linha, simb_sincr, pilhaRegras);

				}else {

					erro(missing_semicolon, token, classe, source_file, linha, simb_sincr,pilhaRegras);

				}

			}else {

				erro(missing_semicolon, token, classe, source_file, linha, simb_sincr,pilhaRegras);

			}


		}else {

			erro(missing_ident, token, classe, source_file, linha, simb_sincr,pilhaRegras);
			
			constante(token, classe, source_file, linha, simb_sincr, pilhaRegras);
			variavel(token, classe, source_file, linha, simb_sincr, pilhaRegras);
			procedimento(token, classe, source_file, linha, simb_sincr, pilhaRegras);
			comando(token, classe, source_file, linha, simb_sincr, pilhaRegras);

			if(!strcmp(classe, "<simb_ponto_virgula>")) {

				obter_token(token, classe, source_file, linha);
				procedimento(token, classe, source_file, linha, simb_sincr, pilhaRegras);

			}else {

				erro(missing_semicolon, token, classe, source_file, linha, simb_sincr,pilhaRegras);

			}
		}
	} 

	desempilharRegra("procedimento", pilhaRegras);

}

void printError(int codigo, char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras){

	switch (codigo)	{

		case 1:
			ERRO_SINTATICO_1(*linha)
			break;
		
		case 2:
			ERRO_SINTATICO_2
			break;

		case 3:
			ERRO_SINTATICO_3 
			break;

		case 4:
			ERRO_SINTATICO_4 
			break;

		case 5:
			ERRO_SINTATICO_5 
			break;

		case 6:
			ERRO_SINTATICO_6 
			break;

		case 7:
			ERRO_SINTATICO_7 
			break;

		case 8:
			ERRO_SINTATICO_8 
			break;

		case 9:
			ERRO_SINTATICO_9 
			break;
					
		case 10:
			ERRO_SINTATICO_10 
			break;

		case 11:
			ERRO_SINTATICO_11 
			break;

		case 12:
			ERRO_SINTATICO_12 
			break;

		case 13:
			ERRO_SINTATICO_13 
			break;

		case 14:
			ERRO_SINTATICO_14 
			break;
		
		case 15:
			ERRO_SINTATICO_15 
			break;

		default:
			break;

	}

}

void erro(int codigo, char **token, char *classe, FILE *source_file, int *linha,  LinkedList *simb_sincr, int *pilhaRegras) {

	printError(codigo, token, classe, source_file, linha, simb_sincr, pilhaRegras);

	// printf("token: %s	classe:	%s", *token, classe);
	while(!containsElement(simb_sincr, classe)) {
		obter_token(token, classe, source_file, linha);
	}

}

void desempilharRegra(char *regra, int *pilhaRegras) {

	//se a posição da regra estiver setada como 1 significa que ela está empilhada, se 0 desempilhada
	pilhaRegras[obter_index_regra(regra)] = -1;	
	
}

void empilharRegra(char *regra, int *pilhaRegras) {

	//se a posição da regra estiver setada como 1 significa que ela está empilhada, se 0 desempilhada
	pilhaRegras[obter_index_regra(regra)] = 1;	

}

int obter_index_regra(char *regra) {

	if(!strcmp("programa", regra)) 
		return programa_index;

	else if(!strcmp("bloco", regra)) 	
		return bloco_index;

	else if(!strcmp("declaracao", regra)) 	
		return declaracao_index;

	else if(!strcmp("constante", regra)) 	
		return constante_index;

	else if(!strcmp("mais_const", regra)) 	
		return mais_const_index;

	else if(!strcmp("variavel", regra)) 	
		return variavel_index;

	else if(!strcmp("mais_var", regra)) 	
		return mais_var_index;

	else if(!strcmp("procedimento", regra)) 	
		return procedimento_index;

	else if(!strcmp("comando", regra)) 	
		return comando_index;

	else if(!strcmp("mais_cmd", regra)) 	
		return mais_cmd_index;

	else if(!strcmp("expressao", regra)) 	
		return expressao_index;

	else if(!strcmp("operador_unario", regra)) 	
		return operador_unario_index;

	else if(!strcmp("termo", regra)) 	
		return termo_index;

	else if(!strcmp("mais_termos", regra)) 	
		return mais_termos_index;

	else if(!strcmp("fator", regra)) 	
		return fator_index;

	else if(!strcmp("mais_fatores", regra)) 	
		return mais_fatores_index;

	else if(!strcmp("condicao", regra)) 	
		return condicao_index;

	else if(!strcmp("relacional", regra))
		return relacional_index;

}

void gerarSimSincr(int *pilhaRegras,  LinkedList *simb_sincr ) {

	removeAllElements(simb_sincr);

	// ? representa o λ
	const FollowSet followSets[] = {
        {"<programa>", {"$", NULL}},
        {"<bloco>", {"<simb_ponto>", NULL}},
        {"<declaracao>", {"<identificador>", "<CALL>", "<BEGIN>", "<IF>", "<WHILE>", "?", NULL}},
        {"<constante>", {"<VAR>", "<PROCEDURE>", "<identificador>", "<CALL>", "<BEGIN>", "<IF>", "<WHILE>", "?", NULL}},
        {"<mais_const>", {"<simb_ponto_virgula>", NULL}},
        {"<variavel>", {"<PROCEDURE>", "<identificador>", "<CALL>", "<BEGIN>", "<IF>", "<WHILE>", "?", NULL}},
        {"<mais_var>", {"<simb_ponto_virgula>", NULL}},
        {"<procedimento>", {"<identificador>", "<CALL>", "<BEGIN>", "<IF>", "<WHILE>", "?", NULL}},
        {"<comando>", {"<END>", "<simb_ponto_virgula>", NULL}},
        {"<mais_cmd>", {"<END>", NULL}},
        {"<expressao>", {"<THEN>", "<DO>", "<fecha_parenteses>", "<simb_ponto_virgula>", NULL}},
        {"<operador_unario>", {"<identificador>", "<numero>", "<abre_parenteses>", NULL}},
        {"<termo>", {"<simb_subtracao>", "<simb_soma>", "<THEN>", "<DO>", "<fecha_parenteses>", "<simb_ponto_virgula>", NULL}},
        {"<mais_termos>", {"<THEN>", "<DO>", "<fecha_parenteses>", "<simb_ponto_virgula>", NULL}},
        {"<fator>", {"<simb_multiplicacao>", "<simb_divisao>", "<simb_subtracao>", "<simb_soma>", "<THEN>", "<DO>", "<fecha_parenteses>", "<simb_ponto_virgula>", NULL}},
        {"<mais_fatores>", {"<simb_subtracao>", "<simb_soma>", "<THEN>", "<DO>", "<fecha_parenteses>", "<simb_ponto_virgula>", NULL}},
        {"<condicao>", {"<THEN>", "<DO>", NULL}},
        {"<relacional>", {"<simb_subtracao>", "<simb_soma>", "<identificador>", "<numero>", "<abre_parenteses>", NULL}}
    };

	for (int i = 0; i <= 17; i++) {

		//se a regra estiver empilhada, adiciona os seguidores dela ao conjunto de simbolos de sincronismo
		if(pilhaRegras[i] == 1) {

			for (int j = 0; followSets[i].followers[j] != NULL; j++) 
				insertElement(simb_sincr, followSets[i].followers[j]);

		}

	}
	
}

void analisador_sintatico(FILE* source_file) {

	int linha = 0;
	int pilhaRegras[18] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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

	LinkedList simb_sincr;
    initializeList(&simb_sincr);

	empilharRegra("programa", pilhaRegras);
	empilharRegra("bloco", pilhaRegras);
	empilharRegra("declaracao", pilhaRegras);
	obter_token(&token, classe, source_file,  &linha);
	constante(&token, classe, source_file,  &linha, &simb_sincr, pilhaRegras);
	variavel(&token, classe, source_file,  &linha, &simb_sincr, pilhaRegras);
	procedimento(&token, classe, source_file,  &linha, &simb_sincr, pilhaRegras);
	desempilharRegra("declaracao", pilhaRegras);
	comando(&token, classe, source_file,  &linha, &simb_sincr, pilhaRegras);

	//verifica se chegou ao fim do arquivo
	if(automato(&token, classe, source_file, &linha)) {

		free(token);
    	free(classe);
		printf("numero de linhas processadas: %d\n", linha);
		return;

	}

	//se não chegou ao fim do arquivo: ERRO
	ERRO_SINTATICO_1(linha)
	printf("numero de linhas processadas: %d\n", linha);

	free(token);
    free(classe);

}