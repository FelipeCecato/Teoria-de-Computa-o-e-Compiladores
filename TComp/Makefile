# Nome do seu programa executável
EXECUTAVEL := exec

# Variável para o argumento padrão
ARG_PADRAO := argumento.txt

all: exec

exec: main.c
	gcc -g -o exec main.c

# Diretiva "run" para executar o programa com o argumento especificado
run: exec
	@./$(EXECUTAVEL)	$(ARG)

# Diretiva "run" com argumento padrão
run_default:
	@./$(EXECUTAVEL)	$(ARG_PADRAO)
