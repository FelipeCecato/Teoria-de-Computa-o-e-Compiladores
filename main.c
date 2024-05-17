#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msgnsErro.h"
#include "automato.h"

#define MAX_CLASSE_LENGHT 32

int main(int argc, char const *argv[]) {

    if(argv[1] == NULL){
        ERRO_NO_INPUT_FILES
        exit(-1);//encerra o programa
    }

    //aloca espaço para a variável que vai salvar o nome do arquivo
    char* source_filename = malloc(sizeof(char)*strlen(argv[1]));
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

    //cria o arquivo de saída
    source_filename = strtok(source_filename, ".");
    size_t output_filename_length = strlen(source_filename) + strlen("_tokens.txt");
    char* output_filename = malloc(sizeof(char)*output_filename_length);
    strcpy(output_filename, source_filename);
    strcat(output_filename, "_tokens.txt");
    FILE *output_file;
    output_file = fopen(output_filename, "w");
    if(output_file == NULL){//imprime uma mensagem de erro caso a abertura do arquivo falhe
        ERRO_ARQUIVO
        exit(-1);//encerra o programa
    }

    char *token;
    token = malloc(sizeof(char));
    *token = '\0';
    if(token == NULL) {//imprime uma mensagem de erro caso a alocação falhe
        ERRO_ALOCACAO
        exit(-1);//encerra o programa 
    }

    char *classe;
    classe = malloc(sizeof(char)*MAX_CLASSE_LENGHT);
    if(classe == NULL) {//imprime uma mensagem de erro caso a alocação falhe
        ERRO_ALOCACAO
        exit(-1);//encerra o programa 
    }
    
    //loop que chama várias vezes o autômato até processar todo o arquivo
    while (!automato(token, classe, source_file)) {

        //se a classe for diferente de "<comentario>", insere o par "token, classe" no arquivo de saída
        if(strcmp(classe, "<comentario>")) {

            fwrite(token, sizeof(char)*strlen(token), 1, output_file);
            fwrite(", ", sizeof(char)*strlen(", "), 1, output_file);
            fwrite(classe, sizeof(char)*strlen(classe), 1, output_file);
            fwrite("\n", sizeof(char)*strlen("\n"), 1, output_file);

        } 

        token = realloc(token, sizeof(char)*2);
        strcpy(token, "");

    }
    
    //libera memória 
    free(source_filename);
    free(output_filename);
    free(token);
    free(classe);

    //fecha o arquivo
    fclose(output_file);
    fclose(source_file);
    return 0;

}