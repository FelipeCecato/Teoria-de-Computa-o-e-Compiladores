#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msgnsErro.h"

#define undefined -1
#define MAX_CLASSE_LENGHT 32
#define true 1
#define false 0

//qual a melhor forma de implementar isso de transição? talvez usar uma matriz seja uma boa ideia
char transicao(const char s, const char c) {

    if(s == 0) {

        if(c == '+')
            return 15;
        
        if(c == '-')
            return 13;

        if(c == '/')
            return 19;

        if(c == '*')
            return 20;

        if(c == '.')
            return 14;

        if(c == '=')
            return 12;
    }

}

char estado_final(char s) {

    if(s == 12 ||
       s == 13 ||
       s == 15 ||
       s == 19 ||
       s == 20 ||
       s == 14)
        return true;

    return false;

}

void definir_classe(char *classe, const char s) {

    switch (s) {

        case 12:
            strcpy(classe, "<simb_igual>");
            break;

        case 13:
            strcpy(classe, "<simb_subtracao>");
            break;

        case 14:
            strcpy(classe, "<simb_ponto>");
            break;

        case 15:
            strcpy(classe, "<simb_soma>");
            break;

        case 19:
            strcpy(classe, "<simb_divisao>");
            break;

        case 20:
            strcpy(classe, "<simb_multiplicacao>");
            break;

        default://colocar <ERRO_LEXICO> aqui?
            break;

    }
}

int main(int argc, char const *argv[]) {

    //aloca espaço para a variável que vai salvar o nome do arquivo
    char* filename = malloc(sizeof(char)*strlen(argv[1]));
    if(filename == NULL) {//imprime uma mensagem de erro caso a alocação falhe
        ERRO_ALOCACAO
        return -1; 
    }

    //copia o nome do arquivo e abre em modo leitura
    strcpy(filename, argv[1]);
    FILE *source_file;
    source_file = fopen(filename, "r");
    if(source_file == NULL){//imprime uma mensagem de erro caso a abertura do arquivo falhe
        ERRO_ARQUIVO
        return -1;
    }

    //cria o arquivo de saída
    FILE *output_file;
    output_file = fopen("saida.txt", "w");
    if(output_file == NULL){//imprime uma mensagem de erro caso a abertura do arquivo falhe
        ERRO_ARQUIVO
        return -1;
    }

    char *token;
    token = malloc(sizeof(char));
    char *token_ini = token;
    *token = '\n';
    if(token == NULL) {//imprime uma mensagem de erro caso a alocação falhe
        ERRO_ALOCACAO
        return -1; 
    }

    char *classe;
    classe = malloc(sizeof(char)*MAX_CLASSE_LENGHT);
    if(classe == NULL) {//imprime uma mensagem de erro caso a alocação falhe
        ERRO_ALOCACAO
        return -1; 
    }

    char c, s;
    c = fgetc(source_file);
    s = 0;


    while (c != EOF) {

        //adiciona o caractere c à cadeia do token
        token = realloc(token, (strlen(token)+1)*sizeof(char));
        strncat(token, &c, 1);

        s = transicao(s,c);

        if(s == undefined) {

            strcpy(classe, "<ERRO_LEXICO>");
            fwrite(token, sizeof(char)*strlen(token), 1, output_file);
            fwrite(", ", sizeof(char)*strlen(", "), 1, output_file);
            fwrite(classe, sizeof(char)*strlen(classe), 1, output_file);
            fwrite("\n", sizeof(char)*strlen("\n"), 1, output_file);
            s = 0;
            token = realloc(token, sizeof(char));
            strcpy(token, "");

        }

        if(estado_final(s)) {

            definir_classe(classe, s);
            fwrite(token, sizeof(char)*strlen(token), 1, output_file);
            fwrite(", ", sizeof(char)*strlen(", "), 1, output_file);
            fwrite(classe, sizeof(char)*strlen(classe), 1, output_file);
            fwrite("\n", sizeof(char)*strlen("\n"), 1, output_file);
            s = 0;
            token = realloc(token, sizeof(char));
            strcpy(token, "");

        }
            
        c = fgetc(source_file);

    }
    
    //libera memória 
    free(filename);
    free(output_file);
    free(token);
    free(classe);

    //fecha o arquivo
    fclose(output_file);
    fclose(source_file);
    return 0;

}