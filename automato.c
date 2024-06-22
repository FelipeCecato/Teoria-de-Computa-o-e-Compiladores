#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "msgnsErro.h"
#include "automato.h"
#include "listas_encadeadas_simples/simple_linked_list.h"

#define true 1
#define false 0
#define NUM_PALAVRAS_RESERVADAS 22

/// @brief vetor de palavras reservadas
const char *palavras_reservadas[NUM_PALAVRAS_RESERVADAS] = {
    "CONST", "const", 
    "VAR", "var", 
    "PROCEDURE", "procedure", 
    "CALL", "call", 
    "BEGIN", "begin", 
    "END", "end", 
    "IF", "if", 
    "THEN", "then", 
    "WHILE", "while", 
    "DO", "do", 
    "ODD", "odd"
};

/// @brief percorre o vetor checando se o token pertence à lista de palavras reservadas
/// @param classe - string usada para salvar a classe do token
/// @param token - string que contém o token
/// @return retorna verdadeiro se o teken é uma palavra reservada ou falso caso contrário
char verifica_palavras_reservadas(char *classe, const char *token) {

    for (int i = 0; i < NUM_PALAVRAS_RESERVADAS; i++) {

        if (!strcmp(token, palavras_reservadas[i])) {

            strcpy(classe, "<");
            strcat(classe, palavras_reservadas[(i%2 ? i-1 : i)]);
            strcat(classe, ">");
            return true;

        }
    }
    
    return false;

}

/// @brief verifica se o caractere c pertence a uma classe de caracteres a serem desprezados
/// @param c - caractere lido do código fonte
/// @return retoena verdadeiro se o caractere c for um dos caracteres a serem desprezados e falso caso contrário
char consumir_caractere(char c, int *linha) {

    if(c == '\n') {

        (*linha)++;
        //printf("%d\n", *linha);
        return true;

    }

    if(c == ' ' || c == '\r' || c == '\t' || c == ' ')
        return true;

    return false;

}


/// @brief função que implementa as transições do autômato, se nenhuma transição é encontrada, o código é interrompido
/// @param s - estado corrente do autômato
/// @param c - último caractere lido do código fonte
/// @param source_file - ponteiro para o arquivo de código fonte
/// @return retorna o próximo estado baseado no estado corrente e no último caractere lido do código fonte
char transicao(const char s, const char c, FILE *source_file, int *linha) {

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
        if(c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == ' ') 
            return 0;   
        
        return 22;

    }

    if(s == 1) {

        //se identificar o fim do comentário avança para o estado 2, 
        if(c == '}')
            return 2;

        //se houve quebra de linha sem '}' relatar erro
        if(c == '\n') {
            
            (*linha)++;
            return 27;

        }

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
        return 28;

    }

    if(s == 21) {

        if(isdigit(c))
            return 21;

        fseek(source_file, -1, SEEK_CUR);
        return 24;
    }

    ERRO_TRANSICAO
    exit(-1);//encerra o programa

}

/// @brief verifica se o estado s faz parte do conjunto de estados finais
/// @param s - estado corrente do autômato
/// @return retorna verdadeiro se s é estado final e falso caso contrário
char estado_final(char s) {

    if(s == 12 ||
       s == 13 ||
       s == 15 ||
       s == 19 ||
       s == 20 ||
       s == 22 ||
       s == 23 ||
       s == 24 ||
       s == 26 ||
       s == 27 ||
       s == 28 ||
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
       s == 4)
        return true;

    return false;

}

/// @brief função que define a classe do token
/// @param classe - string usada para armazenar a classe do token
/// @param s - estado corrente do autômato
/// @param token - string contendo o token 
/// @param source_file - ponteiro para o arquivo de código fonte
void definir_classe(char *classe, const char s, char *token, FILE *source_file, int *linha) {

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
            //estado 2 indica comentário, assim sendo, é preciso obter o próximo token
            strcpy(classe, "<comentario>");
            break;

        case 4:
            if(!verifica_palavras_reservadas(classe, token))
                strcpy(classe, "<identificador>");
            break;

        case 27:
            strcpy(classe, "<ERRO_LEXICO_1>");//ERRO_LEXICO_1 indica comentário não fechado
            break;
        
        case 28:
            strcpy(classe, "<ERRO_LEXICO_2>");//ERRO_LEXICO_2 indica o uso do token inválido ":"
            break;
        //case 22 
        default:
            strcpy(classe, "<ERRO_LEXICO_3>");//ERRO_LEXICO_3 indica caracateres que não pertencem ao alfabeto da linguagem (SyntaxError: Unexpected token ILLEGAL)
            break;

    }
}

/// @brief função que implementa o autômato
/// @param token - string onde será salvo o token lido do código fonte
/// @param classe - string onde será salvo a classe do token processado
/// @param source_file - ponteiro para o arquivo de código fonte
/// @return retorna verdadeiro se chegou ao fim do arquivo e falso caso contrário
int automato(char **token, char *classe, FILE *source_file, int *linha) {

    char c = 0, s = 0;
    strcpy(*token, "");
    strcpy(classe, "");

    //processa a cadeia até encontrar o fim do arquivo ou até atingir um estado final
    while (c != EOF && !estado_final(s)) {

        c = fgetc(source_file);
        s = transicao(s,c, source_file, linha);

        // se c, faz parte do alfabeto da linguagem, adiciona o caractere c à cadeia do token
        if((s != 4 && s != 24 && !consumir_caractere(c, linha)) || (s == 1 && c == ' ')){

            *token = realloc(*token, (strlen(*token)+2)*sizeof(char));
                if(*token == NULL) {//imprime uma mensagem de erro caso a alocação falhe
                ERRO_ALOCACAO
                exit(-1);//encerra o programa 
            }
            strncat(*token, &c, 1);

        }
        
    }

    definir_classe(classe, s, *token, source_file, linha);

    return (c == EOF);

}