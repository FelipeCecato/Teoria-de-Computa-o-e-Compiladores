#ifndef MSGNSERRO_H
#define MSGNSERRO_H

#include <stdio.h>
//define as mensagens de erro
#define ERRO_ALOCACAO fprintf(stderr, "alex: erro: Falha ao alocar memoria!\n");
#define ERRO    fprintf(stderr, "alex: erro: falha no processamento do arquivo.\n");
#define ERRO_ARQUIVO    fprintf(stderr, "alex: erro: falha na abertura do arquivo.\n");
#define ERRO_NO_INPUT_FILES fprintf(stderr, "alex: erro: sem arquivos de entrada\n");
#define ERRO_TRANSICAO fprintf(stderr, "alex: erro: transicao inexistente");
#define ERRO_LEXICO_1  fprintf(stderr, "alex: Erro lexico na linha %d: comentário não fechado: '%s' \n", *linha-1, *token);
#define ERRO_LEXICO_2  fprintf(stderr, "alex: Erro lexico na linha %d: caractere inválido ':', você quis dizer ':='?\n", *linha);
#define ERRO_LEXICO_3  fprintf(stderr, "alex: Erro lexico na linha %d: caractere invalido '%s'\n", *linha, *token);
#define ERRO_SINTATICO_1  fprintf(stderr, "alex: Erro sintatico na linha %d: código inesperado após o fim do programa\n", linha);

#endif