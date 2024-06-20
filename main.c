#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msgnsErro.h"
#include "sintatico.h"

int main(int argc, char const *argv[]) {

    if(argv[1] == NULL){
        ERRO_NO_INPUT_FILES
        exit(-1);//encerra o programa
    }

    //aloca espaço para a variável que vai salvar o nome do arquivo
    char* source_filename = malloc(sizeof(char)*strlen(argv[1])+1);
    if(source_filename == NULL) {//imprime uma mensagem de erro caso a alocação falhe
        ERRO_ALOCACAO
        exit(-1);//encerra o programa 
    }

    //copia o nome do arquivo e abre em modo leitura
    strcpy(source_filename, argv[1]);
    FILE *source_file;
    source_file = fopen(source_filename, "r");
    if(source_file == NULL){//imprime uma mensagem de erro caso a abertura do arquivo falhe
        ERRO_ARQUIVO
        exit(-1);//encerra o programa
    }

/*
    //cria o arquivo de saída
    char* output_filename;
    if(argv[2] == NULL) { 

        char *source_filename_tok = strtok(source_filename, ".");
        size_t output_filename_length = strlen(source_filename_tok) + strlen("_tokens.txt");
        output_filename = malloc(sizeof(char)*output_filename_length);
        if(output_filename == NULL) {//imprime uma mensagem de erro caso a alocação falhe
            ERRO_ALOCACAO
            exit(-1);//encerra o programa 
        }
        strcpy(output_filename, source_filename_tok);
        strcat(output_filename, "_tokens.txt");

    } else {

        output_filename = malloc(sizeof(char)*strlen(argv[2])+1);
        if(output_filename == NULL) {//imprime uma mensagem de erro caso a alocação falhe
            ERRO_ALOCACAO
            exit(-1);//encerra o programa 
        }
        strcpy(output_filename, argv[2]);

    }

    
    FILE *output_file;
    output_file = fopen(output_filename, "w");
    if(output_file == NULL){//imprime uma mensagem de erro caso a abertura do arquivo falhe
        ERRO_ARQUIVO
        exit(-1);//encerra o programa
    }
*/
    analisador_sintatico(source_file);
    
    //libera memória 
    free(source_filename);
    //free(output_filename);


    //fecha o arquivo
    //fclose(output_file);
    fclose(source_file);
    return 0;

}
