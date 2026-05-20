#ifndef prototypes_h
#define prototypes_h
#include "raylib.h"

//Definição dos estados do jogo
typedef enum {
    LOGO,
    MENU,
    JOGANDO,
    PAUSE
} GameState;

// Protótipos das funções
void Atualizar_Logo(GameState *estado, int *temporizador);
void Atualizar_Menu(GameState *estado);
void Pausar_Jogo(GameState *estado);
void Mover_Nave(float *velocidade);

#endif