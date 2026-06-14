#ifndef prototypes_h
#define prototypes_h

#include "raylib.h"
#include <math.h>

#define LARGURA_TELA 1200
#define ALTURA_TELA 800
#define MAX_TIROS 3



//Definição dos estados do jogo
typedef enum {
    LOGO,
    MENU,
    JOGANDO,
    PAUSE,
    SAVE,
    LOAD_OUT_GAME,
    LOAD_IN_GAME,
    LOAD_1,
    LOAD_2,
    LOAD_3,
    LOAD_4,
    LOAD_5,
    LOAD_6,
    LOAD_7,
    LOAD_8,
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
}Projetil;

// Estrutura para os sons do jogo
typedef struct{
    Sound logo_sound;
    Music theme_sound;
    Sound missile_sound;
    int marcador_som_engine;
    float volume_engine;
    Music idle_engine;
    Music engine;
}Som;

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
    float angulo_nave;
    float pos_x_nave;
    float pos_y_nave;
    float vel_x_nave;
    float vel_y_nave;
    int temporizador_logo;
    int frame_atual;
    int frames_barra;
    int contador_tempo;
    int velocidade_animacao;
    int velocidade_animacao_seta;
    int opcao_selecionada;
    int contador;
    Projetil tiros[MAX_TIROS];

}Contextos_Jogo;

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


// Protótipos das funções
void Desenha_Menu_Principal(int *opcao_selecionada);
void Desenha_Menu_Pausa(int *opcao_selecionada);
void Carregar_Texturas(Contextos_Jogo *ctx);
void Carregar_Som(Som *ctx);
void Descarregar_Texturas(Contextos_Jogo *ctx);
void Descarrega_Som(Som *ctx);
void Atualizar_Logo(GameState *estado, int *temporizador);
void Despausar_Jogo(GameState *estado);
void Mover_Nave(float *velocidade);
void Gira_Nave(float *angulo);
void Atualiza_Nave(int *frame, int *contador, int velocidade);
void Desenha_Texto_Centralizado(const char* texto, int pos_y, int tamanho_fonte, Color cor);
void Escolhe_Menu(Music *musica, int *opcao_selecionada, GameState *estado);
void Escolhe_Menu_Pausa(int *opcao_selecionada, GameState *estado);
void Atualiza_Seta(int *frame, int *contador, int velocidade);
void Desenha_Seta_Menu_Principal(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo);
void Desenha_Seta_Menu_Pausa(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo);
void Acelera_Nave(float *vel_x, float *vel_y, float *pos_x, float *pos_y, float *angulo);
void Anima_Propulsor(int *marcador_som, float *angulo, Texture2D textura_idle, Texture2D textura_propulsao, int *framerate, Vector2 pivo, float *pos_x, float *pos_y);
void Sai_Menu(GameState *estado, GameState estado_desejado);
void Limites_Nave(float *pos_x, float *pos_y);
void Desenha_Load(int *opcao_selecionada);
void Desconta_Tamanho(const char* texto, float pos_x, float pos_y, int tamanho_fonte, Color cor);
void Escolhe_Load_Out_Game(int *opcao_selecionada, GameState *estado);
void Escolhe_Load_In_Game(int *opcao_selecionada, GameState *estado);
void Atira_Nave(Sound missile_sound, int *temporizador, Projetil tiros[], float pos_x_nave, float pos_y_nave, float angulo_nave);
void Atualiza_Tiro(int *framerate, Projetil tiros[], Texture2D textura_projetil, Vector2 pivo_projetil);
void Atualiza_Barra(int temporizador_tiro, int *framerate_barra);
void Desenha_Barra(int *framerate, Vector2 pivo_barra, Texture2D textura_barra);
void Move_Cenario(float *pos_y, float *pos_x, float *vel_x_nave, float *vel_y_nave, float peso_parallax);
void Desenha_Cenario(Texture2D textura, float *pos_x, float *pos_y);
void Som_Motor(Music engine, int *textura_ativa, float *volume);





#endif