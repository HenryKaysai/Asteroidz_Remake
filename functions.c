/*
Arquivo que contem todas as definicoes de funcoes do jogo,
desde funcoes genericas ate funcoes auxiliares
*/



#include "raylib.h"
#include "prototypes.h"
#include <math.h>
#include <stdio.h>

//////////////////////////////////////////////////
//Funções dos estados do jogo
//////////////////////////////////////////////////

// funcao para voltar de menus
// retorna true se apertar esc e false se nao
bool Sai_Menu(GameState *estado, GameState estado_saida){
    if(IsKeyPressed(KEY_ESCAPE)){
        (*estado) = estado_saida;
        return true;
    }
    return false;
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

//Função para o desenho do menu principal e de pausa
void Desenha_Menu(const char* titulo, const char* opcoes[], int total_opcoes, int selecionada) {
    // Desenha o titulo
    Desenha_Texto_Centralizado(titulo, ALTURA_TELA / 4, 60, WHITE);

    int inicio_y = (ALTURA_TELA / 2) + 60;
    
    for (int i = 0; i < total_opcoes; i++) {
        Color cor = (selecionada == i) ? PINK : WHITE;
        Desenha_Texto_Centralizado(opcoes[i], inicio_y + (i * 50), 32, cor);
    }
}

// Função para desenhar a seta do menu em diferentes posições
void Desenha_Seta_Menu(int *framerate, int *opcao_selecionada, Texture2D textura, Vector2 pivo, const char* textos[], int total_opcoes) {
    int inicio_y = (ALTURA_TELA / 2) + 60;
    Rectangle seta_hitbox_source = {(*framerate) * 30, 0, 30, 30};

    // calcula o x base do texto selecionado
    int largura_texto = MeasureText(textos[*opcao_selecionada], 32); //textos[*opcao_selecionada]
    int texto_x = (LARGURA_TELA / 2) - (largura_texto / 2);
    
    // posiciona a seta 35px a esquerda do inicio do texto
    int seta_x = texto_x - 35; 
    
    // o y é calculado baseadoo na opcao selecionada
    int seta_y = inicio_y + ((*opcao_selecionada) * 50) + 11; 

    Rectangle seta_hitbox_dest = { (float)seta_x, (float)seta_y, 32, 32 };

    DrawTexturePro(textura, seta_hitbox_source, seta_hitbox_dest, pivo, 0, WHITE);
}

//Função para medir texto e evitar usar 2 funções
void Desconta_Tamanho(const char* texto, Vector2 pos, int tamanho_fonte, Color cor){
    int largura_texto = MeasureText(texto, tamanho_fonte);
    DrawText(texto, roundf(pos.x) - largura_texto/2, roundf(pos.y), tamanho_fonte, cor);
}

//Função para desenhar o menu de pausa
void Desenha_Menu_Slots(int *opcao_selecionada, const char* titulo_menu){
    // Funcao generica para desenhar os slots nos menus de Save e de Load

    Desenha_Texto_Centralizado(titulo_menu, 60, 60, WHITE);

    int fonte_slot = 24;

    // gera 8 quadrados denominados LOAD 1, LOAD 2... LOAD 8 
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
        Desconta_Tamanho(texto_slot, (Vector2){ (float)(pos_x + 130), (float)(pos_y + 90) }, fonte_slot, PINK);
    }

    // BOTA VOLTAR (opcao 8)
    Color cor_back = ((*opcao_selecionada) == 8) ? PINK : WHITE;
    Desenha_Texto_Centralizado("BACK", 700, 40, cor_back);
}



//////////////////////////////////////////////////
//Funções de funcionalidade de opções de menu
//////////////////////////////////////////////////

void Escolhe_Slot(Contextos_Jogo *ctx, 
                    GameState *estado,      // Estado atual - pode ser load ou save
                    GameState estado_voltar // Estado desejado ao voltar 
                    ){ 
    // Funcao generica que serve tanto para o estado de Load quanto Save

    // Pra facilitar o uso das teclas up e down pra navegar entre slots
    int mapa_cima[9]  =    {8, 8, 8, 8, 0, 1, 2, 3, 5};
    int mapa_baixo[9] =    {4, 5, 6, 7, 8, 8, 8, 8, 1};
           
    // Atualiza opcao_selecionada baseada no teclado
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)){
        (ctx->opcao_selecionada)++;
        if(ctx->opcao_selecionada > 8) ctx->opcao_selecionada = 0;
    }
    else if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)){
        (ctx->opcao_selecionada)--;
        if(ctx->opcao_selecionada < 0) ctx->opcao_selecionada = 8;
    }
    else if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        ctx->opcao_selecionada = mapa_cima[ctx->opcao_selecionada];
    }
    else if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        ctx->opcao_selecionada = mapa_baixo[ctx->opcao_selecionada];
    }
    
    Vector2 mouse_virtual = GetMousePosition();

    // Atualiza opcao_selecionada se o mouse tiver dentro dos hitbox dos slots
    for (int i = 0; i < 8; i++) {
        int linha = i / 4;
        int coluna = i % 4;
        Rectangle slot_hit_box = {20 + (coluna * 300), 140 + (linha * 250), 260, 220};
        
        if(CheckCollisionPointRec(mouse_virtual, slot_hit_box)) {
            ctx->opcao_selecionada = i;
        }
    }

    // Atualiza opcao_selecionada se mouse estiver no hitbox do voltar
    Rectangle back_hit_box = {0, 700, LARGURA_TELA, 40};
    if(CheckCollisionPointRec(mouse_virtual, back_hit_box)){
        ctx->opcao_selecionada = 8;
    }
    
    // Efetua a selecao atualizando o estado com base na opcao_selecionada
    if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if (ctx->opcao_selecionada >= 0 && ctx->opcao_selecionada <= 7) {

            if (*estado == SAVE) {
                Executa_Save(ctx, ctx->opcao_selecionada, estado);
            } else if (*estado == LOAD) {
                Executa_Load(ctx, ctx->opcao_selecionada, estado);
            }
            
        } 
        else if (ctx->opcao_selecionada == 8) {
            *estado = estado_voltar;
            // reseta a opcao_selecionada
            ctx->opcao_selecionada = 0;
        }
    }
}
                    


// Função para selecao de opcoes nos menus principal e de pausa
int Navega_Menu(int *selecionada, int max_opcoes, float inicio_y, float altura_linha) {
    // Teclado
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) (*selecionada)++;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) (*selecionada)--;

    // Normalização (Loop do menu)
    if (*selecionada >= max_opcoes) *selecionada = 0;
    if (*selecionada < 0) *selecionada = max_opcoes - 1;

    // Mouse (Verifica se está sobre alguma das linhas)
    Vector2 mouse = GetMousePosition();
    for (int i = 0; i < max_opcoes; i++) {
        Rectangle hit_box = { 0, inicio_y + (i * altura_linha), LARGURA_TELA, 32 };
        if (CheckCollisionPointRec(mouse, hit_box)) *selecionada = i;
    }
    
    // Retorna 1 se o jogador selecionou algo
    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 1;
    
    return 0;
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

// Função para fazer a nave e os asteroides sairem de um lado para o outro
void Aplica_Limites_Circulares(Vector2 *pos, float tamanho){

    //EIXO X
    if((pos->x) > LARGURA_TELA + tamanho){
        pos->x -= LARGURA_TELA;
    }
    else if((pos->x) < -tamanho){
        pos->x += LARGURA_TELA;
    }
    
    // EIXO Y
    if((pos->y) > ALTURA_TELA + tamanho){
        pos->y -= ALTURA_TELA;
    }
    else if((pos->y) < -tamanho){
        pos->y += ALTURA_TELA;
    }
}


//////////////////////////////////////////////////
//Funções auxiliares de desenho 
//////////////////////////////////////////////////

// funcao generica para desenhar as copias nas bordas da tela
void Desenha_Fantasmas(Texture2D textura, Rectangle source, Vector2 pos, float tamanho, Vector2 pivo, float angulo) {
    float pos_x = pos.x;
    float pos_y = pos.y;
    // EIXO X
    if (pos_x > LARGURA_TELA - tamanho) {
        Rectangle fantasma_x = {roundf(pos_x - LARGURA_TELA), roundf(pos_y), tamanho, tamanho};
        DrawTexturePro(textura, source, fantasma_x, pivo, roundf(angulo), WHITE);
    }
    else if (pos_x < tamanho) {
        Rectangle fantasma_x = {roundf(pos_x + LARGURA_TELA), roundf(pos_y), tamanho, tamanho};
        DrawTexturePro(textura, source, fantasma_x, pivo, roundf(angulo), WHITE);
    }

    // EIXO Y
    if (pos_y > ALTURA_TELA - tamanho) { 
        Rectangle fantasma_y = {roundf(pos_x), roundf(pos_y - ALTURA_TELA), tamanho, tamanho};
        DrawTexturePro(textura, source, fantasma_y, pivo, roundf(angulo), WHITE);
    }
    else if (pos_y < tamanho) { 
        Rectangle fantasma_y = {roundf(pos_x), roundf(pos_y + ALTURA_TELA), tamanho, tamanho}; 
        DrawTexturePro(textura, source, fantasma_y, pivo, roundf(angulo), WHITE);
    }

    // QUINAS DA TELA
    if ((pos_x > LARGURA_TELA - tamanho || pos_x < tamanho) && 
        (pos_y > ALTURA_TELA - tamanho || pos_y < tamanho)) {
        
        float quina_x = pos_x;
        float quina_y = pos_y;

        if (pos_x > LARGURA_TELA - tamanho) quina_x -= LARGURA_TELA;
        else if (pos_x < tamanho) quina_x += LARGURA_TELA;

        if (pos_y > ALTURA_TELA - tamanho) quina_y -= ALTURA_TELA;
        else if (pos_y < tamanho) quina_y += ALTURA_TELA;

        Rectangle fantasma_quina = {roundf(quina_x), roundf(quina_y), tamanho, tamanho};
        DrawTexturePro(textura, source, fantasma_quina, pivo, roundf(angulo), WHITE);
    }
}

//////////////////////////////////////////////////
//Funções da nave
//////////////////////////////////////////////////

// Função orquestradora 
void Atualiza_Nave(Contextos_Jogo* ctx, Som* som) {
    Gira_Nave(&ctx->player.angulo);
    Som_Motor(som->engine, &som->marcador_som_engine, &som->volume_engine);
    Acelera_Nave(&ctx->player.vel, &ctx->player.pos, &ctx->player.angulo);
    Anima_Nave(&ctx->frame_atual, &ctx->contador_tempo, ctx->velocidade_animacao);
    Aplica_Limites_Circulares(&ctx->player.pos, TAMANHO_NAVE);
    Atira_Nave(som->missile_sound, &ctx->contador, ctx->tiros, ctx->player.pos, ctx->player.angulo);
}



//Função para atualizar a animação da nave
void Anima_Nave(int *frame, int *contador, int velocidade){
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
void Desenha_Nave(Contextos_Jogo *ctx, Som *som) {
    Rectangle nave_hitbox_source = {ctx->frame_atual * TAMANHO_NAVE, 0, TAMANHO_NAVE, TAMANHO_NAVE};
    Rectangle nave_hitbox_dest = {roundf(ctx->player.pos.x), roundf(ctx->player.pos.y), TAMANHO_NAVE, TAMANHO_NAVE};

    Texture2D textura_ativa;

    // Lógica do motor e som
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        textura_ativa = ctx->Nave_Propulsor;
        som->marcador_som_engine = 1;
    } else {
        som->marcador_som_engine = 0;
        textura_ativa = ctx->Nave;
    }
    
    // se nao estiver invencivel OU
    // se o tempo invencivel for divisivel por 4 (faz piscar rapido)
    if (ctx->player.tempo_invencivel <= 0 || ctx->player.tempo_invencivel % 8 < 4) {
        
        DrawTexturePro(textura_ativa, nave_hitbox_source, nave_hitbox_dest, PIVO_NAVE, roundf(ctx->player.angulo), WHITE);
        Desenha_Fantasmas(textura_ativa, nave_hitbox_source, ctx->player.pos, TAMANHO_NAVE, PIVO_NAVE, ctx->player.angulo);
        
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
void Acelera_Nave(Vector2 *vel, Vector2 *pos, float *angulo){
    float aceleracao = 0.1f; 
    float angulo_ajustado = (*angulo) - 90.0f; //pro sprite começar apontado para cima
    float angulo_radianos = angulo_ajustado * (PI / 180.0f);//math.h opera em radianos
    float move_x = cosf(angulo_radianos) * aceleracao;
    float move_y = sinf(angulo_radianos) * aceleracao;

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){//acelera a posição do sprite na direção do bico da nave
        vel->x += move_x;
        vel->y += move_y;
    }
    vel->x *= 0.99f; //inércia 
    vel->y *= 0.99f;  // desacelera 1% a cada frame

    if(vel->x > -0.01f && vel->x < 0.01f) vel->x = 0.0f;
    if(vel->y > -0.01f && vel->y < 0.01f) vel->y = 0.0f;

    pos->x += vel->x;//move a nave de fato
    pos->y += vel->y;
}


// Função para atirar com a nave
void Atira_Nave(Sound missile_sound, int *temporizador, Projetil tiros[], Vector2 pos_nave, float angulo_nave){    
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

                float pos_inicial_x = pos_nave.x;
                float pos_inicial_y = pos_nave.y;

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

                tiros[i].pos.x = pos_inicial_x + (cosf(angulo_radianos) * raio_nave);
                tiros[i].pos.y = pos_inicial_y + (sinf(angulo_radianos) * raio_nave);
                tiros[i].angulo = angulo_nave;
                tiros[i].vel.x = cosf(angulo_radianos) * velocidade_tiro;
                tiros[i].vel.y = sinf(angulo_radianos) * velocidade_tiro;

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
            tiros[i].pos.x += tiros[i].vel.x;
            tiros[i].pos.y += tiros[i].vel.y;
            Rectangle tiro_hitbox_source = {(*framerate) * 4, 0, 4, 16};
            Rectangle tiro_hitbox_dest = {roundf(tiros[i].pos.x), roundf(tiros[i].pos.y), 4, 16};

            DrawTexturePro(textura_projetil, tiro_hitbox_source, tiro_hitbox_dest, pivo_projetil, tiros[i].angulo, WHITE);

            if(tiros[i].pos.x < -64 || tiros[i].pos.x > LARGURA_TELA + 64){
                tiros[i].ativo = false;
            }
            if(tiros[i].pos.y < -64 || tiros[i].pos.y > ALTURA_TELA + 64){
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

// Função para desenhar a interface contendo:
// barra de municao, vidas e fase atual
void Desenha_Interface(Contextos_Jogo *ctx) { 
    
    // barra de municao
    Rectangle barra_hitbox_source = {(ctx->frames_barra) * 150, 0 , 150, 25};
    Rectangle barra_hitbox_dest = {LARGURA_TELA - 125, ALTURA_TELA - 30 , 150, 25};
    DrawTexturePro(ctx->Barra_Carregamento, barra_hitbox_source, barra_hitbox_dest, PIVO_BARRA, 0, WHITE);

    // vidas restantes
    const char* texto_vidas = TextFormat("VIDAS: %d", ctx->player.vidas);
    int largura_vidas = MeasureText(texto_vidas, 25);
    DrawText(texto_vidas, LARGURA_TELA - largura_vidas - 20, ALTURA_TELA - 70, 25, WHITE);

    // fase atual
    const char* texto_fase = TextFormat("FASE: %d", ctx->fase_atual);
    int largura_fase = MeasureText(texto_fase, 25);
    DrawText(texto_fase, LARGURA_TELA - largura_fase - 20, ALTURA_TELA - 100, 25, WHITE);

    // pontuacao
    const char* texto_pontos = TextFormat("PONTOS: %d", ctx->pontuacao);
    int largura_pontos = MeasureText(texto_pontos, 25);
    DrawText(texto_pontos, LARGURA_TELA - largura_pontos - 20, ALTURA_TELA - 130, 25, WHITE);
}



//////////////////////////////////////////////////
//Funções de Parallax
//////////////////////////////////////////////////

void Move_Cenario(Vector2 *pos_parallax, Vector2 *vel_nave, float peso_parallax){
    pos_parallax->y -= (vel_nave->y * peso_parallax);
    pos_parallax->x -= (vel_nave->x * peso_parallax);

    // Borda Direita / Esquerda
    if(pos_parallax->x >= LARGURA_TELA){
        pos_parallax->x -= LARGURA_TELA;
    }
    else if(pos_parallax->x < 0){
        pos_parallax->x += LARGURA_TELA;
    }

    // Borda Baixo / Cima
    if(pos_parallax->y >= ALTURA_TELA){
        pos_parallax->y -= ALTURA_TELA;
    }
    else if(pos_parallax->y < 0){
        pos_parallax->y += ALTURA_TELA;
    }
}

void Desenha_Cenario(Texture2D textura, Vector2 pos){
    int px = roundf(pos.x);
    int py = roundf(pos.y);

    // Quadrante Principal (Sudeste)
    DrawTexture(textura, px, py, WHITE);
    
    // Quadrante Esquerdo (Sudoeste)
    DrawTexture(textura, px - LARGURA_TELA, py, WHITE);
    
    // Quadrante Superior (Nordeste)
    DrawTexture(textura, px, py - ALTURA_TELA, WHITE);
    
    // Quadrante Diagonal (Noroeste)
    DrawTexture(textura, px - LARGURA_TELA, py - ALTURA_TELA, WHITE);
}



//////////////////////////////////////////////////
//Funções dos asteroides
//////////////////////////////////////////////////

// Atualiza a posicao e rotacao dos asteroides a cada frame
void Atualiza_Asteroides(Contextos_Jogo *ctx) {
    int i;
    
    for (i=0; i<MAX_ASTEROIDES; i++) {
        
        // se não estiver ativo, ignorar
        if (! ctx->asteroides[i].ativo) continue;
        
        // movimento
        ctx->asteroides[i].pos.x += ctx->asteroides[i].vel.x;
        ctx->asteroides[i].pos.y += ctx->asteroides[i].vel.y;
        // rotacao
        ctx->asteroides[i].angulo += ctx->asteroides[i].vel_angular;

        Aplica_Limites_Circulares(&ctx->asteroides[i].pos, TAMANHO_ASTEROIDE);
    
    }
}

// Desenha os asteroides na tela 
void Desenha_Asteroides(Contextos_Jogo *ctx) {
    int i;

    for (i=0; i<MAX_ASTEROIDES; i++) {
        // se não estiver ativo, ignorar
        if (! ctx->asteroides[i].ativo) continue;

        Texture2D textura_atual;
        Vector2 pivo_asteroide = { TAMANHO_ASTEROIDE / 2, TAMANHO_ASTEROIDE / 2 };

        // identifica a textura e salva em textura_atual
        switch (ctx->asteroides[i].tipo) {
            case (1): 
                textura_atual = ctx->Asteroid_1;
                break;
            case (2): 
                textura_atual = ctx->Asteroid_2;
                break;
            case (3): 
                textura_atual = ctx->Asteroid_3;
                break;
            default:  textura_atual = ctx->Asteroid_1; break; // Prevenção de crash
        }

        Rectangle source = { 0, 0, (float)textura_atual.width, (float)textura_atual.height };
        
        // Define a posição na tela 
        Rectangle dest = { ctx->asteroides[i].pos.x, ctx->asteroides[i].pos.y, TAMANHO_ASTEROIDE, TAMANHO_ASTEROIDE };

        // Desenha com rotacao
        DrawTexturePro(textura_atual, source, dest, pivo_asteroide, ctx->asteroides[i].angulo, WHITE);

        Desenha_Fantasmas(textura_atual, source, ctx->asteroides[i].pos, TAMANHO_ASTEROIDE, pivo_asteroide, ctx->asteroides[i].angulo);
    }
}


//////////////////////////////////////////////////
//Funções de colisão
//////////////////////////////////////////////////

void Checa_Colisao_Tiro_Asteroide(Contextos_Jogo *ctx, Som *som) {
    int t, a; //index para tiros e asteroides

    for (t=0; t<MAX_TIROS; t++) {
        // se o tiro não estiver ativo, passa pro prox
        if (!ctx->tiros[t].ativo) continue;

        for (a=0; a<MAX_ASTEROIDES; a++) {
            // se o asteroide nao estiver ativo, ignora
            if (!ctx->asteroides[a].ativo) continue;

            float raio_tiro = 4.0f; // aprox do projetil (meio da sprite 4x16)
            float raio_asteroide = TAMANHO_ASTEROIDE / 2.0f;

            if (CheckCollisionCircles(ctx->tiros[t].pos, raio_tiro,
                                      ctx->asteroides[a].pos, raio_asteroide)) {
                // desativa tiro e asteroide ao colidir
                ctx->tiros[t].ativo = false;
                ctx->asteroides[a].ativo = false;
                
                PlaySound(som->explosion_sound); //toca som da explosao

                //pro calculo do bonus dps
                ctx->asteroides_destruidos++;

                ctx->pontuacao += PONTOS_GANHOS_ASTEROIDE;

                // procura uma explosao inativa e liga ela na posicao do asteroide
                for (int e = 0; e < MAX_EXPLOSOES; e++) {
                    if (ctx->explosoes[e].ativo == false) {
                        ctx->explosoes[e].ativo = true;
                        ctx->explosoes[e].pos = ctx->asteroides[a].pos; // Nasce onde o asteroide morreu
                        ctx->explosoes[e].frame_atual = 0;
                        ctx->explosoes[e].contador_tempo = 0;
                        break; // Ativou uma, pode parar de procurar
                    }
                }

                // break, ja que um tiro so pode destruir um asteroide
                break;
            }
        }
    }
}




bool Checa_Colisao_Nave_Asteroide(Contextos_Jogo *ctx) {
    int a; //index para tiros e asteroides

    for (a=0; a<MAX_ASTEROIDES; a++) {
        // se o asteroide nao estiver ativo, pula pra prox iteracao
        if (!ctx->asteroides[a].ativo) continue;
        
        // nave possui duas hitbox: uma pra ponta e outra pro corpo
        Vector2 ponta = Calcula_Posicao_Ponto(ctx->player.pos, ctx->player.angulo, 0, -20);
        Vector2 corpo = Calcula_Posicao_Ponto(ctx->player.pos, ctx->player.angulo, 0, 5);

        float raio_ponta = 8.0f;   // raio hitbox ponta
        float raio_corpo = 22.0f; // raio hitbox corpo

        // verifica se o asteroide bateu em uma das hitbox
        if (CheckCollisionCircles(ponta, raio_ponta, ctx->asteroides[a].pos, TAMANHO_ASTEROIDE/2) ||
            CheckCollisionCircles(corpo, raio_corpo, ctx->asteroides[a].pos, TAMANHO_ASTEROIDE/2)) {
            return true;
        }
    
    }
    return false;
}

Vector2 Calcula_Posicao_Ponto(Vector2 centro_nave, float angulo, float offset_x, float offset_y) {
    float rad = angulo * (PI / 180.0f);
    // Matriz de rotação básica
    float x_rot = offset_x * cosf(rad) - offset_y * sinf(rad);
    float y_rot = offset_x * sinf(rad) + offset_y * cosf(rad);
    
    return (Vector2){ centro_nave.x + x_rot, centro_nave.y + y_rot };
}

//////////////////////////////////////////////////
//Funções de fase e arquivos
//////////////////////////////////////////////////

int Carrega_Fase(Contextos_Jogo *ctx, const char *nome_arquivo) {
    int i; // para o loop for

    // variaveis temporarias, uma cada para coluna
    char tipo_lido;
    int temp_pos_x, temp_pos_y;
    float temp_vel_x, temp_vel_y;
    // arquivo
    FILE *arquivo_nivel = fopen(nome_arquivo, "r");

    // conferir se abriu certo
    if (arquivo_nivel == NULL) {
        // se nao abriu certo, arquivo nao existe
        // logo, as fases acabaram
        return 1;
    }
    
    // loop para ler linha por linha
    // enqt ler 5 valores, continuar
    while (fscanf(arquivo_nivel, 
                    " %c, %d, %d, %f, %f", 
                    &tipo_lido, 
                    &temp_pos_x,
                    &temp_pos_y,
                    &temp_vel_x,
                    &temp_vel_y) == 5) {
        
        // se for nave
        if (tipo_lido == 'N') {
            ctx->player.pos.x = temp_pos_x;
            ctx->player.pos.y = temp_pos_y;
            ctx->player.vel.x = temp_vel_x;
            ctx->player.vel.y = temp_vel_y;
            // tambem salva a posicao inicial pra quando perde vida
            ctx->pos_inicial_fase.x = temp_pos_x;
            ctx->pos_inicial_fase.y = temp_pos_y;
        }
        // se for asteroide
        else if (tipo_lido == 'A') {

            // itera sobre o vetor de asteroides
            for (i=0; i<MAX_ASTEROIDES; i++) {

                // se o asteroide ja estiver ativo, pula pro proximo
                if (ctx->asteroides[i].ativo) continue;

                // assumindo que esse esta inativo:
                ctx->asteroides[i].pos.x = temp_pos_x;
                ctx->asteroides[i].pos.y = temp_pos_y;
                ctx->asteroides[i].vel.x = temp_vel_x;
                ctx->asteroides[i].vel.y = temp_vel_y;
                ctx->asteroides[i].ativo = true;

                // sorteia a aparencia e a velocidade angular
                ctx->asteroides[i].tipo = GetRandomValue(1, 3);
                ctx->asteroides[i].vel_angular = GetRandomValue(-3, 3);

                // para nao continuar salvando esse asteroide
                // no resto do vetor ctx->asteroides
                break;
            }
        }
    }

    fclose(arquivo_nivel);
    return 0;
}

int Checa_Fase_Concluida(Contextos_Jogo *ctx) {
    for (int i = 0; i < MAX_ASTEROIDES; i++) {
        // se achar pelo menos um asteroide vivo, a fase nao acabou
        if (ctx->asteroides[i].ativo == true) {
            return 0; // falso
        }
    }

    return 1; // verdadeiro
}

void Passa_Proxima_Fase(Contextos_Jogo *ctx, GameState *estado) {

    ctx->fase_atual++; // sobe o nivel
                    
    // monta o nome do prox arquivo 
    char proxima_fase[50]; 
    sprintf(proxima_fase, "fases/nivel_%d.txt", ctx->fase_atual);
    
    // tenta carregar a proxima fase
    // se devolver 1, significa que as fases acabaram
    if (Carrega_Fase(ctx, proxima_fase) == 1) {
        Vitoria(ctx, estado);
        ctx->fase_atual = 1; // reseta pra proxima 
        return;
    }
    
    // reseta tiros
    for(int i = 0; i < MAX_TIROS; i++) {
        ctx->tiros[i].ativo = false;
    }
}

void Resetar_Jogo(Contextos_Jogo *ctx) {
    ctx->pontuacao = 0;
    ctx->frames_jogados = 0;
    ctx->asteroides_destruidos = 0;

    // desativa todos os asteroides
    for (int i = 0; i < MAX_ASTEROIDES; i++) {
        ctx->asteroides[i].ativo = false;
    }

    // desativa as explosoes
    for (int i = 0; i < MAX_EXPLOSOES; i++) {
    ctx->explosoes[i].ativo = false;
    }

    // desativa todos os tiros
    for (int i = 0; i < MAX_TIROS; i++) {
        ctx->tiros[i].ativo = false;
    }

    // reseta o jogador
    ctx->player.pos = (Vector2){ LARGURA_TELA / 2, ALTURA_TELA / 2 };
    ctx->player.vel = (Vector2){ 0.0f, 0.0f };
    ctx->player.vidas = 3;
    ctx->fase_atual = 1;
}

void Perde_Vida(Contextos_Jogo *ctx, GameState *estado) {
    // tira uma vida
    ctx->player.vidas--;

    ctx->pontuacao -= PONTOS_PERDIDOS_MORTE;

    if (ctx->player.vidas <= 0) {
        GameOver(ctx, estado);
        return;
    }

    // reseta a posicao
    ctx->player.pos = ctx->pos_inicial_fase;
    // reseta a velocidade
    ctx->player.vel = (Vector2){0.0f, 0.0f};
    // da um tempo de invencibilidade
    ctx->player.tempo_invencivel = 30;

}




//////////////////////////////////////////////////
//Funções de LOAD e SAVE
//////////////////////////////////////////////////

int Executa_Save(Contextos_Jogo *ctx, int slot, GameState *estado) {

    char nome_arquivo[27];
    sprintf(nome_arquivo, "saves/save_%d.bin", slot+1); //+1 pra ficar de 1 a 8

    FILE *arquivo_save = fopen(nome_arquivo, "wb");

    // conferir se abriu certo
    if (arquivo_save == NULL) {
        printf("ERRO AO ABRIR ARQUIVO\n");
        return 1;
    }
    
    SaveData data = Prepara_SaveData(ctx);
    
    fwrite(&data, sizeof(SaveData), 1, arquivo_save);

    fclose(arquivo_save);

    *estado = MENU;
    ctx->opcao_selecionada=0;

    return 0;
}

// captura os dados do jogo e salva em uma instancia de SaveData
// chamada quando o jogador escolhe um slot para save
SaveData Prepara_SaveData(Contextos_Jogo *ctx) {
    int i; // pro for loop
    SaveData data;

    data.fase_atual = ctx->fase_atual;
    data.pontuacao = ctx->pontuacao;
    data.frames_jogados = ctx->frames_jogados;
    data.asteroides_destruidos = ctx->asteroides_destruidos;
    data.player = ctx->player;
    
    
    for (i=0; i<MAX_ASTEROIDES; i++) {
        data.asteroides[i] = ctx->asteroides[i];
    }
    return data;
}

// le um arquivo de save e chama Carrega_SaveData 
// chamada quando o jogador escolhe um slot para carregar
int Executa_Load(Contextos_Jogo *ctx, int slot, GameState *estado) {
    char nome_arquivo[27];
    sprintf(nome_arquivo, "saves/save_%d.bin", slot+1); //+1 pra ficar de 1 a 8
    
    FILE *arquivo_load = fopen(nome_arquivo, "rb");

    if (arquivo_load == NULL) {
        Erro_Load_Vazia(ctx, slot + 1);
        return 1;
    }
    
    SaveData data; 
    // le o arquivo e salva tudo na variavel data
    fread(&data, sizeof(SaveData), 1, arquivo_load);
    
    // passa os dados para o contexto do jogo
    Carrega_SaveData(ctx, data);

    // muda o estado pra JOGANDO
    *estado = JOGANDO;
    HideCursor();    
    DisableCursor();

    // pra evitar crash de erro de indice
    ctx->opcao_selecionada = 0;

    fclose(arquivo_load);
    return 0;
}

// dada uma savedata, salva os dados no contexto do jogo
void Carrega_SaveData(Contextos_Jogo *ctx, SaveData data) {
    int i; // pro loop for
    
    ctx->fase_atual = data.fase_atual;
    ctx->player = data.player;
    ctx->pontuacao = data.pontuacao;
    ctx->frames_jogados = data.frames_jogados;
    ctx->asteroides_destruidos = data.asteroides_destruidos;

    for (i=0; i<MAX_ASTEROIDES; i++) {
        ctx->asteroides[i] = data.asteroides[i];
    }
}

// pra ser chamada se tentam carregar um slot vazio
void Erro_Load_Vazia(Contextos_Jogo *ctx, int slot) {
    ctx->timer_erro_load = 120; // Fica na tela por 2 segundos (60 * 2)
    ctx->slot_erro = slot;      // Guarda o número do slot que falhou
    // mostrar na tela uma mensagem de erro dizendo "Save X está vazio!"
}

void Desenha_Erro_Load_Vazia(int slot_erro) {
    DrawRectangle(LARGURA_TELA / 2 - 200, ALTURA_TELA / 2 - 50, 400, 100, Fade(BLACK, 0.9f));
    DrawRectangleLines(LARGURA_TELA / 2 - 200, ALTURA_TELA / 2 - 50, 400, 100, RED);
    
    char msg_erro[50];
    sprintf(msg_erro, "SLOT %d VAZIO!", slot_erro);
    
    // desenha o texto centralizado na caixa
    Desenha_Texto_Centralizado(msg_erro, ALTURA_TELA / 2 - 15, 30, RED);
}



// carrega o arquivo binario do best_scores em modo de leitura
void Carrega_Ranking(Contextos_Jogo *ctx){
    FILE *arquivo_ranking = fopen(BEST_SCORES_FILENAME, "rb");

    if (arquivo_ranking == NULL) {
        // Se o arquivo não existe, zera tudo
        for (int i = 0; i < MAX_RANKING; i++) {
            ctx->ranking.pontuacoes[i] = 0;
        }
        return;
    }
    // se o arquivo existir, salva os dados no contexto
    fread(&ctx->ranking, sizeof(Ranking), 1, arquivo_ranking);
    
    fclose(arquivo_ranking);
}

// salva o ranking atualizado na memoria
void Salva_Ranking(Contextos_Jogo *ctx) {
    // wb cria o arquivo se nao existir
    FILE *arquivo = fopen(BEST_SCORES_FILENAME, "wb");
    if (arquivo != NULL) { // se nao der erro ao abrir
        fwrite(&ctx->ranking, sizeof(Ranking), 1, arquivo);
        fclose(arquivo);
        return;
    }
    printf("ERRO LENDO %s", BEST_SCORES_FILENAME);
}

void Atualiza_Ranking(Contextos_Jogo *ctx) {
    int i, j; // pro for

    Carrega_Ranking(ctx);

    for (i=0; i<MAX_RANKING; i++) {
        if (ctx->pontuacao >= ctx->ranking.pontuacoes[i]) {
            // empurra as menores uma posicao pra baixo
            // vai de tras pra frente pra nao perder dados
            for (j = MAX_RANKING - 1; j > i; j--) { 
                ctx->ranking.pontuacoes[j] = ctx->ranking.pontuacoes[j-1];
            }
            //insere nova pontuacao na posicao certa
            ctx->ranking.pontuacoes[i] = ctx->pontuacao;

            break;
        }
    } 
    // salva na memoria
    Salva_Ranking(ctx);
}

// Interface visual para a tela do Ranking
void Desenha_Best_Scores(Contextos_Jogo *ctx) {
    Desenha_Texto_Centralizado("BEST SCORES", 80, 60, WHITE);

    int inicio_y = 220;
    
    // Desenha as 5 posições
    for (int i = 0; i < MAX_RANKING; i++) {
        char texto_score[50];
        
        // se tem pontuacao, mostra ela formatada com zeros a esquerda
        if (ctx->ranking.pontuacoes[i] > 0) {
            sprintf(texto_score, "%d. %06d PONTOS", i + 1, ctx->ranking.pontuacoes[i]);
        } else {
            // se for zero, mostra uns tracinhos para ficar estiloso
            sprintf(texto_score, "%d. ------", i + 1); 
        }
        
        Desenha_Texto_Centralizado(texto_score, inicio_y + (i * 65), 40, WHITE);
    }

    // Botão de voltar (sempre destacado de rosa para mostrar que é a única opção)
    Color cor = (ctx->opcao_selecionada == 1) ? PINK : WHITE;
    Desenha_Texto_Centralizado("BACK", 700, 40, cor);
}

void Navega_Best_Scores(Contextos_Jogo *ctx, GameState *estado) {
    Vector2 mouse_bs = GetMousePosition();
    Rectangle back_hit_box_bs = {0, 700, LARGURA_TELA, 40};
    
    if (CheckCollisionPointRec(mouse_bs, back_hit_box_bs)) {
        // se mouse esta sobre o hitbox, selecionada = 1 para pintar de rosa
        ctx->opcao_selecionada = 1;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *estado = MENU;
            ctx->opcao_selecionada = 0;
        }
    } else { // se mouse nao tiver em cima da hitbox, de-seleciona
        ctx->opcao_selecionada = 0;
    } 
}

///////////////////////////////////////
// EXPLOSOES
///////////////////////////////////////

void Atualiza_Explosoes(Contextos_Jogo *ctx) {
    int velocidade_animacao = 4; //quantos frames dura cada img da animacao

    for (int i = 0; i < MAX_EXPLOSOES; i++) {
        if (ctx->explosoes[i].ativo == true) {
            
            ctx->explosoes[i].contador_tempo++;
            
            if (ctx->explosoes[i].contador_tempo >= velocidade_animacao) {
                ctx->explosoes[i].frame_atual++;
                ctx->explosoes[i].contador_tempo = 0;
            }

            if (ctx->explosoes[i].frame_atual > 7) { 
                ctx->explosoes[i].ativo = false;
            }
        }
    }
}

void Desenha_Explosoes(Contextos_Jogo *ctx) {
    for (int i = 0; i < MAX_EXPLOSOES; i++) {
        if (ctx->explosoes[i].ativo == true) {
            
            // tamanho do spirte da explosao
            float largura_frame = 60.0f; 
            float altura_frame = 60.0f;
            
            Rectangle source = { 
                ctx->explosoes[i].frame_atual * largura_frame, 
                0, 
                largura_frame, 
                altura_frame 
            };
            
            // pivo no centro
            Vector2 pivo = { 30.0f, 30.0f };
            
            // o destino eh o tamanho dos asteroides
            // raylib da zoom pra 96x96
            Rectangle dest = { 
                ctx->explosoes[i].pos.x, 
                ctx->explosoes[i].pos.y, 
                TAMANHO_ASTEROIDE, 
                TAMANHO_ASTEROIDE 
            };

            DrawTexturePro(ctx->Sprite_Explosao, source, dest, pivo, 0.0f, WHITE);
            
            Desenha_Fantasmas(ctx->Sprite_Explosao, source, ctx->explosoes[i].pos, TAMANHO_ASTEROIDE, pivo, 0.0f);
        }
    }
}



///////////////////////////////////////////////
// FUNCOES PRO GAMEOVER
///////////////////////////////////////////////


// funcao chamada quando o jogador perde todas as vidas
void GameOver(Contextos_Jogo *ctx, GameState *estado) {

    Atualiza_Ranking(ctx);

    ShowCursor();
    EnableCursor();

    ctx->frame_gameover = 0;
    ctx->contador_gameover = 0;
    ctx->gameover_em_loop = false;

    ctx->opcao_selecionada = 0; 
    *estado = GAME_OVER;
}


void Atualiza_Animacao_GameOver(Contextos_Jogo *ctx) {
    int velocidade = 8; // quantos frames dura cada sprite

    ctx->contador_gameover++;
    
    if (ctx->contador_gameover >= velocidade) {
        ctx->frame_gameover++;
        ctx->contador_gameover = 0;

        // se ainda ta na primeira parte da animacao,
        //  que nao é ciclica (índices 0 a 12)
        if (ctx->gameover_em_loop == false) {
            if (ctx->frame_gameover > 12) {
                ctx->gameover_em_loop = true; // ativa a parte 2 (ciclica)
                ctx->frame_gameover = 14;     // pula para o primeiro sprite do loop
            }
        } 
        // Se já está no loop (indices 14 a 19)
        else {
            if (ctx->frame_gameover > 19) {
                ctx->frame_gameover = 14; // volta pro início do loop
            }
        }
    }
}

void Desenha_Animacao_GameOver(Contextos_Jogo *ctx) {
    
    // ANIMACAO
    // sprite é 200x250
    float largura_frame = 200.0f; 
    float altura_frame = 250.0f;
    
    Rectangle source = { 
        ctx->frame_gameover * largura_frame, 
        0, 
        largura_frame, 
        altura_frame 
    };
    // aumenta a imagem em 1.5x
    float escala = 1.5f; 
    
    // centraliza no eixo x
    Rectangle dest = { 
        (LARGURA_TELA / 2) - ((largura_frame * escala) / 2), 
        0, // comeca no y=0
        largura_frame * escala, 
        altura_frame * escala 
    };
    // tanto faz o pivo
    Vector2 pivo = { 0, 0 };
    DrawTexturePro(ctx->Sprite_GameOver, source, dest, pivo, 0.0f, WHITE);

    // desenha a pontuacao
    char texto_pontuacao[50];
    sprintf(texto_pontuacao, "PONTUAÇÃO FINAL: %06d", ctx->pontuacao);
    Desenha_Texto_Centralizado(texto_pontuacao, ALTURA_TELA / 2 + 150, 30, WHITE);
    
    // desenha o botao de voltar se ja esta em loop
    if (ctx->gameover_em_loop == true) {
        Desenha_Texto_Centralizado("PRESSIONE ENTER PARA VOLTAR", ALTURA_TELA - 100, 25, WHITE);
    }
}



/////////////////////////
// VITORIA
/////////////////////////


// funcao chamada quando o jogador vence todas fases
void Vitoria(Contextos_Jogo *ctx, GameState *estado) {
    // da pra editar e fazer aparecer uma tela de vitoria
    // por enquanto, vou deixar so como uma mudanca de estado pro menu inicial]

    int bonus = 0;
    // tempo ideal é destruir 1 asteroide a cada 2s (2x o tempo de reload)
    // ve quanto que sobrou do tempo ideal
    int tempo_sobra = (ctx->asteroides_destruidos * 120) - ctx->frames_jogados;
    
    // cada segundo de sobra vale 100 pontos
    if (tempo_sobra > 0) {bonus = tempo_sobra * 100;}
    
    // soma na pontuação final
    ctx->pontuacao += bonus;
    Atualiza_Ranking(ctx);

    ShowCursor();
    EnableCursor();

    ctx->opcao_selecionada = 0; 
    *estado = VITORIA;
}

void Desenha_Tela_Vitoria(Contextos_Jogo *ctx) {

    Desenha_Texto_Centralizado("VOCÊ VENCEU!", ALTURA_TELA / 2 - 100, 100, WHITE);
    
    // desenha a pontuacao
    char texto_pontuacao[50];
    sprintf(texto_pontuacao, "PONTUAÇÃO FINAL: %06d", ctx->pontuacao);
    Desenha_Texto_Centralizado(texto_pontuacao, ALTURA_TELA / 2 + 150, 30, WHITE);
    
    // desenha o botao de voltar 
    Desenha_Texto_Centralizado("PRESSIONE ENTER PARA VOLTAR", ALTURA_TELA - 100, 25, WHITE);
}