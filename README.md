# Montador

## Informações

Natalia Oliveira Borges - 16/0015863

Lívia Gomes Costa Fonseca - 16/0034078

Esse trabalho foi feito usando a linguagem de programação C++11, compilado usando g++ em ambiente Linux Ubuntu 16.04.

O GitHub do projeto pode ser acessado pelo [link](https://github.com/natioliveira97/SB).

## Objetivos

Esse trabalho é uma implementação de um montador que transforma um arquivo texto da linguagem assembly inventada em aula em arquivo objeto.

## Conteúdo do pacote

O trabalho foi dividido em vários arquivos, são eles:

- scanner.cpp
- scanner.hpp
- parser.cpp
- parser.hpp
- pre_processor.cpp
- pre_processor.hpp
- montador.cpp
- montador.hpp

Para auxiliar a compilação também foi feito um Makefile.

## Como compilar:

Para compilar esse trabalho faça:

```bash
make
```

## Como executar:

Para executar esse trabalho faça:

```bash
./tradutor myprogram.asm
```