#ifndef prototypes_h
#define prototypes_h
#include "raylib.h"

//Definição dos estados do jogo
typedef enum {
    LOGO,
    MENU,
    JOGANDO
} GameState;

// Protótipos das funções
void AtualizarLogo(GameState *estado, int *temporizador);
void AtualizarMenu(GameState *estado);

#endif