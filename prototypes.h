#ifndef prototypes_h
#define prototypes_h

#include "raylib.h"

#define LARGURA_TELA 1200
#define ALTURA_TELA 800

//Definição dos estados do jogo
typedef enum {
    LOGO,
    MENU,
    JOGANDO,
    PAUSE
} GameState;

//Carregamento das texturas e variáveis utilitárias
typedef struct{
    Texture2D Nave;
    Vector2 pivo_nave;
    Texture2D Asteroid_1;
    Texture2D Asteroid_2;
    Texture2D Asteroid_3;

    //variáveis
    float angulo_nave;
    int frame_atual;
    int contador_tempo;
    int velocidade_animacao;

}Contextos_Jogo;


// Protótipos das funções
void Desenha_Menu_Principal(void);
void Desenha_Menu_Pausa(void);
void Carregar_Texturas(Contextos_Jogo *ctx);
void Descarregar_Texturas(Contextos_Jogo *ctx);
void Atualizar_Logo(GameState *estado, int *temporizador);
void Atualizar_Menu(GameState *estado);
void Pausar_Jogo(GameState *estado);
void Mover_Nave(float *velocidade);
void Gira_Nave(float *angulo);
void Atualiza_Nave(int *frame, int *contador, int velocidade);
void Desenha_Texto_Centralizado(const char* texto, int pos_y, int tamanho_fonte, Color cor);

#endif