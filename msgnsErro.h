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
#define ERRO_SINTATICO_1(linha)  fprintf(stderr, "alex: Erro sintatico na linha %d: código inesperado após o fim do programa\n", linha);
#define ERRO_SINTATICO_2 fprintf(stderr, "alex: Erro sintatico na linha %d: símbolo '=' faltando\n", *linha);
#define ERRO_SINTATICO_3 fprintf(stderr, "alex: Erro sintatico na linha %d: valor da contante faltando\n", *linha);
#define ERRO_SINTATICO_4 fprintf(stderr, "alex: Erro sintatico na linha %d: símbolo ';' faltando\n", *linha);
#define ERRO_SINTATICO_5 fprintf(stderr, "alex: Erro sintatico na linha %d: símbolo ':=' faltando\n", *linha);
#define ERRO_SINTATICO_6 fprintf(stderr, "alex: Erro sintatico na linha %d: identificador faltando\n", *linha);
#define ERRO_SINTATICO_7 fprintf(stderr, "alex: Erro sintatico na linha %d: cláusula 'END' faltando\n", *linha);
#define ERRO_SINTATICO_8 fprintf(stderr, "alex: Erro sintatico na linha %d: cláusula 'THEN' faltando\n", *linha);
#define ERRO_SINTATICO_9 fprintf(stderr, "alex: Erro sintatico na linha %d: cláusula 'DO' faltando\n", *linha);
#define ERRO_SINTATICO_10 fprintf(stderr, "alex: Erro sintatico na linha %d: cláusula 'ODD' faltando\n", *linha);
#define ERRO_SINTATICO_11 fprintf(stderr, "alex: Erro sintatico na linha %d: expressão faltando\n", *linha);
#define ERRO_SINTATICO_12 fprintf(stderr, "alex: Erro sintatico na linha %d: símbolo ')' faltando\n", *linha);
#define ERRO_SINTATICO_13 fprintf(stderr, "alex: Erro sintatico na linha %d: operador relacional faltando\n", *linha);
#define ERRO_SINTATICO_14 fprintf(stderr, "alex: Erro sintatico na linha %d: condição faltando\n", *linha);
#define ERRO_SINTATICO_15 fprintf(stderr, "alex: Erro sintatico na linha %d: 'ODD' inesperado\n", *linha);

#endif