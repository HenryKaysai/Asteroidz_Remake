@echo off
echo Iniciando a compilacao do projeto...
echo ----------------------------------------

REM nome do executavel
set SAIDA=main.exe

REM arquivos .c (codigo fonte)
set FONTES=*.c

REM arquivos .h
set INCLUDES=-I . -I include

REM pasta de bibliotecas 
REM -lopengl32 -lgdi32 -lwinmm: bibliotecas do Windows que a Raylib precisa
set LIBS=-L lib -lraylib -lopengl32 -lgdi32 -lwinmm

REM Executa a compilacao
echo Compilando arquivos...
gcc %FONTES% %INCLUDES% %LIBS% -Wall -o %SAIDA%

REM 6. Verifica o resultado
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilacao concluida com sucesso!
    echo.
    echo Executando %SAIDA%...
    echo ----------------------------------------
    %SAIDA%
) else (
    echo.
    echo [ERRO] Falha na compilacao. Verifique os erros acima.
)

echo.
pause