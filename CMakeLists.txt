cmake_minimum_required(VERSION 3.31)
project(untitled C)

set(CMAKE_C_STANDARD 11)


add_executable(untitled
        main.c
        compressor.c
        descompressor.c
        huffman.c
        tabela_de_frequencias.c
        fila_prioridade.c
        codigo.c
)

