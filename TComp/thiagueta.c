#include<stdio.h> 
#include<stdlib.h>

#define Numero ( c>= '0' && c<='9' ) // Numeros de 0 a 9
#define Letra ( c>='A' && c<='z' ) // Letras do alfabeto
#define CaracterEspecial ( c>='(' && c <= '/') // Caracteres permitidos no PL0

char *verif_ident(FILE *arq){ // Verifica se o que esta lendo eh ident

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

    if(Numero||Letra||Especial){
        printf("%s, ident\n", retorno);

    }

    else if (c != EOF)
        return; // SEI LA O Q RETORNA
    else
        printf("%s, <ERRO_LEXICO>\n", retorno);

}




int main(int argc, char **argv){





}
