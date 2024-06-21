#ifndef SINTATICO_H
#define SINTATICO_H

#include <stdio.h>

void analisador_sintatico(FILE* source_file);
void mais_const(char **token, char *classe, FILE *source_file, int *linha);
void constante(char **token, char *classe, FILE *source_file, int *linha);
void mais_var(char **token, char *classe, FILE *source_file, int *linha);
void variavel(char **token, char *classe, FILE *source_file, int *linha);
void expressao(char **token, char *classe, FILE *source_file, int *linha);
void fator(char **token, char *classe, FILE *source_file, int *linha);
void mais_fatores(char **token, char *classe, FILE *source_file, int *linha);
void mais_termos(char **token, char *classe, FILE *source_file, int *linha);
void condicao(char **token, char *classe, FILE *source_file, int *linha);
void comando(char **token, char *classe, FILE *source_file, int *linha);
void mais_cmd(char **token, char *classe, FILE *source_file, int *linha);
void procedimento(char **token, char *classe, FILE *source_file, int *linha);
void obter_token(char **token, char *classe, FILE *source_file, int *linha);

#endif