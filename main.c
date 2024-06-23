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


    analisador_sintatico(source_file);
    
    //libera memória 
    free(source_filename);


    //fecha o arquivo
    fclose(source_file);
    return 0;

}
