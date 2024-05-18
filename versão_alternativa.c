#include<stdio.h> 
#include<stdlib.h>
#include<string.h>


#define arq arquivo_leitura
#define arq2 arquivo_escrita
#define Numero ( *c>= '0' && *c<='9' ) // Numeros de 0 a 9
#define Letra ( (*c>='A' && *c <='Z') || (*c>='a'&& *c<='z') ) // Letras do alfabeto
#define CaracterEspecial ( (*c>='(' && *c <= '/')|| (*c >= ':' && *c <= '>') ) // Caracteres permitidos no PL0
#define PalavraEspecial !strcmp(retorno,"BEGIN")||!strcmp(retorno,"VAR")||!strcmp(retorno,"END")||!strcmp(retorno,"ODD")||!strcmp(retorno,"CALL")||!strcmp(retorno,"IF")||!strcmp(retorno,"WHILE")||!strcmp(retorno,"IF")||!strcmp(retorno,"THEN")||!strcmp(retorno,"DO")||!strcmp(retorno,"PROCEDURE")
#define Outro !Numero && !Letra && !CaracterEspecial && *c != EOF &&  *c != '\n' && *c !=' '


/* Verifica se eh palavra reservada */
int verificar_palavras_reservadas(char *retorno){
    if(PalavraEspecial)
        return 1;
    return 0;
}

/* Verifica se o que esta lendo eh ident */
int verif_ident(FILE *arq, FILE* arq2){ 

    int cont = 0;
    char retorno[1000];   
    char *c = (char *) malloc(sizeof(char)); 

    *c = fgetc(arq);
    
    if(*c == ',')
        *c = fgetc(arq);

    if(Letra) //Se for letra, inicia a ler o nome do identificador
    	while(Numero || Letra){
        	retorno[cont] = *c;
        	*c = fgetc(arq);
        	cont++;
    	}
    else{
	    ungetc(*c,arq); //retrocede
        free(c);
	    return 0;	
    }

    if(cont == 0)
    	cont++;   

    retorno[cont] = '\0';
	

    if(verificar_palavras_reservadas(retorno))
    	fprintf(arq2 ,"%s, %s \n",retorno, retorno);
     
    else
	    fprintf(arq2 ,"%s, ident\n",retorno);

    ungetc(*c,arq);
    free(c);
    return 1; //encontrou um identificador
}

/* Verifica comentario*/
void verif_comentario(FILE *arq){
    
    char *c = (char *) malloc(sizeof(char)); 
    *c = fgetc(arq);
 
    if(*c == '{'){
	
        while(*c!='}' && *c!= EOF){
            *c = fgetc(arq);
	  
	}
	if(*c == EOF){
	        ungetc(*c,arq);
            free(c);
        	return;
        }
    }
    else 
	    ungetc(*c,arq);
    free(c);
    return;
}

int verif_maior(FILE *arq, FILE *arq2){
    char *c = (char *) malloc(sizeof(char)); 

    *c = fgetc(arq);

    if(*c == '>'){

        *c = fgetc(arq);

        if(*c == '=')
            fprintf(arq2 ,">=, simbolo_maior_igual\n");
        else{
            fprintf(arq2, ">, simbolo_maior\n");
	        ungetc(*c,arq);
        }
        free(c);
        return 1;
    }
    else{
	    ungetc(*c,arq);
        free(c);
        return 0;
    }

}

int verif_menor(FILE *arq, FILE *arq2){

    char *c = (char *) malloc(sizeof(char)); 
    *c = fgetc(arq);

    if(*c == '<'){

        *c = fgetc(arq);

        if(*c == '>'){
            fprintf(arq2, "<>, simbolo_diferente\n");
            free(c);
            return 1;
        }
        else if(*c == '='){
            fprintf(arq2, "<=, simbolo_menor_igual\n");
            free(c);
            return 1;
        }
        else
	        ungetc(*c,arq);
        free(c);
        return 1;
    }
    else
       	 ungetc(*c,arq);
    free(c);
    return 0;
}

int verif_simb(FILE *arq,FILE *arq2){

    char *c = (char *) malloc(sizeof(char)); 
    *c = fgetc(arq);

    if(*c == '+'){
        fprintf(arq2, "+, simbolo_soma\n");
        free(c);
        return 1;
    }
    else if(*c == '-'){
        fprintf(arq2, "-, simbolo_menos\n");
        free(c);
        return 1;
    }
    else if(*c == ','){
        fprintf(arq2, ",, simbolo_virgula\n");
        free(c);
        return 1;
    }
    else if(*c == '.'){
        fprintf(arq2 ,"., simbolo_ponto\n");
        free(c);
        return 1;
    }
    else if(*c == ';'){
        fprintf(arq2, ";, simbolo_ponto_e_virgula\n");
        free(c);
        return 1;
    }
    else if(*c == '*'){
        fprintf(arq2, "*, simbolo_multiplicacao\n");
        free(c);
        return 1;
    }
    else if(*c == '/'){
        fprintf(arq2, "/, simbolo_divisao\n");
        free(c);
        return 1;
    }
    else if( *c == ')'){
        fprintf(arq2, "), simbolo_fecha_parenteses\n");
        free(c);
        return 1;
    }
    else if( *c == '('){
        fprintf(arq2, "(, simbolo_abre_parenteses\n");
        free(c);
        return 1;
    }
    else if(Outro){
	    fprintf(arq2 ,"%c, <ERRO_LEXICO>\n", *c); 
	    return 1; //consome o caracter 'outro' e retorna
    }
    ungetc(*c,arq);
    
    free(c);
    return 0;
}

int verif_atrib(FILE *arq, FILE *arq2){
    char *c = (char *) malloc(sizeof(char));
    *c = fgetc(arq);
    if(*c == ':'){
        *c = fgetc(arq);
        if(*c == '='){
            fprintf(arq2, ":=, simbolo_atribuicao\n");
            return 1;
        }
        else 
            	 ungetc(*c,arq);

    }
    else
        	 ungetc(*c,arq);
    
    free(c);
    return 0;
}

int verif_num(FILE *arq, FILE *arq2){

    char *c = (char *) malloc(sizeof(char));
    *c = fgetc(arq);
    int cont = 0;
    
    while(Numero){
	    fprintf(arq2, "%c", *c);
        *c = fgetc(arq);
        cont++;
    }

	ungetc(*c,arq);

    if(cont == 0){
        free(c);
        return 0;
    }
    else fprintf(arq2, ", numero\n");

    free(c);
    return 1;
}

void verif_espaco(FILE *arq){
	char *c = (char *) malloc(sizeof(char)); 
    *c = fgetc(arq);
    while(*c == ' ' || *c == '\n')
        *c = fgetc(arq);
    ungetc(*c,arq);
    free(c);
	return;
}

int verif_eof(FILE*arq){
	char *c = (char *) malloc(sizeof(char));
    *c = fgetc(arq);

	if(*c==EOF){
        free(c);
		return 1;
    }
	ungetc(*c,arq);
    
    free(c);
	return 0 ;

}
int automato(FILE *arq, FILE *arq2){

	    verif_espaco(arq);
        verif_comentario(arq);

        if(verif_ident(arq,arq2))
            return 0;


        if(verif_atrib(arq,arq2))
            return 0;

        if(verif_simb(arq,arq2))
            return 0;

        if(verif_menor(arq,arq2))
            return 0;


        if(verif_maior(arq,arq2))
            return 0;


        if(verif_num(arq,arq2))
            return 0;
 
        
	    return(verif_eof(arq));

}

int main(int argc, char *argv[]){

    // Verifica se há pelo menos dois argumentos na linha de comando
    if (argc != 3) {
        printf("Uso: %s texto1 texto2\n", argv[0]);
        return 1;
    }

    // Imprime os dois argumentos fornecidos
    printf("Argumento 1: %s\n", argv[1]);
    printf("Argumento 2: %s\n", argv[2]);

    FILE *arq, *arq2;

    arq = fopen(argv[1],"r");
    arq2 = fopen(argv[2],"w");
    fseek(arq,SEEK_SET,0);

    while(!automato(arq,arq2));

    fclose(arq);
    fclose(arq2);
    return 0;

}
