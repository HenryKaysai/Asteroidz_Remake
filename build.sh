#!/bin/bash

gcc *.c -o main -Iinclude/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

if [ $? -eq 0 ]; then
    echo "Sucesso! Compilacao concluida sem erros."
    echo "Para jogar, digite: ./main"
else
    echo "ERRO: A compilacao falhou. Verifique os avisos acima."
fi