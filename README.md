# JVM
Universidade de Brasília
Software Básico
2023/1 

## Integrantes
- Thiago Elias dos Reis - 190126892
- André Larrosa Chimpliganond - 190010321
- Marcus Vinicius Oliveira de Abrantes - 190034084
- Moisés Felipe Jacó Andrade de Lima - 190018364
- Matheus Barbosa e Silva - 190113987

## Compilar
A compilação é feita a partir de de um arquivo [makefile](https://www.gnu.org/software/make/). Utilize o comando `make` para compilar os arquivos.

## Leitor-exibidor
Para executar o leitor-exibidor utilize o comando `$ ./jvm.exe -e ./examples/<nome_da_classe>.class` para alguma das classes disponíveis no diretório `examples`. Será criado um novo diretório com um arquivo de texto relativo à classe escolhida, `out/<nome_da_classe>.txt`.

## Interpretador
Para executar o interpretador utilize o comando `$ ./jvm.exe -i ./examples/<nome_da_classe>.class` para alguma das classes disponíveis no diretório `examples`. Será impresso no terminal a execução do programa relativo à classe escolhida.

## Documentação
Documentação criada a partir do [Doxygen](https://www.doxygen.nl/index.html). Utilize o comando `$ dosygen Doxyfile`. Será criado um novo diretório, abro o arquivo `doxygen/files.html` no browser para visualizar a documentação.