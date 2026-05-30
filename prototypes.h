#ifndef prototypes_h
#define prototypes_h

#include "raylib.h"
#include <math.h>

#define LARGURA_TELA 1200
#define ALTURA_TELA 800

#define ESCALA_VIRTUAL 2
#define LARGURA_VIRTUAL (LARGURA_TELA/ESCALA_VIRTUAL)
#define ALTURA_VIRTUAL (ALTURA_TELA/ESCALA_VIRTUAL)


//Definição dos estados do jogo
typedef enum {
    LOGO,
    MENU,
    JOGANDO,
    PAUSE,
    SAVE,
    LOAD_OUT_GAME,
    LOAD_IN_GAME,
    BEST_SCORES,
    SAIR
} GameState;

//Carregamento das texturas e variáveis utilitárias
typedef struct{
    //texturas
    Texture2D Nave;
    Texture2D Nave_Propulsor;
    Texture2D Asteroid_1;
    Texture2D Asteroid_2;
    Texture2D Asteroid_3;
    Texture2D Pink_Arrow;
    Vector2 pivo_nave;
    Vector2 pivo_seta;

    //variáveis
    float angulo_nave;
    float pos_x_nave;
    float pos_y_nave;
    float vel_x_nave;
    float vel_y_nave;
    int frame_atual;
    int contador_tempo;
    int velocidade_animacao;
    int velocidade_animacao_seta;
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
void Atualiza_Seta(int *frame, int *contador, int velocidade);
void Desenha_Seta_Menu_Principal(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo);
void Desenha_Seta_Menu_Pausa(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo);
void Acelera_Nave(float *vel_x, float *vel_y, float *pos_x, float *pos_y, float *angulo);
void Anima_Propulsor(float *angulo, Texture2D textura_idle, Texture2D textura_propulsao, int *framerate, Vector2 pivo, float *pos_x, float *pos_y);
void Sai_Menu(GameState *estado, GameState estado_desejado);



#endif