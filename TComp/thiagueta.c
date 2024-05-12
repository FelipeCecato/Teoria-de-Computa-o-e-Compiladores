#include<stdio.h> 
#include<stdlib.h>

#define Numero (c>= 0 && c<=9)
#define Letra (c>=A && c<=z)
#define Outro
#define CaracterEspecial




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

    if(Numero||Letra||Especial)
        printf("%s, ident\n", retorno);
    else
        printf("%s, <ERRO_LEXICO>\n", retorno);

}




int main(int argc, char **argv){





}
