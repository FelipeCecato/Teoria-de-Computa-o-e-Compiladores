#ifndef MSGNSERRO_H
#define MSGNSERRO_H

//define as mensagens de erro
#define ERRO_ALOCACAO printf("alex: erro: Falha ao alocar memoria!\n");
#define ERRO    printf("alex: erro: falha no processamento do arquivo.\n");
#define ERRO_ARQUIVO    printf("alex: erro: falha na abertura do arquivo.\n");
#define ERRO_NO_INPUT_FILES printf("alex: erro: sem arquivos de entrada\n");
#define ERRO_TRANSICAO  printf("alex: erro: transicao inexistente");
#define ERRO_LEXICO_1  printf("alex: Erro lexico na linha %d: comentário não fechado \n6", *linha);
#define ERRO_LEXICO_2  printf("alex: Erro lexico na linha %d: caractere inválido ':', você quis dizer ':='?\n", *linha);
#define ERRO_LEXICO_3  printf("alex: Erro lexico na linha %d: caractere invalido '%s'\n", *linha, *token);
#define ERRO_SINTATICO_1  printf("alex: Erro sintatico na linha %d: código inesperado após o fim do programa\n", linha);

#endif