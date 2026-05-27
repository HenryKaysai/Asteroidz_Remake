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
    Desenha_Texto_Centralizado("START", inicio_y, 30, cor_start);
    // LOAD (1)
    Desenha_Texto_Centralizado("LOAD", inicio_y + 50, 30, cor_load);
    // BEST SCORES (2)
    Desenha_Texto_Centralizado("BEST SCORES", inicio_y + 100, 30, cor_best_scores);
    // EXIT (3)
    Desenha_Texto_Centralizado("EXIT", inicio_y + 150, 30, cor_exit);
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
    Desenha_Texto_Centralizado("RESUME", inicio_y, 30, cor_start);
    // LOAD (1)
    Desenha_Texto_Centralizado("LOAD", inicio_y + 50, 30, cor_load);
    // SAVE (2)
    Desenha_Texto_Centralizado("SAVE", inicio_y + 100, 30, cor_save);
    // MAIN MENU (3)
    Desenha_Texto_Centralizado("MAIN MENU", inicio_y + 150, 30, cor_menu);
    // EXIT (4)
    Desenha_Texto_Centralizado("EXIT", inicio_y + 200, 30, cor_exit);
}

//////////////////////////////////////////////////
//Funções de funcionalidade de opções de menu
//////////////////////////////////////////////////

// Função para seleção de opções do Menu Principal
void Escolhe_Menu(int *opcao_selecionada, GameState *estado){
    int inicio_y = (ALTURA_TELA / 2) + 60;
    // hit box para passar o mouse ou selecionar
    Rectangle start_hit_box = {0, inicio_y, LARGURA_TELA, 30};
    Rectangle load_hit_box = {0, inicio_y + 50, LARGURA_TELA, 30};
    Rectangle best_scores_hit_box = {0, inicio_y + 100, LARGURA_TELA, 30};
    Rectangle exit_hit_box = {0, inicio_y + 150, LARGURA_TELA, 30};
    
    // Teclado
    if(IsKeyPressed(KEY_DOWN)){
        (*opcao_selecionada)++;
        if(*opcao_selecionada > 3){
            *opcao_selecionada = 0;
        }
    }
    if(IsKeyPressed(KEY_UP)){
        (*opcao_selecionada)--;
        if(*opcao_selecionada < 0){
            *opcao_selecionada = 3;
        }
    }
    // Mouse
    if(CheckCollisionPointRec(GetMousePosition(), start_hit_box)){
        *opcao_selecionada = 0;//start
    }
    if(CheckCollisionPointRec(GetMousePosition(), load_hit_box)){
        *opcao_selecionada = 1;//load
    }
    if(CheckCollisionPointRec(GetMousePosition(), best_scores_hit_box)){
        *opcao_selecionada = 2;//best scores
    }
    if(CheckCollisionPointRec(GetMousePosition(), exit_hit_box)){
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
                *estado = LOAD;
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
    }
}

// Função para seleção de opções do menu de pausa
void Escolhe_Menu_Pausa(int *opcao_selecionada, GameState *estado){
    int inicio_y = (ALTURA_TELA / 2) + 60;
    // hit box para passar o mouse ou selecionar
    Rectangle resume_hit_box = {0, inicio_y, LARGURA_TELA, 30};
    Rectangle load_hit_box = {0, inicio_y + 50, LARGURA_TELA, 30};
    Rectangle save_hit_box = {0, inicio_y + 100, LARGURA_TELA, 30};
    Rectangle main_menu_hit_box = {0, inicio_y + 150, LARGURA_TELA, 30};
    Rectangle exit_hit_box = {0, inicio_y + 200, LARGURA_TELA, 30};
    
    // Teclado
    if(IsKeyPressed(KEY_DOWN)){
        (*opcao_selecionada)++;
        if(*opcao_selecionada > 4){
            *opcao_selecionada = 0;
        }
    }
    if(IsKeyPressed(KEY_UP)){
        (*opcao_selecionada)--;
        if(*opcao_selecionada < 0){
            *opcao_selecionada = 4;
        }
    }
    // Mouse
    if(CheckCollisionPointRec(GetMousePosition(), resume_hit_box)){
        *opcao_selecionada = 0;//resume
    }
    if(CheckCollisionPointRec(GetMousePosition(), load_hit_box)){
        *opcao_selecionada = 1;//load
    }
    if(CheckCollisionPointRec(GetMousePosition(), save_hit_box)){
        *opcao_selecionada = 2;//save
    }
    if(CheckCollisionPointRec(GetMousePosition(), main_menu_hit_box)){
        *opcao_selecionada = 3;//main menu
    }
    if(CheckCollisionPointRec(GetMousePosition(), exit_hit_box)){
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
                *estado = LOAD;
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
            break;
            }
        case 4:
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                *estado = SAIR;
            }
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