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
    DrawText(texto, (LARGURA_TELA / 2) - (largura_texto / 2), pos_y, tamanho_fonte, cor);
}

//Função para a aparência do menu principal
void Desenha_Menu_Principal(int *opcao_selecionada){
    // TÍTULO
    Desenha_Texto_Centralizado("MAIN MENU", ALTURA_TELA / 4, 60, WHITE);

    Color cor_start = ((*opcao_selecionada) == 0) ? PINK : WHITE;
    Color cor_load = ((*opcao_selecionada) == 1) ? PINK : WHITE;
    Color cor_best_scores = ((*opcao_selecionada) == 2) ? PINK : WHITE;
    Color cor_exit = ((*opcao_selecionada) == 3) ? PINK : WHITE;

    int inicio_y = (ALTURA_TELA / 2) + 60;
    // START (0)
    Desenha_Texto_Centralizado("START", inicio_y, 32, cor_start);
    // LOAD (1)
    Desenha_Texto_Centralizado("LOAD", inicio_y + 50, 32, cor_load);
    // BEST SCORES (2)
    Desenha_Texto_Centralizado("BEST SCORES", inicio_y + 100, 32, cor_best_scores);
    // EXIT (3)
    Desenha_Texto_Centralizado("EXIT", inicio_y + 150, 32, cor_exit);
}

//Função para aparência do menu de pausa
void Desenha_Menu_Pausa(int *opcao_selecionada){
    // TÍTULO
    Desenha_Texto_Centralizado("PAUSE", ALTURA_TELA / 4, 60, WHITE);

    Color cor_start = ((*opcao_selecionada) == 0) ? PINK : WHITE;
    Color cor_load = ((*opcao_selecionada) == 1) ? PINK : WHITE;
    Color cor_save = ((*opcao_selecionada) == 2) ? PINK : WHITE;
    Color cor_menu = ((*opcao_selecionada) == 3) ? PINK : WHITE;
    Color cor_exit = ((*opcao_selecionada) == 4) ? PINK : WHITE;


    int inicio_y = (ALTURA_TELA / 2) + 60;
    // START (0)
    Desenha_Texto_Centralizado("RESUME", inicio_y, 32, cor_start);
    // LOAD (1)
    Desenha_Texto_Centralizado("LOAD", inicio_y + 50, 32, cor_load);
    // SAVE (2)
    Desenha_Texto_Centralizado("SAVE", inicio_y + 100, 32, cor_save);
    // MAIN MENU (3)
    Desenha_Texto_Centralizado("MAIN MENU", inicio_y + 150, 32, cor_menu);
    // EXIT (4)
    Desenha_Texto_Centralizado("EXIT", inicio_y + 200, 32, cor_exit);
}

// Função para desenhar a seta do menu em diferentes posições
void Desenha_Seta_Menu_Principal(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo){
    int inicio_y = (ALTURA_TELA / 2) + 60;
    Rectangle seta_hitbox_source = {(*framerate) * 30, 0, 30, 30};
                        
                        
    if ((*opcao_selecionada) == 0){//seta apontando para o start
            Rectangle seta_hitbox_start = {(LARGURA_TELA / 2) - (MeasureText("LOAAD", 32)), inicio_y, 32, 32};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_start, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 1){//seta apontando para o load
            Rectangle seta_hitbox_load = {(LARGURA_TELA / 2) - (MeasureText("LOAD", 32)), inicio_y + 50, 32, 32};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_load, pivo, 0, WHITE);
    }
    else if (*opcao_selecionada == 2){//seta apontando para o best scores
            Rectangle seta_hitbox_best_scores = {(LARGURA_TELA / 2) - (MeasureText("LOADLOAA", 32)), inicio_y + 100, 32, 32};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_best_scores, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 3){//seta apontando para o exit
            Rectangle seta_hitbox_exit = {(LARGURA_TELA / 2) - (MeasureText("EXIT", 32)), inicio_y + 150, 32, 32}  ;  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_exit, pivo, 0, WHITE);
    }
}

// Função para desenhar a seta do menu de pausa em diferentes posições
void Desenha_Seta_Menu_Pausa(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo){
    int inicio_y = (ALTURA_TELA / 2) + 60;
    Rectangle seta_hitbox_source = {(*framerate) * 30, 0, 30, 30};
                        
                        
    if ((*opcao_selecionada) == 0){//seta apontando para o resume
            Rectangle seta_hitbox_resume = {(LARGURA_TELA / 2) - (MeasureText("REUME", 32)), inicio_y, 32, 32};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_resume, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 1){//seta apontando para o load
            Rectangle seta_hitbox_load = {(LARGURA_TELA / 2) - (MeasureText("LOAD", 32)), inicio_y + 50, 32, 32};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_load, pivo, 0, WHITE);
    }
    else if (*opcao_selecionada == 2){//seta apontando para o save
            Rectangle seta_hitbox_save = {(LARGURA_TELA / 2) - (MeasureText("SAVE", 32)), inicio_y + 100, 32, 32};  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_save, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 3){//seta apontando para o main menu
            Rectangle seta_hitbox_main_menu = {(LARGURA_TELA / 2) - (MeasureText("AINAENU", 32)), inicio_y + 150, 32, 32}  ;  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_main_menu, pivo, 0, WHITE);
    }
    else if ((*opcao_selecionada) == 4){//seta apontando para o exit
            Rectangle seta_hitbox_exit = {(LARGURA_TELA / 2) - (MeasureText("EXIT", 32)), inicio_y + 200, 32, 32}  ;  
            DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_exit, pivo, 0, WHITE);
    }
}


//Função para medir texto e evitar usar 2 funções
void Desconta_Tamanho(const char* texto, float pos_x, float pos_y, int tamanho_fonte, Color cor){
    int largura_texto = MeasureText(texto, tamanho_fonte);
    DrawText(texto, pos_x - largura_texto/2, pos_y, tamanho_fonte, cor);
}

//Função para desenhar o menu de pausa
void Desenha_Load(int *opcao_selecionada){
    Color cor_load_1 = ((*opcao_selecionada) == 0) ? PINK : BLACK;
    Color cor_load_2 = ((*opcao_selecionada) == 1) ? PINK : BLACK;
    Color cor_load_3 = ((*opcao_selecionada) == 2) ? PINK : BLACK;
    Color cor_load_4 = ((*opcao_selecionada) == 3) ? PINK : BLACK;
    Color cor_load_5 = ((*opcao_selecionada) == 4) ? PINK : BLACK;
    Color cor_load_6 = ((*opcao_selecionada) == 5) ? PINK : BLACK;
    Color cor_load_7 = ((*opcao_selecionada) == 6) ? PINK : BLACK;
    Color cor_load_8 = ((*opcao_selecionada) == 7) ? PINK : BLACK;
    Color cor_back = ((*opcao_selecionada) == 8) ? PINK : WHITE;
    
    int fonte_slot = 24;

    // LOAD 1 
    DrawRectangle(20, 140, 260, 220, cor_load_1);
    DrawRectangle(30, 150, 240, 200, WHITE);
    Desconta_Tamanho("SLOT 1", 148, 240, fonte_slot, PINK);

    // LOAD 2 
    DrawRectangle(320, 140, 260, 220, cor_load_2);
    DrawRectangle(330, 150, 240, 200, WHITE);
    Desconta_Tamanho("SLOT 2", 448, 240, fonte_slot, PINK);

    // LOAD 3 
    DrawRectangle(620, 140, 260, 220, cor_load_3);
    DrawRectangle(630, 150, 240, 200, WHITE);
    Desconta_Tamanho("SLOT 3", 748, 240, fonte_slot, PINK);

    // LOAD 4 
    DrawRectangle(920, 140, 260, 220, cor_load_4);
    DrawRectangle(930, 150, 240, 200, WHITE);
    Desconta_Tamanho("SLOT 4", 1048, 240, fonte_slot, PINK);

    // LOAD 5 
    DrawRectangle(20, 390, 260, 220, cor_load_5);
    DrawRectangle(30, 400, 240, 200, WHITE);
    Desconta_Tamanho("SLOT 5", 148, 490, fonte_slot, PINK);

    // LOAD 6 
    DrawRectangle(320, 390, 260, 220, cor_load_6);
    DrawRectangle(330, 400, 240, 200, WHITE);
    Desconta_Tamanho("SLOT 6", 448, 490, fonte_slot, PINK);

    // LOAD 7 
    DrawRectangle(620, 390, 260, 220, cor_load_7);
    DrawRectangle(630, 400, 240, 200, WHITE);
    Desconta_Tamanho("SLOT 7", 748, 490, fonte_slot, PINK);

    // LOAD 8 
    DrawRectangle(920, 390, 260, 220, cor_load_8);
    DrawRectangle(930, 400, 240, 200, WHITE);
    Desconta_Tamanho("SLOT 8", 1048, 490, fonte_slot, PINK);

    // BOTÃO VOLTAR
    Desenha_Texto_Centralizado("BACK", 700, 40, cor_back);

}

//////////////////////////////////////////////////
//Funções de funcionalidade de opções de menu
//////////////////////////////////////////////////

// Função para seleção de opções do Menu de Load a partir do menu principal
void Escolhe_Load_Out_Game(int *opcao_selecionada, GameState *estado){
    // hit box para passar o mouse ou selecionar
    Rectangle slot_1_hit_box = {20, 140, 260, 220};
    Rectangle slot_2_hit_box = {320, 140, 260, 220};
    Rectangle slot_3_hit_box = {620, 140, 260, 220};
    Rectangle slot_4_hit_box = {920, 140, 260, 220};
    
    Rectangle slot_5_hit_box = {20, 390, 260, 220};
    Rectangle slot_6_hit_box = {320, 390, 260, 220};
    Rectangle slot_7_hit_box = {620, 390, 260, 220};
    Rectangle slot_8_hit_box = {920, 390, 260, 220};
    
    Rectangle back_hit_box = {0, 700, LARGURA_TELA, 40};

    
    // Teclado
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)){
        (*opcao_selecionada)++;
        if(*opcao_selecionada > 8){
            *opcao_selecionada = 0;
        }
    }
    if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)){
        (*opcao_selecionada)--;
        if(*opcao_selecionada < 0){
            *opcao_selecionada = 8;
        }
    }

    Vector2 mouse_virtual = GetMousePosition();

    // Mouse
    if(CheckCollisionPointRec(mouse_virtual, slot_1_hit_box)){
        *opcao_selecionada = 0;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_2_hit_box)){
        *opcao_selecionada = 1;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_3_hit_box)){
        *opcao_selecionada = 2;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_4_hit_box)){
        *opcao_selecionada = 3;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_5_hit_box)){
        *opcao_selecionada = 4;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_6_hit_box)){
        *opcao_selecionada = 5;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_7_hit_box)){
        *opcao_selecionada = 6;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_8_hit_box)){
        *opcao_selecionada = 7;
    }
    if(CheckCollisionPointRec(mouse_virtual, back_hit_box)){
        *opcao_selecionada = 8;
    }

    // Seleção
    switch(*opcao_selecionada)
    {
        case 0:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_1;
            }
            break;
        case 1:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_2;
            }
            break;

        case 2:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_3;
            }      
            break;

        case 3:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_4;
            }
            break;
        case 4:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_5;
            }
            break;
        case 5:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_6;
            }
            break;
        case 6:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_7;
            }
            break;
        case 7:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_8;
            }
            break; 
        case 8:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = MENU;
            }
            break;        
    }
}

// Função para seleção de opções do Menu de Load a partir do menu principal
void Escolhe_Load_In_Game(int *opcao_selecionada, GameState *estado){
    // hit box para passar o mouse ou selecionar
    Rectangle slot_1_hit_box = {20, 140, 260, 220};
    Rectangle slot_2_hit_box = {320, 140, 260, 220};
    Rectangle slot_3_hit_box = {620, 140, 260, 220};
    Rectangle slot_4_hit_box = {920, 140, 260, 220};
    
    Rectangle slot_5_hit_box = {20, 390, 260, 220};
    Rectangle slot_6_hit_box = {320, 390, 260, 220};
    Rectangle slot_7_hit_box = {620, 390, 260, 220};
    Rectangle slot_8_hit_box = {920, 390, 260, 220};
    
    Rectangle back_hit_box = {0, 700, LARGURA_TELA, 40};

    
    // Teclado
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)){
        (*opcao_selecionada)++;
        if(*opcao_selecionada > 8){
            *opcao_selecionada = 0;
        }
    }
    if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)){
        (*opcao_selecionada)--;
        if(*opcao_selecionada < 0){
            *opcao_selecionada = 8;
        }
    }

    Vector2 mouse_virtual = GetMousePosition();

    // Mouse
    if(CheckCollisionPointRec(mouse_virtual, slot_1_hit_box)){
        *opcao_selecionada = 0;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_2_hit_box)){
        *opcao_selecionada = 1;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_3_hit_box)){
        *opcao_selecionada = 2;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_4_hit_box)){
        *opcao_selecionada = 3;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_5_hit_box)){
        *opcao_selecionada = 4;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_6_hit_box)){
        *opcao_selecionada = 5;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_7_hit_box)){
        *opcao_selecionada = 6;
    }
    if(CheckCollisionPointRec(mouse_virtual, slot_8_hit_box)){
        *opcao_selecionada = 7;
    }
    if(CheckCollisionPointRec(mouse_virtual, back_hit_box)){
        *opcao_selecionada = 8;
    }

    // Seleção
    switch(*opcao_selecionada)
    {
        case 0:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_1;
            }
            break;
        case 1:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_2;
            }
            break;

        case 2:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_3;
            }      
            break;

        case 3:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_4;
            }
            break;
        case 4:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_5;
            }
            break;
        case 5:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_6;
            }
            break;
        case 6:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_7;
            }
            break;
        case 7:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = LOAD_8;
            }
            break; 
        case 8:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = PAUSE;
            }
            break;        
    }
}

// Função para seleção de opções do Menu Principal
void Escolhe_Menu(int *opcao_selecionada, GameState *estado){
    int inicio_y = (ALTURA_TELA / 2) + 60;
    // hit box para passar o mouse ou selecionar
    Rectangle start_hit_box = {0, inicio_y, LARGURA_TELA, 32};
    Rectangle load_hit_box = {0, inicio_y + 50, LARGURA_TELA, 32};
    Rectangle best_scores_hit_box = {0, inicio_y + 100, LARGURA_TELA, 32};
    Rectangle exit_hit_box = {0, inicio_y + 150, LARGURA_TELA, 32};
    
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
    int inicio_y = (ALTURA_TELA / 2) + 60;
    // hit box para passar o mouse ou selecionar
    Rectangle resume_hit_box = {0, inicio_y, LARGURA_TELA, 32};
    Rectangle load_hit_box = {0, inicio_y + 50, LARGURA_TELA, 32};
    Rectangle save_hit_box = {0, inicio_y + 100, LARGURA_TELA, 32};
    Rectangle main_menu_hit_box = {0, inicio_y + 150, LARGURA_TELA, 32};
    Rectangle exit_hit_box = {0, inicio_y + 200, LARGURA_TELA, 32};
    
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
    Rectangle nave_hitbox_dest = {roundf(*pos_x), roundf(*pos_y), 64, 64};

    Texture2D textura_ativa;

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        textura_ativa = textura_propulsao;
    }
    else{
        textura_ativa = textura_idle;
    }
    DrawTexturePro(textura_ativa, nave_hitbox_source, nave_hitbox_dest, pivo, roundf(*angulo), WHITE);

    // EIXO X
    if ((*pos_x) > LARGURA_TELA - 64) {
        Rectangle fantasma_x = {roundf((*pos_x) - LARGURA_TELA), roundf(*pos_y), 64, 64};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_x, pivo, roundf(*angulo), WHITE);
    }
    if ((*pos_x) < 64) {
        Rectangle fantasma_x = {roundf((*pos_x) + LARGURA_TELA), roundf(*pos_y), 64, 64};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_x, pivo, roundf(*angulo), WHITE);
    }

    // EIXO Y 
    if ((*pos_y) > ALTURA_TELA - 64) { 
        Rectangle fantasma_y = {roundf(*pos_x), roundf((*pos_y) - ALTURA_TELA), 64, 64};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_y, pivo, roundf(*angulo), WHITE);
    }
    if ((*pos_y) < 64) { 
        Rectangle fantasma_y = {roundf(*pos_x), roundf((*pos_y) + ALTURA_TELA), 64, 64}; 
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_y, pivo, roundf(*angulo), WHITE);
    }

    // QUINAS DA TELA
    if (((*pos_x) > LARGURA_TELA - 64 || (*pos_x) < 64) && 
        ((*pos_y) > ALTURA_TELA - 64 || (*pos_y) < 64)) {
        
        float quina_x = *pos_x;
        float quina_y = *pos_y;

        if ((*pos_x) > LARGURA_TELA - 64) quina_x -= LARGURA_TELA;
        else if ((*pos_x) < 64) quina_x += LARGURA_TELA;

        if ((*pos_y) > ALTURA_TELA - 64) quina_y -= ALTURA_TELA;
        else if ((*pos_y) < 64) quina_y += ALTURA_TELA;

        Rectangle fantasma_quina = {roundf(quina_x), roundf(quina_y), 64, 64};
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
    float margem = 64.0f;
    
    //EIXO X
    if((*pos_x) > LARGURA_TELA + margem){
        (*pos_x) -= LARGURA_TELA;
    }
    else if((*pos_x) < -margem){
        (*pos_x) += LARGURA_TELA;
    }
    
    // EIXO Y
    if((*pos_y) > ALTURA_TELA + margem){
        (*pos_y) -= ALTURA_TELA;
    }
    else if((*pos_y) < -margem){
        (*pos_y) += ALTURA_TELA;
    }
}