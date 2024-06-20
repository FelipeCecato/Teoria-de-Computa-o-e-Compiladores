#define ident 
//0: erro
//1: certo

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

int main(int argc, char const *argv[]) {


	while (!automato(&token, classe, source_file)) {

        
		analise_sintatica(&token,
		
        token = realloc(token, sizeof(char));
        if(token == NULL) {//imprime uma mensagem de erro caso a alocação falhe
            ERRO_ALOCACAO
            exit(-1);//encerra o programa 
        }
        *token = '\0';

    }

}

