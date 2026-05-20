#include "raylib.h"
#include "prototypes.h"

//Atualiza o estado LOGO para estado MENU
void Atualizar_Logo(GameState *estado, int *temporizador){
    (*temporizador)++;
    if ((*temporizador) > 180) { //Quando se passarem 3 segundos, o jogo sai do logo e vai para o menu (60FPS * 3)
        *estado = MENU;
    }
}

//Atualiza o estado MENU e vai para o estado JOGANDO
void Atualizar_Menu(GameState *estado){
    if (IsKeyPressed(KEY_ENTER)){
        *estado = JOGANDO;
    }
}

//Volta do Estado PAUSE para o JOGANDO
void Pausar_Jogo(GameState *estado){
    if(IsKeyPressed(KEY_ESCAPE)){
        *estado = JOGANDO;
        HideCursor(); 
        DisableCursor();
    }
}

//Define uma função que vai ativar a turbina da nave
void Mover_Nave(float *velocidade){
    if (IsKeyPressed(KEY_SPACE)){
        *velocidade += 1;
    }
}