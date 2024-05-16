#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "msgnsErro.h"

#define undefined -1
#define MAX_CLASSE_LENGHT 32
#define true 1
#define false 0

#define NUM_PALAVRAS_RESERVADAS 11

//matriz de palavras reservadas
const char *palavras_reservadas[NUM_PALAVRAS_RESERVADAS] = {
    "CONST", "VAR", "PROCEDURE", "CALL", "BEGIN", "END", "IF", "THEN", "WHILE", "DO", "ODD"
};

char verifica_palavras_reservadas(char *classe, const char *token) {

    for (int i = 0; i < NUM_PALAVRAS_RESERVADAS; i++) {

        if (!strcmp(token, palavras_reservadas[i])) {

            strcpy(classe, "<");
            strcat(classe, palavras_reservadas[i]);
            strcat(classe, ">");
            return true;

        }
    }
    
    return false;

}

char consumir_caractere(char c) {

    if(c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == ' ' || c == ',')
        return true;

    return false;

}

//qual a melhor forma de implementar isso de transição? talvez usar uma matriz seja uma boa ideia
char transicao(const char s, const char c, FILE *source_file) {

    if(s == 0) {

        if(c == '(')
            return 26;
        
        if(c == ')')
            return 25;

        if(c == '+')
            return 15;
        
        if(c == ',')
            return 13;

        if(c == '-')
            return 23;

        if(c == '/')
            return 19;

        if(c == '*')
            return 20;

        if(isdigit(c))
            return 21;

        if(c == '.')
            return 14;

        if(c == '=')
            return 12;

        if(c == '{')
            return 1;
        
        if(c == ';')
            return 18;
        
        if(isalpha(c))
            return 3;
        
        if(c == '<')
            return 7;
        
        if(c == '>')
            return 8;

        if(c == ':')
            return 16;

        //consome espaços em branco, tabulações e quebras de linha 
        if(c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == ' ' || c == ',')     
            return 0;   
        
        return undefined;

    }

    if(s == 1) {

        //se identificar o fim do comentário avança para o estado 2, 
        if(c == '}')
            return 2;

        //se houve quebra de linha sem '}' relatar erro
        if(c == '\n')
            return undefined;

        return 1;
    }

    if(s == 3) {

        //enquanto forem identificados letras ou dígitos ou '_' ele mantém o autômato no estado 3
        if(isalnum(c) || c == '_')
            return 3;

        fseek(source_file, -1, SEEK_CUR);
        return 4;
        
    }

    if(s == 7) {
        
        if(c == '=')
            return 11;
        
        if(c == '>')
            return 5;
        
        fseek(source_file, -1, SEEK_CUR);
        return 10;

    }

    if(s == 8) {

        if(c == '=')
            return 9;

        fseek(source_file, -1, SEEK_CUR);
        return 6;

    }

    if(s == 16) {

        if(c == '=')
            return 17;

        fseek(source_file, -1, SEEK_CUR);
        return undefined;

    }

    if(s == 21) {

        if(c == isdigit(c))
            return 21;

        fseek(source_file, -1, SEEK_CUR);
        return 24;
    }

    return undefined;

}

char estado_final(char s) {

    if(s == 12 ||
       s == 13 ||
       s == 15 ||
       s == 19 ||
       s == 20 ||
 //      s == 22 ||
       s == 23 ||
       s == 24 ||
       s == 26 ||
       s == 25 ||
       s == 14 ||
       s == 17 ||
       s == 18 ||
       s == 10 ||
       s == 11 ||
       s == 5 ||
       s == 9 ||
       s == 6 ||
       s == 2 ||
       s == 4 ||
       s == undefined)
        return true;

    return false;

}

void definir_classe(char *classe, const char s, const char *token,FILE *source_file) {

    switch (s) {

        case 12:
            strcpy(classe, "<simb_igual>");
            break;

        case 13:
            strcpy(classe, "<virgula>");
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

        case 18:
            strcpy(classe, "<simb_ponto_virgula>");
            break;

        case 17:
            strcpy(classe, "<simb_atribuicao>");
            break;

        case 10:
            strcpy(classe, "<simb_menor>");
            break;

        case 5:
            strcpy(classe, "<simb_diferente>");
            break;

        case 11:
            strcpy(classe, "<simb_menor_igual>");
            break;

        case 6:
            strcpy(classe, "<simb_maior>");
            break;
        
        case 9:
            strcpy(classe, "<simb_maior_igual>");
            break;

        case 24:
            strcpy(classe, "<numero>");
            break;
        
        case 23:
            strcpy(classe, "<simb_subtracao>");
            break;

        case 26:
            strcpy(classe, "<abre_parenteses>");
            break;

        case 25:
            strcpy(classe, "<fecha_parenteses>");
            break;

        case 2:
            strcpy(classe, "<comentario>");
            break;

        case 4:
            if(!verifica_palavras_reservadas(classe, token))
                strcpy(classe, "<identificador>");
            break;

        default://colocar <ERRO_LEXICO> aqui?
            strcpy(classe, "<ERRO_LEXICO>");
            break;

    }
}

int automato(char * token, char *classe, FILE *source_file) {

    char c = 0, s = 0;

    while (c != EOF && !estado_final(s)) {

        c = fgetc(source_file);
        s = transicao(s,c, source_file);

        // se c, faz parte do alfabeto da linguagem, adiciona o caractere c à cadeia do token
        if(s != 4 && s != 24 && !consumir_caractere(c)){

            token = realloc(token, (strlen(token)+1)*sizeof(char));
            strncat(token, &c, 1);

        }
        
    }

    definir_classe(classe, s, token, source_file);

    return (c == EOF);

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
    *token = '\0';
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
    
    while (!automato(token, classe, source_file)) {

        fwrite(token, sizeof(char)*strlen(token), 1, output_file);
        fwrite(", ", sizeof(char)*strlen(", "), 1, output_file);
        fwrite(classe, sizeof(char)*strlen(classe), 1, output_file);
        fwrite("\n", sizeof(char)*strlen("\n"), 1, output_file);
        token = realloc(token, sizeof(char)*2);
        strcpy(token, "");

    }
    
    //libera memória 
    free(filename);
    free(token);
    free(classe);

    //fecha o arquivo
    fclose(output_file);
    fclose(source_file);
    return 0;

}