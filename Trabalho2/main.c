#define ident 
//0: erro
//1: certo

int analise_ident(char *token){

	automato(&token, classe, source_file);

	if(token == , ){
		if(analise_ident())
			return 1;
	}

	else if(token == ident){
		return 1;
	}

	else if(token == ;){
		return 0;
	}
	return 1;
}


int analise_sintatica(char *token){
	
	if (token == ident){
		analise_ident(token);
		
	}
		


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

