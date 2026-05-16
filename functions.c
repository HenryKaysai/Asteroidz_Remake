#include "raylib.h"
#include "prototypes.h"

//Atualiza o estado LOGO para estado MENU
void AtualizarLogo(GameState *estado, int *temporizador){
    (*temporizador)++;
    if ((*temporizador) > 180) { //Quando se passarem 3 segundos, o jogo sai do logo e vai para o menu (60FPS * 3)
        *estado = MENU;
    }
}

//Atualiza o estado MENU e vai para o estado JOGANDO
void AtualizarMenu(GameState *estado){
    if (IsKeyPressed(KEY_ENTER)){
        *estado = JOGANDO;
    }
}