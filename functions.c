#include "raylib.h"
#include "prototypes.h"
#include <math.h>

//////////////////////////////////////////////////
//Funções dos estados do jogo
//////////////////////////////////////////////////
//Função para voltar de menus
void Sai_Menu(GameState *estado, GameState estado_desejado){
    if(IsKeyPressed(KEY_ESCAPE)){
        (*estado) = estado_desejado;
    }
}

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
void Despausar_Jogo(GameState *estado){
    if(IsKeyPressed(KEY_ESCAPE)){
        *estado = JOGANDO;
        HideCursor(); 
        DisableCursor();
    }
}

//////////////////////////////////////////////////
//Funções de aparência
//////////////////////////////////////////////////

// Função para desenhar texto sempre centralizado
void Desenha_Texto_Centralizado(const char* texto, int pos_y, int tamanho_fonte, Color cor) {
    int largura_texto = MeasureText(texto, tamanho_fonte);
    DrawText(texto, (LARGURA_VIRTUAL / 2) - (largura_texto / 2), pos_y, tamanho_fonte, cor);
}

//Função para a aparência do menu principal
void Desenha_Menu_Principal(int *opcao_selecionada){
    // TÍTULO
    Desenha_Texto_Centralizado("MAIN MENU", ALTURA_VIRTUAL / 4, 30, WHITE);

    Color cor_start = ((*opcao_selecionada) == 0) ? PINK : WHITE;
    Color cor_load = ((*opcao_selecionada) == 1) ? PINK : WHITE;
    Color cor_best_scores = ((*opcao_selecionada) == 2) ? PINK : WHITE;
    Color cor_exit = ((*opcao_selecionada) == 3) ? PINK : WHITE;

    int inicio_y = (ALTURA_VIRTUAL / 2) + 40;
    // START (0)
    Desenha_Texto_Centralizado("START", inicio_y, 16, cor_start);
    // LOAD (1)
    Desenha_Texto_Centralizado("LOAD", inicio_y + 24, 16, cor_load);
    // BEST SCORES (2)
    Desenha_Texto_Centralizado("BEST SCORES", inicio_y + 50, 16, cor_best_scores);
    // EXIT (3)
    Desenha_Texto_Centralizado("EXIT", inicio_y + 74, 16, cor_exit);
}

//Função para aparência do menu de pausa
void Desenha_Menu_Pausa(int *opcao_selecionada){
    // TÍTULO
    Desenha_Texto_Centralizado("PAUSE", ALTURA_VIRTUAL / 4, 30, WHITE);

    Color cor_start = ((*opcao_selecionada) == 0) ? PINK : WHITE;
    Color cor_load = ((*opcao_selecionada) == 1) ? PINK : WHITE;
    Color cor_save = ((*opcao_selecionada) == 2) ? PINK : WHITE;
    Color cor_menu = ((*opcao_selecionada) == 3) ? PINK : WHITE;
    Color cor_exit = ((*opcao_selecionada) == 4) ? PINK : WHITE;


    int inicio_y = (ALTURA_VIRTUAL / 2) + 40;
    // START (0)
    Desenha_Texto_Centralizado("RESUME", inicio_y, 16, cor_start);
    // LOAD (1)
    Desenha_Texto_Centralizado("LOAD", inicio_y + 24, 16, cor_load);
    // SAVE (2)
    Desenha_Texto_Centralizado("SAVE", inicio_y + 50, 16, cor_save);
    // MAIN MENU (3)
    Desenha_Texto_Centralizado("MAIN MENU", inicio_y + 74, 16, cor_menu);
    // EXIT (4)
    Desenha_Texto_Centralizado("EXIT", inicio_y + 100, 16, cor_exit);
}

// Função para desenhar a seta do menu em diferentes posições
void Desenha_Seta_Menu_Principal(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo){
    int inicio_y = (ALTURA_VIRTUAL / 2) + 40;
    Rectangle seta_hitbox_source = {(*framerate) * 30, 0, 30, 30};
                        
                        
    if ((*opcao_selecionada) == 0){//seta apontando para o start
            Rectangle seta_hitbox_start = {(LARGURA_VIRTUAL / 2) - (MeasureText("LOAAD", 16)), inicio_y, 16, 16};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_start, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 1){//seta apontando para o load
            Rectangle seta_hitbox_load = {(LARGURA_VIRTUAL / 2) - (MeasureText("LOAD", 16)), inicio_y + 24, 16, 16};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_load, pivo, 0, WHITE);
    }
    else if (*opcao_selecionada == 2){//seta apontando para o best scores
            Rectangle seta_hitbox_best_scores = {(LARGURA_VIRTUAL / 2) - (MeasureText("LOADLOAA", 16)), inicio_y + 50, 16, 16};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_best_scores, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 3){//seta apontando para o exit
            Rectangle seta_hitbox_exit = {(LARGURA_VIRTUAL / 2) - (MeasureText("EXIT", 16)), inicio_y + 74, 16, 16}  ;  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_exit, pivo, 0, WHITE);
    }
}

// Função para desenhar a seta do menu de pausa em diferentes posições
void Desenha_Seta_Menu_Pausa(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo){
    int inicio_y = (ALTURA_VIRTUAL / 2) + 40;
    Rectangle seta_hitbox_source = {(*framerate) * 30, 0, 30, 30};
                        
                        
    if ((*opcao_selecionada) == 0){//seta apontando para o resume
            Rectangle seta_hitbox_resume = {(LARGURA_VIRTUAL / 2) - (MeasureText("REUME", 16)), inicio_y, 16, 16};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_resume, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 1){//seta apontando para o load
            Rectangle seta_hitbox_load = {(LARGURA_VIRTUAL / 2) - (MeasureText("LOAD", 16)), inicio_y + 24, 16, 16};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_load, pivo, 0, WHITE);
    }
    else if (*opcao_selecionada == 2){//seta apontando para o save
            Rectangle seta_hitbox_save = {(LARGURA_VIRTUAL / 2) - (MeasureText("SAVE", 16)), inicio_y + 50, 16, 16};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_save, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 3){//seta apontando para o main menu
            Rectangle seta_hitbox_main_menu = {(LARGURA_VIRTUAL / 2) - (MeasureText("AINAENU", 16)), inicio_y + 74, 16, 16}  ;  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_main_menu, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 4){//seta apontando para o exit
            Rectangle seta_hitbox_exit = {(LARGURA_VIRTUAL / 2) - (MeasureText("EXIT", 16)), inicio_y + 100, 16, 16}  ;  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_exit, pivo, 0, WHITE);
    }
}

//Função para desenhar o menu de pausa
void Desenha_Load(void){


    DrawRectangle(20, 100, 150, 100, WHITE);
    DrawRectangle(ALTURA_VIRTUAL/2, 100, 150, 100, WHITE);
    DrawRectangle(ALTURA_VIRTUAL/2 + 20, 100, 150, 100, WHITE);

}

//////////////////////////////////////////////////
//Funções de funcionalidade de opções de menu
//////////////////////////////////////////////////

// Função para seleção de opções do Menu Principal
void Escolhe_Menu(int *opcao_selecionada, GameState *estado){
    int inicio_y = (ALTURA_VIRTUAL / 2) + 40;
    // hit box para passar o mouse ou selecionar
    Rectangle start_hit_box = {0, inicio_y, LARGURA_VIRTUAL, 24};
    Rectangle load_hit_box = {0, inicio_y + 24, LARGURA_VIRTUAL, 24};
    Rectangle best_scores_hit_box = {0, inicio_y + 50, LARGURA_VIRTUAL, 24};
    Rectangle exit_hit_box = {0, inicio_y + 74, LARGURA_VIRTUAL, 24};
    
    // Teclado
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        (*opcao_selecionada)++;
        if(*opcao_selecionada > 3){
            *opcao_selecionada = 0;
        }
    }
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        (*opcao_selecionada)--;
        if(*opcao_selecionada < 0){
            *opcao_selecionada = 3;
        }
    }

    Vector2 mouse_virtual = GetMousePosition();
    mouse_virtual.x /= ESCALA_VIRTUAL;
    mouse_virtual.y /= ESCALA_VIRTUAL;

    // Mouse
    if(CheckCollisionPointRec(mouse_virtual, start_hit_box)){
        *opcao_selecionada = 0;//start
    }
    if(CheckCollisionPointRec(mouse_virtual, load_hit_box)){
        *opcao_selecionada = 1;//load
    }
    if(CheckCollisionPointRec(mouse_virtual, best_scores_hit_box)){
        *opcao_selecionada = 2;//best scores
    }
    if(CheckCollisionPointRec(mouse_virtual, exit_hit_box)){
        *opcao_selecionada = 3;//exit
    }

    // Seleção
    switch(*opcao_selecionada)
    {
        case 0:

            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = JOGANDO;
            }
            break;
        case 1:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_OUT_GAME;
            }
            break;

        case 2:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = BEST_SCORES;
            }      
            break;

        case 3:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = SAIR;
            }
            break;
    }
}

// Função para seleção de opções do menu de pausa
void Escolhe_Menu_Pausa(int *opcao_selecionada, GameState *estado){
    int inicio_y = (ALTURA_VIRTUAL / 2) + 40;
    // hit box para passar o mouse ou selecionar
    Rectangle resume_hit_box = {0, inicio_y, LARGURA_VIRTUAL, 24};
    Rectangle load_hit_box = {0, inicio_y + 24, LARGURA_VIRTUAL, 24};
    Rectangle save_hit_box = {0, inicio_y + 50, LARGURA_VIRTUAL, 24};
    Rectangle main_menu_hit_box = {0, inicio_y + 74, LARGURA_VIRTUAL, 24};
    Rectangle exit_hit_box = {0, inicio_y + 100, LARGURA_VIRTUAL, 24};
    
    // Teclado
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        (*opcao_selecionada)++;
        if(*opcao_selecionada > 4){
            *opcao_selecionada = 0;
        }
    }
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        (*opcao_selecionada)--;
        if(*opcao_selecionada < 0){
            *opcao_selecionada = 4;
        }
    }

    Vector2 mouse_virtual = GetMousePosition();
    mouse_virtual.x /= ESCALA_VIRTUAL;
    mouse_virtual.y /= ESCALA_VIRTUAL;

    // Mouse
    if(CheckCollisionPointRec(mouse_virtual, resume_hit_box)){
        *opcao_selecionada = 0;//resume
    }
    if(CheckCollisionPointRec(mouse_virtual, load_hit_box)){
        *opcao_selecionada = 1;//load
    }
    if(CheckCollisionPointRec(mouse_virtual, save_hit_box)){
        *opcao_selecionada = 2;//save
    }
    if(CheckCollisionPointRec(mouse_virtual, main_menu_hit_box)){
        *opcao_selecionada = 3;//main menu
    }
    if(CheckCollisionPointRec(mouse_virtual, exit_hit_box)){
        *opcao_selecionada = 4;//exit
    }

    // Seleção
    switch(*opcao_selecionada)
    {
        case 0:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = JOGANDO;
            }
            break;
        case 1:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_IN_GAME;
            }
            break;

        case 2:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = SAVE;
            }      
            break;

        case 3:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = MENU;
            
            }
            break;
        case 4:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = SAIR;
            }
            break;
    }
}

//Função para atualizar a animação da seta do menu principal
void Atualiza_Seta(int *frame, int *contador, int velocidade){
    (*contador)++;
    if(*contador >= velocidade){
        (*frame)++;
        (*contador) = 0;
    }
    if(*frame == 8){
        (*frame) = 0;
    }
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

// Função para animar o propulsor da nave e desenhar a nave
void Anima_Propulsor(float *angulo, Texture2D textura_idle, Texture2D textura_propulsao, int *framerate, Vector2 pivo, float *pos_x, float *pos_y){
    Rectangle nave_hitbox_source = {*framerate * 64, 0 ,64, 64};
    Rectangle nave_hitbox_dest = {roundf(*pos_x), roundf(*pos_y), 32, 32};

    Texture2D textura_ativa;

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        textura_ativa = textura_propulsao;
    }
    else{
        textura_ativa = textura_idle;
    }
    DrawTexturePro(textura_ativa, nave_hitbox_source, nave_hitbox_dest, pivo, roundf(*angulo), WHITE);

    // EIXO X
    if ((*pos_x) > LARGURA_VIRTUAL - 32) {
        Rectangle fantasma_x = {roundf((*pos_x) - LARGURA_VIRTUAL), roundf(*pos_y), 32, 32};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_x, pivo, roundf(*angulo), WHITE);
    }
    if ((*pos_x) < 32) {
        Rectangle fantasma_x = {roundf((*pos_x) + LARGURA_VIRTUAL), roundf(*pos_y), 32, 32};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_x, pivo, roundf(*angulo), WHITE);
    }

    // EIXO Y 
    if ((*pos_y) > ALTURA_VIRTUAL - 32) { 
        Rectangle fantasma_y = {roundf(*pos_x), roundf((*pos_y) - ALTURA_VIRTUAL), 32, 32};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_y, pivo, roundf(*angulo), WHITE);
    }
    if ((*pos_y) < 32) { 
        Rectangle fantasma_y = {roundf(*pos_x), roundf((*pos_y) + ALTURA_VIRTUAL), 32, 32}; 
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_y, pivo, roundf(*angulo), WHITE);
    }

    // QUINAS DA TELA
    if (((*pos_x) > LARGURA_VIRTUAL - 32 || (*pos_x) < 32) && 
        ((*pos_y) > ALTURA_VIRTUAL - 32 || (*pos_y) < 32)) {
        
        float quina_x = *pos_x;
        float quina_y = *pos_y;

        if ((*pos_x) > LARGURA_VIRTUAL - 32) quina_x -= LARGURA_VIRTUAL;
        else if ((*pos_x) < 32) quina_x += LARGURA_VIRTUAL;

        if ((*pos_y) > ALTURA_VIRTUAL - 32) quina_y -= ALTURA_VIRTUAL;
        else if ((*pos_y) < 32) quina_y += ALTURA_VIRTUAL;

        Rectangle fantasma_quina = {roundf(quina_x), roundf(quina_y), 32, 32};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_quina, pivo, roundf(*angulo), WHITE);
    }
}


//Função para rotacionar a nave
void Gira_Nave(float *angulo){
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) *angulo += 3.0f;
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) *angulo -= 3.0f;
    
    // Normaliza para manter entre 0 e 360
    if (*angulo >= 360.0f) *angulo = 0.0f;
    if (*angulo < 0.0f) *angulo = 360.0f;
}


// Função para acelerar os propulsores da nave
void Acelera_Nave(float *vel_x, float *vel_y, float *pos_x, float *pos_y, float *angulo){
float velocidade = 0.1f; 
float angulo_ajustado = (*angulo) - 90.0f;//o sprite começa apontado para cima
float angulo_radianos = angulo_ajustado * (PI / 180.0f);//math.h opera em radianos
float move_x = cosf(angulo_radianos) * velocidade;
float move_y = sinf(angulo_radianos) * velocidade;
// o angulo do jogo acumula infinitamente então o cos e sen geram valores entre -1 e 1

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){//acelera a posição do sprite na direção do bico da nave
        ((*vel_x) += move_x);
        ((*vel_y) += move_y);
    }
    (*vel_x) *= 0.99f; //inércia 
    (*vel_y) *= 0.99f;  // desacelera 1% a cada frame então...\/

    if((*vel_x) > -0.01f && (*vel_x) < 0.01f) *vel_x = 0.0f;//isso é o que efetivamente
    if((*vel_y) > -0.01f && (*vel_y) < 0.01f) *vel_y = 0.0f;//para a nave

    (*pos_x) += (*vel_x);//move a nave de fato
    (*pos_y) += (*vel_y);
}

// Função para fazer a nave sair de um lado para o outro
void Limites_Nave(float *pos_x, float *pos_y){
    float margem = 32.0f;
    
    if((*pos_x) > LARGURA_VIRTUAL + margem){
        (*pos_x) = -margem;
    }
    else if((*pos_x) < -margem){
        (*pos_x) = LARGURA_VIRTUAL + margem;
    }
    if((*pos_y) > ALTURA_VIRTUAL + margem){
        (*pos_y) = -margem;
    }
    else if((*pos_y) < -margem){
        (*pos_y) = ALTURA_VIRTUAL + margem;
    }
}