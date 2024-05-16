# Alex - Analisador Léxico

Este é um repositório destinado ao Alex, nosso analisador Léxico desenvolvido para a disciplina de Teoria de Computação e Compiladores.

# 1 Instalação e uso

## 1.1 Primeira forma de executar

A primeira forma de utilizar o `alex` é realizando a sua instalação por meio do comando:

```
sudo make install
```

Em seguida o alex estará pronto para uso por meio do comando:

```
alex entrada.txt
```

sendo `entrada.txt` o arquivo que se deseja extrair os tokens. O resultado da execução é o arquivo `entrada_tokens.txt`, contendo os tokens do programa fonte.


Para desinstalar basta executar o comando:

```
sudo make uninstall
```

## 1.2 Segunda forma de executar 

Asegunda forma de utilizar o alex, sem que seja necessário efetuar a sua instalação é gerando o executável utilizando o comando:

```
make all
```

Em seguida, basta executá-lo passando como argumento o arquivo txt de entrada:

```
make run ARG=entrada.txt
```

Após a utilização do programa, caso se deseje apagar o executável, basta utilizar o comando:

```
make clean
```

# 2 Dependências
