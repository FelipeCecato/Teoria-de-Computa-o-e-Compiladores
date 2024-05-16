# Nome do seu programa executável
EXECUTAVEL := alex

# Variável para o argumento padrão
ARG_PADRAO := argumento.txt

all: alex

alex: main.c
	gcc -o alex main.c

clean:
	rm alex

install: alex
	ln -s $(CURDIR)/alex	/usr/local/bin

# Diretiva "run" para executar o programa com o argumento especificado
run: alex
	@./$(EXECUTAVEL)	$(ARG)

# Diretiva "run" com argumento padrão
run_default:
	@./$(EXECUTAVEL)	$(ARG_PADRAO)
