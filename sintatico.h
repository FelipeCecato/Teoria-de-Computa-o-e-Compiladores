#ifndef SINTATICO_H
#define SINTATICO_H

#include <stdio.h>

typedef struct {
    const char* symbol;
    const char* followers[10];
} FollowSet;

void analisador_sintatico(FILE* source_file);
void mais_const(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void constante(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void mais_var(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void variavel(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void expressao(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void fator(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void mais_fatores(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void mais_termos(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void condicao(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void comando(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void mais_cmd(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void procedimento(char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void obter_token(char **token, char *classe, FILE *source_file, int *linha);
void erro(int codigo, char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void printError(int codigo, char **token, char *classe, FILE *source_file, int *linha, LinkedList *simb_sincr, int *pilhaRegras);
void desempilharRegra(int *pilhaRegras);
void empilharRegra(char *regra, int *pilhaRegras);
void gerarSimSincr(int *pilhaRegras, LinkedList *simb_sincr );

#endif