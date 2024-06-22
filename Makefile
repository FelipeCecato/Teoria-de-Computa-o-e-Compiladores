EXECUTAVEL := alex

.PHONY: help

help:	# Exibe o conteúdo de ajuda
	@echo "Uso: make [comando]"
	@echo ""
	@echo "Comandos disponíveis:"
	@awk 'BEGIN {FS = ":.?# "} /^[a-zA-Z_-]+:.?# / {printf "  %-20s # %s\n", $$1, $$2}' $(MAKEFILE_LIST)

all: alex	# Compila e gera o executável 

alex: # Compila e gera o executável
	gcc -g -o $(EXECUTAVEL) main.c automato.c sintatico.c listas_encadeadas_simples/simple_linked_list.c

clean: # Remove o executável 
	rm -f $(EXECUTAVEL)

install: alex # Instala o alex 
	ln -s $(CURDIR)/$(EXECUTAVEL) /usr/local/bin

uninstall: # Desinstala o alex 
	rm -f /usr/local/bin/$(EXECUTAVEL)
	rm -f $(EXECUTAVEL)

run: # Executa o alex. Necessita dos argumentos [ARQ_ENTRADA] e [ARQ_SAIDA]
	./$(EXECUTAVEL) $(ARQ_ENTRADA) $(ARQ_SAIDA)