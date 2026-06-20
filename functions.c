#include "raylib.h"
#include "prototypes.h"
#include <math.h>
#include <stdio.h>

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
    if ((*temporizador) > 300) { //Quando se passarem 3 segundos, o jogo sai do logo e vai para o menu (60FPS * 3)
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
void Desenha_Menu_Slots(int *opcao_selecionada, const char* titulo_menu){
    // Funcao generica para desenhar os slots nos menus de Save e de Load

    Desenha_Texto_Centralizado(titulo_menu, 60, 60, WHITE);

    int fonte_slot = 24;

    // Gera 8 retângulos denominados LOAD 1, LOAD 2... LOAD 8 
    // representando diferentes slots que podem ser selecionados
    for (int i = 0; i < 8; i++) {
        // Se a opção selecionada for igual a i, pinta de rosa, senao, de preto
        Color cor_borda = ((*opcao_selecionada) == i) ? PINK : BLACK;
        
        // divide por 4 para saber a linha (0 ou 1)
        int linha = i / 4; 
        // pega o resto da divisão por 4 para saber a coluna 
        int coluna = i % 4; 

        // calcula as coordenadas baseado na linha e coluna
        int pos_x = 20 + (coluna * 300);
        int pos_y = 140 + (linha * 250);

        DrawRectangle(pos_x, pos_y, 260, 220, cor_borda);
        DrawRectangle(pos_x + 10, pos_y + 10, 240, 200, WHITE);

        // Cria o texto "SLOT X"
        char texto_slot[10];
        sprintf(texto_slot, "SLOT %d", i + 1); 
        Desconta_Tamanho(texto_slot, pos_x + 130, pos_y + 90, fonte_slot, PINK);
    }

    // BOTA VOLTAR (opcao 8)
    Color cor_back = ((*opcao_selecionada) == 8) ? PINK : WHITE;
    Desenha_Texto_Centralizado("BACK", 700, 40, cor_back);

}



//////////////////////////////////////////////////
//Funções de funcionalidade de opções de menu
//////////////////////////////////////////////////

void Escolhe_Slot(int *opcao_selecionada,   
                    GameState *estado,      // Estado atual - pode ser load ou save
                    GameState estado_voltar // Estado desejado ao voltar 
                    ){ 
    // Funcao generica que serve tanto para o estado de Load_In_Game, Load_Out_Game e Save

    // Pra facilitar o uso das teclas up e down pra navegar entre slots
    int mapa_cima[9]  =    {8, 8, 8, 8, 0, 1, 2, 3, 4};
    int mapa_baixo[9] =    {4, 5, 6, 7, 8, 8, 8, 8, 0};

    int primeiro_slot;
    // Muda a variavel primeiro_slot para servir tanto para load quanto para save
    if (*estado == SAVE) primeiro_slot = SAVE_SLOT_1;
    else if ((*estado==LOAD_IN_GAME) || (*estado==LOAD_OUT_GAME)) {
        primeiro_slot = LOAD_SLOT_1;
    }            
    // Atualiza opcao_selecionada baseada no teclado
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)){
        (*opcao_selecionada)++;
        if(*opcao_selecionada > 8) *opcao_selecionada = 0;
    }
    else if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)){
        (*opcao_selecionada)--;
        if(*opcao_selecionada < 0) *opcao_selecionada = 8;
    }
    else if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        *opcao_selecionada = mapa_cima[*opcao_selecionada];
    }
    else if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        *opcao_selecionada = mapa_baixo[*opcao_selecionada];
    }
    
    Vector2 mouse_virtual = GetMousePosition();

    // Atualiza opcao_selecionada se o mouse tiver dentro dos hitbox dos slots
    for (int i = 0; i < 8; i++) {
        int linha = i / 4;
        int coluna = i % 4;
        Rectangle slot_hit_box = {20 + (coluna * 300), 140 + (linha * 250), 260, 220};
        
        if(CheckCollisionPointRec(mouse_virtual, slot_hit_box)) {
            *opcao_selecionada = i;
        }
    }

    // Atualiza opcao_selecionada se mouse estiver no hitbox do voltar
    Rectangle back_hit_box = {0, 700, LARGURA_TELA, 40};
    if(CheckCollisionPointRec(mouse_virtual, back_hit_box)){
        *opcao_selecionada = 8;
    }
    
    // Efetua a selecao atualizando o estado com base na opcao_selecionada
    if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if (*opcao_selecionada >= 0 && *opcao_selecionada <= 7) {

            // primeiro_slot -> LOAD_SLOT_1, LOAD_SLOT_2, ... LOAD_SLOT_8 sao enums,
            // logo podem ser tratados como int
            *estado = primeiro_slot + *opcao_selecionada; 
        } 
        else if (*opcao_selecionada == 8) {
            *estado = estado_voltar; 
        }
    }
}
                    


// Função para seleção de opções do Menu Principal
void Escolhe_Menu(Music *musica, int *opcao_selecionada, GameState *estado){
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
                StopMusicStream(*musica);
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
//Funções auxiliares de movimento (lógica)
//////////////////////////////////////////////////

// Função para fazer a nave sair de um lado para o outro
void Aplica_Limites_Circulares(float *pos_x, float *pos_y, float tamanho){

    //EIXO X
    if((*pos_x) > LARGURA_TELA + tamanho){
        (*pos_x) -= LARGURA_TELA;
    }
    else if((*pos_x) < -tamanho){
        (*pos_x) += LARGURA_TELA;
    }
    
    // EIXO Y
    if((*pos_y) > ALTURA_TELA + tamanho){
        (*pos_y) -= ALTURA_TELA;
    }
    else if((*pos_y) < -tamanho){
        (*pos_y) += ALTURA_TELA;
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

// Função para tocar o som do motor
void Som_Motor(Music engine, int *textura_ativa, float *volume){
    // acelerar
    if ((*textura_ativa) == 1) {     
        if (!IsMusicStreamPlaying(engine)) {
            PlayMusicStream(engine);
        }
        // Fade in
        if ((*volume) < 0.2f) {
            (*volume) += 0.1f; 
        }
        SetMusicVolume(engine, *volume);
        UpdateMusicStream(engine);
    }
    // fade out
    else {   
        if (IsMusicStreamPlaying(engine)) {
            (*volume) -= 0.01f;

            if ((*volume) <= 0.0f) {
                (*volume) = 0.0f;
                StopMusicStream(engine);
            } 
            else {
                // Se ainda tem volume, atualiza o nível e continua rodando a fita
                SetMusicVolume(engine, *volume);
                UpdateMusicStream(engine); 
            }
        }
    }
}



// Função para animar o propulsor da nave e desenhar a nave
void Desenha_Nave(int *marcador_som, float *angulo, Texture2D textura_idle, Texture2D textura_propulsao, int *framerate, Vector2 pivo, float *pos_x, float *pos_y){
    Rectangle nave_hitbox_source = {*framerate * TAMANHO_NAVE, 0 ,TAMANHO_NAVE, TAMANHO_NAVE};
    Rectangle nave_hitbox_dest = {roundf(*pos_x), roundf(*pos_y), TAMANHO_NAVE, TAMANHO_NAVE};

    Texture2D textura_ativa;

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        textura_ativa = textura_propulsao;
        (*marcador_som) = 1;
    }
    else{
        (*marcador_som) = 0;
        textura_ativa = textura_idle;
    }
    DrawTexturePro(textura_ativa, nave_hitbox_source, nave_hitbox_dest, pivo, roundf(*angulo), WHITE);

    // EIXO X
    if ((*pos_x) > LARGURA_TELA - TAMANHO_NAVE) {
        Rectangle fantasma_x = {roundf((*pos_x) - LARGURA_TELA), roundf(*pos_y), TAMANHO_NAVE, TAMANHO_NAVE};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_x, pivo, roundf(*angulo), WHITE);
    }
    if ((*pos_x) < TAMANHO_NAVE) {
        Rectangle fantasma_x = {roundf((*pos_x) + LARGURA_TELA), roundf(*pos_y), TAMANHO_NAVE, TAMANHO_NAVE};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_x, pivo, roundf(*angulo), WHITE);
    }

    // EIXO Y 
    if ((*pos_y) > ALTURA_TELA - TAMANHO_NAVE) { 
        Rectangle fantasma_y = {roundf(*pos_x), roundf((*pos_y) - ALTURA_TELA), TAMANHO_NAVE, TAMANHO_NAVE};
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_y, pivo, roundf(*angulo), WHITE);
    }
    if ((*pos_y) < TAMANHO_NAVE) { 
        Rectangle fantasma_y = {roundf(*pos_x), roundf((*pos_y) + ALTURA_TELA), TAMANHO_NAVE, TAMANHO_NAVE}; 
        DrawTexturePro(textura_ativa, nave_hitbox_source, fantasma_y, pivo, roundf(*angulo), WHITE);
    }

    // QUINAS DA TELA
    if (((*pos_x) > LARGURA_TELA - TAMANHO_NAVE || (*pos_x) < TAMANHO_NAVE) && 
        ((*pos_y) > ALTURA_TELA - TAMANHO_NAVE || (*pos_y) < TAMANHO_NAVE)) {
        
        float quina_x = *pos_x;
        float quina_y = *pos_y;

        if ((*pos_x) > LARGURA_TELA - TAMANHO_NAVE) quina_x -= LARGURA_TELA;
        else if ((*pos_x) < TAMANHO_NAVE) quina_x += LARGURA_TELA;

        if ((*pos_y) > ALTURA_TELA - TAMANHO_NAVE) quina_y -= ALTURA_TELA;
        else if ((*pos_y) < TAMANHO_NAVE) quina_y += ALTURA_TELA;

        Rectangle fantasma_quina = {roundf(quina_x), roundf(quina_y), TAMANHO_NAVE, TAMANHO_NAVE};
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
    float aceleracao = 0.1f; 
    float angulo_ajustado = (*angulo) - 90.0f; //pro sprite começar apontado para cima
    float angulo_radianos = angulo_ajustado * (PI / 180.0f);//math.h opera em radianos
    float move_x = cosf(angulo_radianos) * aceleracao;
    float move_y = sinf(angulo_radianos) * aceleracao;
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


// Função para atirar com a nave
void Atira_Nave(Sound missile_sound, int *temporizador, Projetil tiros[], float pos_x_nave, float pos_y_nave, float angulo_nave){    
    if (*temporizador < 60) {
        (*temporizador)++;
    }

    // Se a tecla estiver pressionada E a arma estiver carregada
    if(IsKeyPressed(KEY_SPACE) && (*temporizador) >= 60){
        SetSoundVolume(missile_sound, 0.2f);
        PlaySound(missile_sound);
        for(int i = 0; i < MAX_TIROS; i++){
            if(tiros[i].ativo == false){
                tiros[i].ativo = true;

                float pos_inicial_x = pos_x_nave;
                float pos_inicial_y = pos_y_nave;

                if(pos_inicial_x > LARGURA_TELA){
                    pos_inicial_x -= LARGURA_TELA;
                }
                else if(pos_inicial_x < 0){
                    pos_inicial_x += LARGURA_TELA;
                }

                if(pos_inicial_y > ALTURA_TELA){
                    pos_inicial_y -= ALTURA_TELA;
                }
                else if(pos_inicial_y < 0){
                    pos_inicial_y += ALTURA_TELA;
                }

                float raio_nave = 32.0f;
                float velocidade_tiro = 15.0f;
                float angulo_ajustado = angulo_nave - 90.0f;
                float angulo_radianos = angulo_ajustado * (PI / 180.0f);

                tiros[i].pos_x = pos_inicial_x + (cosf(angulo_radianos) * raio_nave);
                tiros[i].pos_y = pos_inicial_y + (sinf(angulo_radianos) * raio_nave);
                tiros[i].angulo = angulo_nave;
                tiros[i].vel_x = cosf(angulo_radianos) * velocidade_tiro;
                tiros[i].vel_y = sinf(angulo_radianos) * velocidade_tiro;

                // A nave atirou, zera o timer
                *temporizador = 0; 
                break;
            
            }
        }
    }
}

// Função que desenha o tiro da nave
void Atualiza_Tiro(int *framerate, Projetil tiros[], Texture2D textura_projetil, Vector2 pivo_projetil){
    for(int i = 0; i < MAX_TIROS; i++){
        if(tiros[i].ativo == true){
            tiros[i].pos_x += tiros[i].vel_x;
            tiros[i].pos_y += tiros[i].vel_y;
            Rectangle tiro_hitbox_source = {(*framerate) * 4, 0, 4, 16};
            Rectangle tiro_hitbox_dest = {roundf(tiros[i].pos_x), roundf(tiros[i].pos_y), 4, 16};

            DrawTexturePro(textura_projetil, tiro_hitbox_source, tiro_hitbox_dest, pivo_projetil, tiros[i].angulo, WHITE);

            if(tiros[i].pos_x < -64 || tiros[i].pos_x > LARGURA_TELA + 64){
                tiros[i].ativo = false;
            }
            if(tiros[i].pos_y < -64 || tiros[i].pos_y > ALTURA_TELA + 64){
                tiros[i].ativo = false;
            }
        }
    }

}

//Função para gerar a barra de carregamento dos tiros da nave
void Atualiza_Barra(int temporizador_tiro, int *framerate_barra){
   // A cada 10 frames a barra avança 1 frame
   *framerate_barra = (temporizador_tiro / 12);

   if(*framerate_barra > 5){
        *framerate_barra = 5;
   }
}

// Função para desenhar a barra de carregamento dos tiros da nave
void Desenha_Barra(int *framerate, Vector2 pivo_barra, Texture2D textura_barra){
    Rectangle barra_hitbox_source = {(*framerate) * 150, 0 , 150, 25};
    Rectangle barra_hitbox_dest = {LARGURA_TELA - 125, ALTURA_TELA - 35 , 150, 25};
    DrawTexturePro(textura_barra, barra_hitbox_source, barra_hitbox_dest, pivo_barra, 0, WHITE);
}


//////////////////////////////////////////////////
//Funções dos asteroides
//////////////////////////////////////////////////

void Atualiza_Asteroides(Contextos_Jogo *ctx) {
    int i;
    Asteroide ast;
    
    for (i=0; i<MAX_TIROS; i++) {
        ast = ctx->asteroides[i];
        
        // se não estiver ativo, ignorar
        if ( ! ast.ativo) continue;
        
        // movimento
        ast.pos_x += ast.vel_x;
        ast.pos_y += ast.vel_y;
        // rotacao
        ast.angulo += ast.vel_angular;

        
    
    }
}


void Desenha_Asteroides(Contextos_Jogo *ctx);


//////////////////////////////////////////////////
//Funções de Parallax
//////////////////////////////////////////////////

void Move_Cenario(float *pos_y, float *pos_x, float *vel_x_nave, float *vel_y_nave, float peso_parallax){
    (*pos_y) -= (*vel_y_nave * peso_parallax);
    (*pos_x) -= (*vel_x_nave * peso_parallax);

    // Borda Direita / Esquerda
    if((*pos_x) >= LARGURA_TELA){
        (*pos_x) -= LARGURA_TELA;
    }
    else if((*pos_x) < 0){
        (*pos_x) += LARGURA_TELA;
    }

    // Borda Baixo / Cima
    if((*pos_y) >= ALTURA_TELA){
        (*pos_y) -= ALTURA_TELA;
    }
    else if((*pos_y) < 0){
        (*pos_y) += ALTURA_TELA;
    }
}

void Desenha_Cenario(Texture2D textura, float *pos_x, float *pos_y){
    int px = roundf(*pos_x);
    int py = roundf(*pos_y);

    // Quadrante Principal (Sudeste)
    DrawTexture(textura, px, py, WHITE);
    
    // Quadrante Esquerdo (Sudoeste)
    DrawTexture(textura, px - LARGURA_TELA, py, WHITE);
    
    // Quadrante Superior (Nordeste)
    DrawTexture(textura, px, py - ALTURA_TELA, WHITE);
    
    // Quadrante Diagonal (Noroeste)
    DrawTexture(textura, px - LARGURA_TELA, py - ALTURA_TELA, WHITE);
}