#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#define Numero ( c>= '0' && c<='9' ) // Numeros de 0 a 9
#define Letra ( c>='A' && c<='z' ) // Letras do alfabeto
#define CaracterEspecial ( c>='(' && c <= '/') // Caracteres permitidos no PL0
#define PalavraEspecial !strcmp(retorno,"BEGIN")||!strcmp(retorno,"VAR")||!strcmp(retorno,"END")||!strcmp(retorno,"ODD")||!strcmp(retorno,"CALL")||!strcmp(retorno,"IF")||!strcmp(retorno,"WHILE")||!strcmp(retorno,"IF")||!strcmp(retorno,"THEN")||!strcmp(retorno,"DO")||!strcmp(retorno,"PROCEDURE")


/* Verifica se eh palavra reservada */
int verificar_palavras_reservadas(char *retorno){
    if(PalavraEspecial)
        return 1;
    return 0;
}

/* Verifica se o que esta lendo eh ident */
int verif_ident(FILE *arq){ 

    int cont = 0;
    char retorno[1000];    
    char c = '$';
    c = fgetc(arq);
    
    while(Numero || Letra){
        retorno[cont] = c;
        c = fgetc(arq);
        cont++;
    }

    retorno[cont-1] = '\0';

    fseek(arq,SEEK_CUR,-1);

    if(CaracterEspecial){
        if(verificar_palavras_reservadas(retorno))
            printf("%s, %s", retorno, retorno);
        else
            printf("%s, ident\n", retorno);
    }

    else if (c != EOF){
        if(c != '\n')
            printf("%s, <ERRO_LEXICO>\n", retorno);
    }
    else
        return 1; 
    return 0;
}

/* Verifica comentario*/
int verif_comentario(FILE *arq){
    char c;
    c = fgetc(arq);
    if(c == '{')
    while(c!='}' && c!= EOF)
        c = fgetc(arq);
    if(c== EOF){
        printf("Comentario não está fechado\n");
        return 1;
    }
    return 0;
}

int verif_menor(FILE *arq){
    char c;
    c = fgetc(arq);
    if(c == '>'){
        c = fgetc(arq);
        if(c == '=')
            printf("maior e igual\n");
        else
            fseek(arq, SEEK_CUR, -1);
    }
    else
        fseek(arq, SEEK_CUR, -1);
    return 0;
}

int verif_maior(FILE *arq){
    char c;
    c = fgetc(arq);

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
    return 0;
}

int verif_simb(FILE *arq){
    char c;
    c = fgetc(arq);
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

    fseek(arq, SEEK_CUR, -1);
    return 0;
}

int verif_atrib(FILE *arq){
    char c;
    c = fgetc(arq);
    if(c == ':'){
        c = fgetc(arq);
        if(c == '=')
            printf("atrib\n");
        else 
            fseek(arq,SEEK_CUR, -1);
    }
    else
        fseek(arq, SEEK_CUR, -1);
    return 0;
}

int verif_num(FILE *arq){
    char c;
    c = fgetc(arq);
    while(Numero){
        c = fgetc(arq);
        printf("loucuraboy");
        if(!Numero)
            fseek(arq, SEEK_CUR,-1);
    }
    return 0;

}

void automato(FILE *arq){
    int flag = 0;
    while (!flag){
        flag += verif_ident(arq);
        flag += verif_atrib(arq);
        flag += verif_simb(arq);
        flag += verif_menor(arq);
        flag += verif_maior(arq);
        flag += verif_comentario(arq);
        flag += verif_num(arq);
    }
}

int main(){
    FILE *arq;
    arq = fopen("teste.txt","r");
    automato(arq);
    return 0;
}
