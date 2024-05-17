# Alex - Analisador Léxico

A linguagem PL0 é uma linguagem simples usada principalmente para fins educacionais e acadêmicos no estudo de compiladores e linguagens de programação. 

Este projeto implementa um analisador léxico, o Alex, capaz de analisar programas escritos em PL0 e identificar tokens válidos de acordo com a gramática da linguagem. Ele é projetado para ser uma ferramenta útil para aqueles que desejam compreender melhor a estrutura e o funcionamento de analisadores léxicos e compiladores.

# Instalação e uso

## Primeira forma de executar

A primeira forma de utilizar o `alex` é realizando a sua instalação por meio do comando:

```
sudo make install
```

Isso irá criar um link simbólico para o executável no diretório ‘/usr/local/bin’, sendo por isso necessário executar o comando com privilégios de superusuário. Em seguida, o código estará pronto para execução por meio do comando:

```
alex entrada.txt
```

sendo `entrada.txt` o arquivo que se deseja extrair os tokens. O resultado da execução é o arquivo `entrada_tokens.txt`, contendo os tokens do programa fonte.


Para desinstalar, ou seja, remover o arquivo executável e seu link simbólico, basta executar o comando

```
sudo make uninstall
```

## Segunda forma de executar 

Se preferir utilizar o programa sem realizar a sua instalação no sistema, você pode optar pela execução direta do executável, o primeiro passo é gerar o executável com o seguinte comando:

```
make all
```

ou ainda 

```
make alex
```

Este comando compila o código fonte do programa e cria um executável na pasta atual. Isso permite que você utilize o programa sem a necessidade de uma instalação completa.

Em seguida, basta executá-lo passando como argumento o arquivo txt de entrada:

```
make run ARG=entrada.txt
```

Aqui, `entrada.txt` é o arquivo que você deseja processar. Os tokens extraídos serão inseridos no arquivo de saída que receberá o nome de `entrada_tokens.txt`.

Após a utilização do programa, caso se deseje remover o arquivo executável, basta utilizar o comando:

```
make clean
```