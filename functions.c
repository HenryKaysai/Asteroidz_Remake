#include "raylib.h"
#include "prototypes.h"

//////////////////////////////////////////////////
//Funções dos estados do jogo
//////////////////////////////////////////////////

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

//////////////////////////////////////////////////
//Funções de "aparência"
//////////////////////////////////////////////////

// Função para desenhar texto sempre centralizado
void Desenha_Texto_Centralizado(const char* texto, int pos_y, int tamanho_fonte, Color cor) {
    int largura_texto = MeasureText(texto, tamanho_fonte);
    DrawText(texto, (LARGURA_TELA / 2) - (largura_texto / 2), pos_y, tamanho_fonte, cor);
}

void Desenha_Menu_Principal(void){
    // TÍTULO
    Desenha_Texto_Centralizado("MAIN MENU", ALTURA_TELA / 4, 60, WHITE);

    int inicio_y = (ALTURA_TELA / 2) + 60;
    // START
    Desenha_Texto_Centralizado("START", inicio_y, 30, WHITE);
    // LOAD
    Desenha_Texto_Centralizado("LOAD", inicio_y + 50, 30, WHITE);
    // BEST SCORES
    Desenha_Texto_Centralizado("BEST SCORES", inicio_y + 100, 30, WHITE);
    // EXIT
    Desenha_Texto_Centralizado("START", inicio_y + 150, 30, WHITE);
}

void Desenha_Menu_Pausa(void){
    // TÍTULO
    Desenha_Texto_Centralizado("PAUSE", ALTURA_TELA / 4, 60, WHITE);

    int inicio_y = (ALTURA_TELA / 2) + 60;
    // START
    Desenha_Texto_Centralizado("RESUME", inicio_y, 30, WHITE);
    // LOAD
    Desenha_Texto_Centralizado("LOAD", inicio_y + 50, 30, WHITE);
    // SAVE
    Desenha_Texto_Centralizado("SAVE", inicio_y + 100, 30, WHITE);
    // EXIT
    Desenha_Texto_Centralizado("EXIT", inicio_y + 150, 30, WHITE);
}







//////////////////////////////////////////////////
//Funções da nave
//////////////////////////////////////////////////


//Função para atualizar a animação da nave
void Atualiza_Nave(int *frame, int *contador, int velocidade){
    (*contador)++;
    if(*contador >= velocidade){
        (*frame)++;
        (*contador) = 0;
    }
    if(*frame == 4){
        (*frame) = 0;
    }
}

//Função para rotacionar a nave
void Gira_Nave(float *angulo){
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        *angulo += 5.0f;
    }
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        *angulo -= 5.0f;
    }
}

//Define uma função que vai ativar a turbina da nave
void Mover_Nave(float *velocidade){
    if (IsKeyPressed(KEY_SPACE)){
        *velocidade += 1;
    }
}