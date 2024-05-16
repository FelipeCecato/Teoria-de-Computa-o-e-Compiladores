EXECUTAVEL := alex
ARG_PADRAO := teste.txt

.PHONY: help

help:	# Exibe o conteúdo de ajuda
	@echo "Uso: make [comando]"
	@echo ""
	@echo "Comandos disponíveis:"
	@awk 'BEGIN {FS = ":.?# "} /^[a-zA-Z_-]+:.?# / {printf "  %-20s # %s\n", $$1, $$2}' $(MAKEFILE_LIST)

all: # Compila e gera o executável 
	gcc -o $(EXECUTAVEL) main.c

clean: # Remove o executável 
	rm -f $(EXECUTAVEL)

install: # Instala o alex 
	ln -s $(CURDIR)/$(EXECUTAVEL) /usr/local/bin

uninstall: # Desinstala o alex 
	rm -f /usr/local/bin/$(EXECUTAVEL)

run: # Executa o alex 
	./$(EXECUTAVEL) $(ARG)

run_default: # Executa o alex com o arquivo padrão teste.txt 
	./$(EXECUTAVEL) $(ARG_PADRAO)
