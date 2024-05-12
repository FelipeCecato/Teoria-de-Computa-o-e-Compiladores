#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#define Numero ( c>= '0' && c<='9' ) // Numeros de 0 a 9
#define Letra ( (c>='A' && c <='Z') || (c>='a'&& c<='z') ) // Letras do alfabeto
#define CaracterEspecial ( (c>='(' && c <= '/')|| (c >= ':' && c <= '>') ) // Caracteres permitidos no PL0
#define PalavraEspecial !strcmp(retorno,"BEGIN")||!strcmp(retorno,"VAR")||!strcmp(retorno,"END")||!strcmp(retorno,"ODD")||!strcmp(retorno,"CALL")||!strcmp(retorno,"IF")||!strcmp(retorno,"WHILE")||!strcmp(retorno,"IF")||!strcmp(retorno,"THEN")||!strcmp(retorno,"DO")||!strcmp(retorno,"PROCEDURE")
#define Outro !Numero && !Letra && !CaracterEspecial && c != EOF &&  c != '\n' && c!=' '
/* Verifica se eh palavra reservada */
int verificar_palavras_reservadas(char *retorno){
    if(PalavraEspecial)
        return 1;
    return 0;
}

/* Verifica se o que esta lendo eh ident */
void verif_ident(FILE *arq){ 

    int cont = 0;
    char retorno[1000];    
    char c = '$';

    c = fgetc(arq);
       
    if(Letra)
    	while(Numero || Letra){
        	retorno[cont] = c;
        	c = fgetc(arq);
        	cont++;
    	}
    else{
	 fseek(arq,SEEK_CUR,-1);
	 return;
    	
    }

    if(cont == 0)
    	cont++;    
    retorno[cont] = '\0';
	

    if(Outro){
	    printf("%c, <ERRO_LEXICO>\n", c);
	    return;
    }
    else if(verificar_palavras_reservadas(retorno)){
    	printf("%s, %s \n",retorno, retorno);
    } else
	printf("%s, ident\n",retorno);
    fseek(arq,SEEK_CUR,-1);    
    return;
}

/* Verifica comentario*/
void verif_comentario(FILE *arq){
    
    char c = fgetc(arq);

    if(c == '{'){
        while(c!='}' && c!= EOF)
            c = fgetc(arq);
	if(c == EOF){
	    fseek(arq,SEEK_CUR,-1);
            printf("Comentario não está fechado\n");
            return;
        }
    }
    else 
    	fseek(arq,SEEK_CUR,-1);
    return;
}

void verif_menor(FILE *arq){
    char c = fgetc(arq);
    if(c == '>'){
        c = fgetc(arq);
        if(c == '=')
            printf("maior e igual\n");
        else
            fseek(arq, SEEK_CUR, -1);
    }
    else
        fseek(arq, SEEK_CUR, -1);
    return;
}

void verif_maior(FILE *arq){
    char c = fgetc(arq);

    if(c == '<'){
        c = fgetc(arq);
        if(c == '>')
            printf("maior e igual\n");
        else if(c == '=')
            printf("maior e igual\n");
        else
            fseek(arq, SEEK_CUR, -1);
    }
    else
        fseek(arq, SEEK_CUR, -1);
    return;
}

void verif_simb(FILE *arq){
    char c = fgetc(arq);
    if(c == '+')
        printf("mais\n");
    else if(c == '-')
        printf("menos\n");
    else if(c == ',')
        printf("virgula\n");
    else if(c == '.')
        printf("ponto\n");
    else if(c == ';')
        printf("ponto e virgula\n");
    else if(c == '*')
        printf("mult\n");
    else if(c == '/')
        printf("div\n");
    else if(c == '(' || c == ')')
        printf("sei la\n");
    else
    	fseek(arq, SEEK_CUR, -1);
    return;
}

void verif_atrib(FILE *arq){
    char c = fgetc(arq);
    if(c == ':'){
        c = fgetc(arq);
        if(c == '=')
            printf("atrib\n");
        else 
            fseek(arq,SEEK_CUR, -1);
    }
    else
        fseek(arq, SEEK_CUR, -1);
    return;
}

void verif_num(FILE *arq){
    char c = fgetc(arq);

    while(Numero){
	printf("%c",c);
        c = fgetc(arq);
    }

    fseek(arq,SEEK_CUR,-1);
    return 0;

}
void verif_espaco(FILE *arq){
	char c = fgetc(arq);
	if(c!=' '&& c != '	' && c != '\n')
		fseek(arq,SEEK_CUR,-1);
	return;
}

int verif_eof(FILE*arq){
	char c = fgetc(arq);
	
	if(c==EOF)
		return 1;

	fseek(arq,SEEK_CUR,-1);
	return 0 ;

}
void automato(FILE *arq){
    int flag = 0;
    while (!flag){
	verif_espaco(arq);
        verif_ident(arq);
        verif_atrib(arq);
        verif_simb(arq);
        verif_menor(arq);
        verif_maior(arq);
        verif_comentario(arq);
        verif_num(arq);
	flag = verif_eof(arq);
    }
}

int main(){
    FILE *arq;

    char teste = '%';
    arq = fopen("teste.txt","r");
    fseek(arq,SEEK_SET,0);
    automato(arq);
    fclose(arq);
    return 0;
}
