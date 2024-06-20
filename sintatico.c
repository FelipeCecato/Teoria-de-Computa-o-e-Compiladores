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

void mais_const(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<identificador>")) {

		automato(token, classe, source_file);
		if(!strcmp(classe, "<simb_igual>")) {

			automato(token, classe, source_file);
			if(!strcmp(classe, "<numero>")) {

				automato(token, classe, source_file);
				if(!strcmp(classe, "<virgula>")) {

					automato(token, classe, source_file);
					mais_const(token, classe, source_file);

				} 
				
			}
		}
	}

}

void constante(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<CONST>")) {

		automato(token, classe, source_file);
		mais_const(token, classe, source_file);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {

			automato(token, classe, source_file);
			
		}
		
	}
		

}

void mais_var(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<identificador>")) {

		automato(token, classe, source_file);
		if(!strcmp(classe, "<virgula>")) {

			automato(token, classe, source_file);
			mais_var(token, classe, source_file);

		} 
			
		
		
	}

}

void variavel(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<VAR>")) {

		automato(token, classe, source_file);
		mais_var(token, classe, source_file);
		if(!strcmp(classe, "<simb_ponto_virgula>")) {

			automato(token, classe, source_file);
			if(!strcmp(classe, "<identificador>")) {

			}
			
		}
		
	}

}

void expressao(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<simb_soma>") || !strcmp(classe, "<simb_subtracao>")) {

		automato(token, classe, source_file);

	}
	fator(token, classe, source_file);
	mais_fatores(token, classe, source_file);
	mais_termos(token, classe, source_file);
	automato(token, classe, source_file);

}

void fator(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<identificador>")) {

		automato(token, classe, source_file);

	}else if(!strcmp(classe, "<numero>")) {

		automato(token, classe, source_file);

	}else if(!strcmp(classe, "<identificador>")) {

		automato(token, classe, source_file);
		if(!strcmp(classe, "<abre_parenteses>")) {

			automato(token, classe, source_file);
			expressao(token, classe, source_file);
			if(!strcmp(classe, "<fecha_parenteses>")) {

				automato(token, classe, source_file);

			}

		}
		
	}

}

void mais_fatores(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<simb_multiplicacao>") || !strcmp(classe, "<simb_divisao>")) {

		automato(token, classe, source_file);
		fator(token, classe, source_file);
		mais_fatores(token, classe, source_file);

	}

}

void mais_termos(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<simb_soma>") || !strcmp(classe, "<simb_subtracao>")) {

		automato(token, classe, source_file);
		fator(token, classe, source_file);
		mais_fatores(token, classe, source_file);
		mais_termos(token, classe, source_file);
		automato(token, classe, source_file);

	}
}

void condicao(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<ODD>")) {

		automato(token, classe, source_file);
		expressao(token, classe, source_file);
		automato(token, classe, source_file);

	}

	expressao(token, classe, source_file);
	if(!strcmp(classe, "<simb_diferente>") 
	|| !strcmp(classe, "<simb_menor>")
	|| !strcmp(classe, "<simb_menor_igual>")
	|| !strcmp(classe, "<simb_maior>")
	|| !strcmp(classe, "<simb_maior_igual>")) {

		automato(token, classe, source_file);

	}
	expressao(token, classe, source_file);

}

void comando(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<identificador>")) {

		if(!strcmp(classe, "<simb_atribuicao>")) {

			automato(token, classe, source_file);

		}

	}else if(!strcmp(classe, "<CALL>")) {

		if(!strcmp(classe, "<identificador>")) {

			automato(token, classe, source_file);

		}

	}else if(!strcmp(classe, "<BEGIN>")) {

		automato(token, classe, source_file);
		comando(token, classe, source_file);
		mais_cmd(token, classe, source_file);
		automato(token, classe, source_file);
		if(!strcmp(classe, "<END>")) {

			automato(token, classe, source_file);

		}
		

	}else if(!strcmp(classe, "<IF>")) {

		automato(token, classe, source_file);
		condicao(token, classe, source_file);
		if(!strcmp(classe, "<THEN>")) {

			automato(token, classe, source_file);
			comando(token, classe, source_file);

		}

	}else if(!strcmp(classe, "<WHILE>")) {

		automato(token, classe, source_file);
		condicao(token, classe, source_file);
		if(!strcmp(classe, "<DO>")) {

			automato(token, classe, source_file);
			comando(token, classe, source_file);
			
		}

	}

}

void mais_cmd(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<simb_ponto_virgula>")) {

		automato(token, classe, source_file);
		comando(token, classe, source_file);	
		mais_cmd(token, classe, source_file);	

	}

}

void procedimento(char **token, char *classe, FILE *source_file) {

	if(!strcmp(classe, "<PROCEDURE>")) {

		automato(token, classe, source_file);
		if(!strcmp(classe, "<identificador>")) {

			automato(token, classe, source_file);
			if(!strcmp(classe, "<simb_ponto_virgula>")) {

				constante(token, classe, source_file);
				variavel(token, classe, source_file);
				procedimento(token, classe, source_file);
				comando(token, classe, source_file);

				automato(token, classe, source_file);
				if(!strcmp(classe, "<simb_ponto_virgula>")) {

					automato(token, classe, source_file);
					procedimento(token, classe, source_file);

				}
			}


		}

	} 

}

void analisador_sintatico(FILE* source_file) {

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

	automato(&token, classe, source_file);
	constante(&token, classe, source_file);
	variavel(&token, classe, source_file);
	procedimento(&token, classe, source_file);
	comando(&token, classe, source_file);

	if(automato(&token, classe, source_file) == EOF) {

		free(token);
    	free(classe);
		return;
	}

	free(token);
    free(classe);

}