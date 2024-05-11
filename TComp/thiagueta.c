#include<stdio.h> 
#include<stdlib.h>

#define Numero ( c>= '0' && c<='9' ) // Numeros de 0 a 9
#define Letra ( c>='A' && c<='z' ) // Letras do alfabeto
#define CaracterEspecial ( c>='(' && c <= '/') // Caracteres permitidos no PL0
#define PalavraEspecial !strcmp(retorno,"BEGIN")||!strcmp(retorno,"VAR")||!strcmp(retorno,"END")||!strcmp(retorno,"ODD")||!strcmp(retorno,"CALL")||!strcmp(retorno,"IF")||!strcmp(retorno,"WHILE")||!strcmp(retorno,"IF")||!strcmp(retorno,"THEN")||!strcmp(retorno,"DO")||!strcmp(retorno,"PROCEDURE")

/* Verifica se eh palavra reservada */
int verificar_palavras_reservadas(retorno){
    if(PalavraEspecial)
        return 1;
    return 0;
}

/* Verifica se o que esta lendo eh ident */
char *verif_ident(FILE *arq){ 

    int cont = 0;
    char *retorno;    
    char c;
    c = fgetc(arq);
    
    while(Numero || Letra){
        retorno[cont] = c;
        c = fgetc(arq);
        cont++;
    }

    fseek(arq,SEEK_CUR,-1);

    if(Especial){
        if(verificar_palavras_reservadas(retorno))
            printf("%s, %s", retorno)
        else
            printf("%s, ident\n", retorno);
    }

    else if (c != EOF)
        return; // SEI LA O Q RETORNA
    else
        printf("%s, <ERRO_LEXICO>\n", retorno);

}

int main(int argc, char **argv){

printf("aaaaaaaaaaaaa");



}
