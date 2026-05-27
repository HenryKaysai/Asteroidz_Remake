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
    PAUSE,
    SAVE,
    LOAD,
    BEST_SCORES,
    SAIR
} GameState;

//Carregamento das texturas e variáveis utilitárias
typedef struct{
    //texturas
    Texture2D Nave;
    Texture2D Asteroid_1;
    Texture2D Asteroid_2;
    Texture2D Asteroid_3;
    Vector2 pivo_nave;
    Texture2D Pink_Arrow;

    //variáveis
    float angulo_nave;
    int frame_atual;
    int contador_tempo;
    int velocidade_animacao;
    int opcao_selecionada;

}Contextos_Jogo;


// Protótipos das funções
void Desenha_Menu_Principal(int *opcao_selecionada);
void Desenha_Menu_Pausa(int *opcao_selecionada);
void Carregar_Texturas(Contextos_Jogo *ctx);
void Descarregar_Texturas(Contextos_Jogo *ctx);
void Atualizar_Logo(GameState *estado, int *temporizador);
void Atualizar_Menu(GameState *estado);
void Despausar_Jogo(GameState *estado);
void Mover_Nave(float *velocidade);
void Gira_Nave(float *angulo);
void Atualiza_Nave(int *frame, int *contador, int velocidade);
void Desenha_Texto_Centralizado(const char* texto, int pos_y, int tamanho_fonte, Color cor);
void Escolhe_Menu(int *opcao_selecionada, GameState *estado);
void Escolhe_Menu_Pausa(int *opcao_selecionada, GameState *estado);

#endif