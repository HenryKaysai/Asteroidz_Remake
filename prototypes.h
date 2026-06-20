#ifndef prototypes_h
#define prototypes_h

#include "raylib.h"
#include <math.h>

#define LARGURA_TELA 1200
#define ALTURA_TELA 800
#define MAX_ASTEROIDES 15
#define MAX_TIROS 3
#define TAMANHO_NAVE 64.0f
#define TAMANHO_ASTEROIDE 96.0f

//Definição dos estados do jogo
typedef enum {
    LOGO,
    MENU,
    JOGANDO,
    PAUSE,
    SAVE,
    LOAD_IN_GAME,
    LOAD_OUT_GAME,
    LOAD_SLOT_1,
    LOAD_SLOT_2,
    LOAD_SLOT_3,
    LOAD_SLOT_4,
    LOAD_SLOT_5,
    LOAD_SLOT_6,
    LOAD_SLOT_7,
    LOAD_SLOT_8,
    SAVE_SLOT_1,
    SAVE_SLOT_2,
    SAVE_SLOT_3,
    SAVE_SLOT_4,
    SAVE_SLOT_5,
    SAVE_SLOT_6,
    SAVE_SLOT_7,
    SAVE_SLOT_8,
    BEST_SCORES,
    SAIR
} GameState;

//Definição de um projetil da nave
typedef struct{
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    float angulo;
    bool ativo;
} Projetil;

// estrutura pra nave (jogador)
typedef struct {
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    float angulo;
    int vidas; 
} Nave;

// estrutura pra um asteroide
typedef struct {
    float pos_x; 
    float pos_y; 
    float vel_x; 
    float vel_y; 
    float angulo; 
    float vel_angular;
    bool ativo;
    int tipo; // Qual textura 
} Asteroide;

// Estrutura para os sons do jogo
typedef struct{
    Sound logo_sound;
    Music theme_sound;
    Sound missile_sound;
    int marcador_som_engine;
    float volume_engine;
    Music idle_engine;
    Music engine;
} Som;

//Carregamento das texturas e variáveis utilitárias
typedef struct{
    //texturas
    Texture2D Nave;
    Texture2D Nave_Propulsor;
    Texture2D Asteroid_1;
    Texture2D Asteroid_2;
    Texture2D Asteroid_3;
    Texture2D Pink_Arrow;
    Texture2D Projetil;
    Texture2D Barra_Carregamento;
    Texture2D Estrelas_Maiores;
    Texture2D Nebulosa;
    Texture2D Estrelas_Menores;
    Vector2 pivo_projetil;
    Vector2 pivo_nave;
    Vector2 pivo_seta;
    Vector2 pivo_barra;

    //variáveis
    int temporizador_logo;
    int frame_atual;
    int frames_barra;
    int contador_tempo;
    int velocidade_animacao;
    int velocidade_animacao_seta;
    int opcao_selecionada;
    int contador;
    
    Projetil tiros[MAX_TIROS];
    Nave player;
    Asteroide asteroides[MAX_ASTEROIDES]

} Contextos_Jogo;

typedef struct
{
    float nebulosa_pos_y;
    float nebulosa_pos_x;
    float nebulosa_vel;
    float estrelas_menores_pos_y;
    float estrelas_menores_pos_x;
    float estrelas_menores_vel;
    float estrelas_maiores_pos_y;
    float estrelas_maiores_pos_x;
    float estrelas_maiores_vel;
}Parallax;


////////////////////////////
// PROTOTIPOS DAS FUNCOES //
////////////////////////////

// GERENCIAMENTO DE RECURSOS (Assets)
void Carregar_Texturas(Contextos_Jogo *ctx);
void Descarregar_Texturas(Contextos_Jogo *ctx);
void Carregar_Som(Som *ctx);
void Descarrega_Som(Som *ctx);

// CONTROLE DE ESTADOS DO JOGO
void Atualizar_Logo(GameState *estado, int *temporizador);
void Despausar_Jogo(GameState *estado);
void Sai_Menu(GameState *estado, GameState estado_desejado);

// LÓGICA DE MENUS E NAVEGAÇÃO
void Escolhe_Menu(Music *musica, int *opcao_selecionada, GameState *estado);
void Escolhe_Menu_Pausa(int *opcao_selecionada, GameState *estado);
void Escolhe_Slot(int *opcao_selecionada, GameState *estado, GameState estado_voltar);
void Atualiza_Seta(int *frame, int *contador, int velocidade);

// RENDERIZAÇÃO DE INTERFACE (UI) E TEXTOS
void Desenha_Menu_Principal(int *opcao_selecionada);
void Desenha_Menu_Pausa(int *opcao_selecionada);
void Desenha_Menu_Slots(int *opcao_selecionada, const char* titulo_menu);
void Desenha_Seta_Menu_Principal(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo);
void Desenha_Seta_Menu_Pausa(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo);
void Desenha_Texto_Centralizado(const char* texto, int pos_y, int tamanho_fonte, Color cor);
void Desconta_Tamanho(const char* texto, float pos_x, float pos_y, int tamanho_fonte, Color cor);
void Atualiza_Barra(int temporizador_tiro, int *framerate_barra);
void Desenha_Barra(int *framerate, Vector2 pivo_barra, Texture2D textura_barra);

// LÓGICA DE MOVIMENTO
Aplica_Limites_Circulares(float *pos_x, float *pos_y, float tamanho);

// MECÂNICAS DA NAVE (Player)
void Gira_Nave(float *angulo);
void Acelera_Nave(float *vel_x, float *vel_y, float *pos_x, float *pos_y, float *angulo);
void Atualiza_Nave(int *frame, int *contador, int velocidade);
void Desenha_Nave(int *marcador_som, float *angulo, Texture2D textura_idle, Texture2D textura_propulsao, int *framerate, Vector2 pivo, float *pos_x, float *pos_y);

// SISTEMA DE COMBATE (Tiros e asteroides)
void Atira_Nave(Sound missile_sound, int *temporizador, Projetil tiros[], float pos_x_nave, float pos_y_nave, float angulo_nave);
void Atualiza_Tiro(int *framerate, Projetil tiros[], Texture2D textura_projetil, Vector2 pivo_projetil);
void Atualiza_Asteroides(Contextos_Jogo *ctx);
void Desenha_Asteroides(Contextos_Jogo *ctx);

// CENÁRIO (Parallax) E ÁUDIO DINÂMICO
void Move_Cenario(float *pos_y, float *pos_x, float *vel_x_nave, float *vel_y_nave, float peso_parallax);
void Desenha_Cenario(Texture2D textura, float *pos_x, float *pos_y);
void Som_Motor(Music engine, int *textura_ativa, float *volume);



#endif