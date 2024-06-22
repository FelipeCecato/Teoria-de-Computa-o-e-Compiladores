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

#define MAX_CLASSE_LENGHT 32

/*
int analise_ident(char *token){

	automato(&token, classe, source_file);

	if(token == ident){
		automato(&token, classe, source_file);
		if(token == ,)
			return analise_ident();
		else{
			return 1;
		}
	}

	return 0;

}

int analise_variavel(arq , token){
	if(token == VAR)
		if(analise_ident()){
			if(token == ;)`
				return 1;
			return 0;
		}

	return 1;
}

int analise_procedimento(arq,token){
	if(token == PROCEDURE){
		automato(token);
		if(token == ident)
			return 1;
		return 0;
	}
	if(analise_bloco())
	return 1;
}

int analise_sintatica(char *token){
	
	if (token == ident){
		analise_ident(token);
		
	}
		


}

int analise_declaracao(){
	if(analise_constante()&&analise_variavel()&&analise_procedimento)
		return 1;
	return 0;
}

int analise_bloco(){
	if(analise_declaracao()&&analise_comando)
		return 1;
	
	return 0;
}
*/
//===================================================================================

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

void mais_const(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<simb_igual>")) {

			obter_token(token, classe, source_file, linha);
			if(!strcmp(classe, "<numero>")) {

				obter_token(token, classe, source_file, linha);
				if(!strcmp(classe, "<virgula>")) {

					obter_token(token, classe, source_file, linha);
					mais_const(token, classe, source_file, linha);

				} 
				
			}
		}
	}

}

void constante(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<CONST>")) {

		obter_token(token, classe, source_file, linha);
		mais_const(token, classe, source_file, linha);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {

			obter_token(token, classe, source_file, linha);
			
		}
		
	}
		

}

void mais_var(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<virgula>")) {

			obter_token(token, classe, source_file, linha);
			mais_var(token, classe, source_file, linha);

		} 
			
		
		
	}

}

void variavel(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<VAR>")) {

		obter_token(token, classe, source_file, linha);
		mais_var(token, classe, source_file, linha);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {

			obter_token(token, classe, source_file, linha);
			if(!strcmp(classe, "<identificador>")) {

			}
			
		}
		
	}

}

void expressao(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<simb_soma>") || !strcmp(classe, "<simb_subtracao>")) {

		obter_token(token, classe, source_file, linha);

	}
	fator(token, classe, source_file, linha);
	mais_fatores(token, classe, source_file, linha);
	mais_termos(token, classe, source_file, linha);

}

void fator(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<numero>")) {

		obter_token(token, classe, source_file, linha);

	}else if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<abre_parenteses>")) {

			obter_token(token, classe, source_file, linha);
			expressao(token, classe, source_file, linha);
			if(!strcmp(classe, "<fecha_parenteses>")) {

				obter_token(token, classe, source_file, linha);

			}

		}
		
	}

}

void mais_fatores(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<simb_multiplicacao>") || !strcmp(classe, "<simb_divisao>")) {

		obter_token(token, classe, source_file, linha);
		fator(token, classe, source_file, linha);
		mais_fatores(token, classe, source_file, linha);

	}

}

void mais_termos(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<simb_soma>") || !strcmp(classe, "<simb_subtracao>")) {

		obter_token(token, classe, source_file, linha);
		fator(token, classe, source_file, linha);
		mais_fatores(token, classe, source_file, linha);
		mais_termos(token, classe, source_file, linha);

	}
}

void condicao(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<ODD>")) {

		obter_token(token, classe, source_file, linha);
		expressao(token, classe, source_file, linha);

	}

	expressao(token, classe, source_file, linha);
	if(!strcmp(classe, "<simb_diferente>") 
	|| !strcmp(classe, "<simb_menor>")
	|| !strcmp(classe, "<simb_menor_igual>")
	|| !strcmp(classe, "<simb_maior>")
	|| !strcmp(classe, "<simb_maior_igual>")) {

		obter_token(token, classe, source_file, linha);

	}
	expressao(token, classe, source_file, linha);

}

void comando(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<identificador>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<simb_atribuicao>")) {

			obter_token(token, classe, source_file, linha);
			expressao(token, classe, source_file, linha);

		}

	}else if(!strcmp(classe, "<CALL>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<identificador>")) {

			obter_token(token, classe, source_file, linha);

		}

	}else if(!strcmp(classe, "<BEGIN>")) {

		obter_token(token, classe, source_file, linha);
		comando(token, classe, source_file, linha);
		mais_cmd(token, classe, source_file, linha);
		if(!strcmp(classe, "<END>")) {

			obter_token(token, classe, source_file, linha);

		}
		

	}else if(!strcmp(classe, "<IF>")) {

		obter_token(token, classe, source_file, linha);
		condicao(token, classe, source_file, linha);
		if(!strcmp(classe, "<THEN>")) {

			obter_token(token, classe, source_file, linha);
			comando(token, classe, source_file, linha);

		}

	}else if(!strcmp(classe, "<WHILE>")) {

		obter_token(token, classe, source_file, linha);
		condicao(token, classe, source_file, linha);
		if(!strcmp(classe, "<DO>")) {

			obter_token(token, classe, source_file, linha);
			comando(token, classe, source_file, linha);
			
		}

	}

}

void mais_cmd(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<simb_ponto_virgula>")) {

		obter_token(token, classe, source_file, linha);
		comando(token, classe, source_file, linha);	
		mais_cmd(token, classe, source_file, linha);	

	}

}

void procedimento(char **token, char *classe, FILE *source_file, int *linha) {

	if(!strcmp(classe, "<PROCEDURE>")) {

		obter_token(token, classe, source_file, linha);
		if(!strcmp(classe, "<identificador>")) {

			obter_token(token, classe, source_file, linha);
			if(!strcmp(classe, "<simb_ponto_virgula>")) {

				obter_token(token, classe, source_file, linha);
				constante(token, classe, source_file, linha);
				variavel(token, classe, source_file, linha);
				procedimento(token, classe, source_file, linha);
				comando(token, classe, source_file, linha);

				obter_token(token, classe, source_file, linha);
				if(!strcmp(classe, "<simb_ponto_virgula>")) {

					obter_token(token, classe, source_file, linha);
					procedimento(token, classe, source_file, linha);

				}
			}


		}

	} 

}

void printError(int codigo, char **token, char *classe, FILE *source_file, int *linha){

	switch (codigo)	{

		case 1:
			ERRO_SINTATICO_1
			break;

		default:
			break;

	}

}

void erro(int codigo, char **token, char *classe, FILE *source_file, int *linha) {

	printError(codigo, token, classe, source_file, linha);

	while() {
		obter_token(token, classe, source_file, linha);
	}

}

void analisador_sintatico(FILE* source_file) {

	int linha = 0;

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

	obter_token(&token, classe, source_file,  &linha);
	constante(&token, classe, source_file,  &linha);
	variavel(&token, classe, source_file,  &linha);
	procedimento(&token, classe, source_file,  &linha);
	comando(&token, classe, source_file,  &linha);

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