/*
 Header file do jogo. Contem:
 - Definicoes de constantes 
 - Estados do jogo em forma de Enum
 - Definicoes de todas structs utilizadas
 - Prototipos de todas funcoes implementadas
*/



#ifndef prototypes_h
#define prototypes_h

#include "raylib.h"
#include <math.h>

#define LARGURA_TELA 1200
#define ALTURA_TELA 800

#define MAX_ASTEROIDES 15
#define MAX_TIROS 3
#define MAX_EXPLOSOES 15
#define MAX_RANKING 5

#define TAMANHO_NAVE 64.0f
#define TAMANHO_ASTEROIDE 96.0f

#define BEST_SCORES_FILENAME "saves/best_scores.bin"

// quantos pontos se ganha por asteroide
#define PONTOS_GANHOS_ASTEROIDE 50
// quantos pontos se perde por morte
#define PONTOS_PERDIDOS_MORTE 200

#define PIVO_NAVE (Vector2){ TAMANHO_NAVE / 2, TAMANHO_NAVE / 2 }
#define PIVO_PROJETIL (Vector2){ 2.0f, 8.0f }
#define PIVO_BARRA (Vector2){ 32.0f, 2.5f }
#define PIVO_SETA (Vector2){ 15.0f, 15.0f }


//Definição dos estados do jogo
typedef enum {
    LOGO,
    MENU,
    JOGANDO,
    PAUSE,
    SAVE,
    LOAD,
    BEST_SCORES,
    GAME_OVER,
    VITORIA,
    SAIR
} GameState;

//Definição de um projetil da nave
typedef struct{
    Vector2 pos;
    Vector2 vel;
    float angulo;
    bool ativo;
} Projetil;

// estrutura pra nave (jogador)
typedef struct {
    Vector2 pos;
    Vector2 vel;
    float angulo;
    int vidas; 
    int tempo_invencivel;
} Nave;

// estrutura pra um asteroide
typedef struct {
    Vector2 pos;
    Vector2 vel;
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
    Sound explosion_sound;
    int marcador_som_engine;
    float volume_engine;
    Music idle_engine;
    Music engine;
    Music menu_sound;
    
} Som;

// struct pra guardar os best scores
typedef struct {
    int pontuacoes[MAX_RANKING];
} Ranking;

typedef struct {
    Vector2 pos;
    bool ativo;
    int frame_atual;
    int contador_tempo; // Para controlar a velocidade da animação
} Explosao;

//Carregamento das texturas e variáveis utilitárias
typedef struct{
    //texturas
    Texture2D Nave;
    Texture2D Nave_Propulsor;
    Texture2D Asteroid_1;
    Texture2D Asteroid_2;
    Texture2D Asteroid_3;
    Texture2D Sprite_Explosao;
    Texture2D Pink_Arrow;
    Texture2D Projetil;
    Texture2D Barra_Carregamento;
    Texture2D Estrelas_Maiores;
    Texture2D Nebulosa;
    Texture2D Estrelas_Menores;
    Texture2D Sprite_GameOver;

    //variáveis
    int temporizador_logo;
    int frame_atual;
    int frames_barra;
    int contador_tempo;
    int velocidade_animacao;
    int velocidade_animacao_seta;
    int opcao_selecionada;
    int contador;
    int fase_atual;
    int pontuacao;
    Vector2 pos_inicial_fase;

    // pra calcular bonus de pontuacao por tempo
    int frames_jogados;
    int asteroides_destruidos;

    // pra lidar com erros de slot vazio
    int timer_erro_load;
    int slot_erro;

    // pra animacao de gameover
    int frame_gameover; 
    int contador_gameover;
    bool gameover_em_loop;

    Ranking ranking;
    Projetil tiros[MAX_TIROS];
    Nave player;
    Asteroide asteroides[MAX_ASTEROIDES];
    Explosao explosoes[MAX_EXPLOSOES];

} Contextos_Jogo;


// struct para representar os dados das saves
typedef struct {
    Nave player;
    Asteroide asteroides[MAX_ASTEROIDES];
    int pontuacao;
    int fase_atual;
    int frames_jogados;
    int asteroides_destruidos;
    // nao vejo necessidade de incluir os tiros 
} SaveData;



typedef struct
{
    Vector2 nebulosa_pos;
    float nebulosa_vel;
    Vector2 estrelas_menores_pos;
    float estrelas_menores_vel;
    Vector2 estrelas_maiores_pos;
    float estrelas_maiores_vel;
} Parallax;



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
bool Sai_Menu(GameState *estado, GameState estado_desejado);

// LÓGICA DE MENUS E NAVEGAÇÃO
int Navega_Menu(int *selecionada, int max_opcoes, float inicio_y, float altura_linha);
void Escolhe_Slot(Contextos_Jogo *ctx, GameState *estado, GameState estado_voltar);
void Atualiza_Seta(int *frame, int *contador, int velocidade);

// RENDERIZAÇÃO DE INTERFACE (UI) E TEXTOS
void Desenha_Menu(const char* titulo, const char* opcoes[], int total_opcoes, int selecionada);
void Desenha_Menu_Slots(int *opcao_selecionada, const char* titulo_menu);
void Desenha_Seta_Menu(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo, const char* textos[], int total_opcoes);
void Desenha_Texto_Centralizado(const char* texto, int pos_y, int tamanho_fonte, Color cor);
void Desconta_Tamanho(const char* texto, Vector2 pos, int tamanho_fonte, Color cor);
void Atualiza_Barra(int temporizador_tiro, int *framerate_barra);
void Desenha_Interface(Contextos_Jogo *ctx);

// LÓGICA DE MOVIMENTO
void Aplica_Limites_Circulares(Vector2 *pos, float tamanho);

// FUNCOES AUXILIARES DE DESENHO
void Desenha_Fantasmas(Texture2D textura, Rectangle source, Vector2 pos, float tamanho, Vector2 pivo, float angulo);

// MECÂNICAS DA NAVE (Player)
void Gira_Nave(float *angulo);
void Acelera_Nave(Vector2 *vel, Vector2 *pos, float *angulo);
void Anima_Nave(int *frame, int *contador, int velocidade);
void Desenha_Nave(Contextos_Jogo *ctx, Som *som);
void Atualiza_Nave(Contextos_Jogo* jogo, Som* som);
void Atira_Nave(Sound missile_sound, int *temporizador, Projetil tiros[], Vector2 pos_nave, float angulo_nave);

// SISTEMA DE COMBATE (Tiros e asteroides)
void Atualiza_Tiro(int *framerate, Projetil tiros[], Texture2D textura_projetil, Vector2 pivo_projetil);
void Atualiza_Asteroides(Contextos_Jogo *ctx);
void Desenha_Asteroides(Contextos_Jogo *ctx);
void Aplica_Limites_Circulares_Asteroides(Contextos_Jogo *ctx, float tamanho);
void Checa_Colisao_Tiro_Asteroide(Contextos_Jogo *ctx, Som *som);

Vector2 Calcula_Posicao_Ponto(Vector2 centro_nave, float angulo, float offset_x, float offset_y);
bool Checa_Colisao_Nave_Asteroide(Contextos_Jogo *ctx);

void Perde_Vida(Contextos_Jogo *ctx, GameState *estado);

// CENÁRIO (Parallax) E ÁUDIO DINÂMICO
void Move_Cenario(Vector2 *pos_parallax, Vector2 *vel_nave, float peso_parallax);
void Desenha_Cenario(Texture2D textura, Vector2 pos);
void Som_Motor(Music engine, int *textura_ativa, float *volume);
void Toca_Musica(Music som);

// FASES
int Carrega_Fase(Contextos_Jogo *ctx, const char *nome_arquivo);
int Checa_Fase_Concluida(Contextos_Jogo *ctx);
void Resetar_Jogo(Contextos_Jogo *ctx);
void Passa_Proxima_Fase(Contextos_Jogo *ctx, GameState *estado);

// SAVE E LOAD
SaveData Prepara_SaveData(Contextos_Jogo *ctx);
int Executa_Save(Contextos_Jogo *ctx, int slot, GameState *estado);

void Carrega_SaveData(Contextos_Jogo *ctx, SaveData data);
int Executa_Load(Contextos_Jogo *ctx, int slot, GameState *estado);

void Erro_Load_Vazia(Contextos_Jogo *ctx, int slot);
void Desenha_Erro_Load_Vazia(int slot_erro);

// RANKING
void Carrega_Ranking(Contextos_Jogo *ctx);
void Salva_Ranking(Contextos_Jogo *ctx);
void Atualiza_Ranking(Contextos_Jogo *ctx);
void Desenha_Best_Scores(Contextos_Jogo *ctx);
void Navega_Best_Scores(Contextos_Jogo *ctx, GameState *estado);

// ANIMACOES EXPLOSOES
void Atualiza_Explosoes(Contextos_Jogo *ctx);
void Desenha_Explosoes(Contextos_Jogo *ctx);

// GAMEOVER
void GameOver(Contextos_Jogo *ctx, GameState *estado);
void Atualiza_Animacao_GameOver(Contextos_Jogo *ctx);
void Desenha_Animacao_GameOver(Contextos_Jogo *ctx);

// VITORIA
void Vitoria(Contextos_Jogo *ctx, GameState *estado);
void Desenha_Tela_Vitoria(Contextos_Jogo *ctx);

#endif