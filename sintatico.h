#ifndef SINTATICO_H
#define SINTATICO_H

#include <stdio.h>

void analisador_sintatico(FILE* source_file);
void mais_const(char **token, char *classe, FILE *source_file);
void constante(char **token, char *classe, FILE *source_file);
void mais_var(char **token, char *classe, FILE *source_file);
void variavel(char **token, char *classe, FILE *source_file);
void expressao(char **token, char *classe, FILE *source_file);
void fator(char **token, char *classe, FILE *source_file);
void mais_fatores(char **token, char *classe, FILE *source_file);
void mais_termos(char **token, char *classe, FILE *source_file);
void condicao(char **token, char *classe, FILE *source_file);
void comando(char **token, char *classe, FILE *source_file);
void mais_cmd(char **token, char *classe, FILE *source_file);
void procedimento(char **token, char *classe, FILE *source_file);

#endif