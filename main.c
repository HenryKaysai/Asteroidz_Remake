/*
Arquivo principal do jogo. Carrega a biblioteca raylib e os 
prototipos das funções e controla as transiçoes entre estados 
e todos passos do loop. 
*/

#include "raylib.h"
#include "prototypes.h"
#include <math.h>
#include <stdio.h>

/*
Tarefas:
ESCREVER CABEÇALHOS

animacao asteroide

mensagem de morte e de vitória

modo de jogo infinito
*/

int main(void){
    //Incialização
    GameState estado_atual = LOGO;

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Asteroidz_Remake");
    SetExitKey(KEY_NULL); // Impede que a tecla ESC feche o jogo
    SetTargetFPS(60);
    InitAudioDevice();
    SetMasterVolume(0.79f);

    //Carrega o Struct com as "infos" do jogo
    Contextos_Jogo jogo = { 0 };
    Som som = {0};
    Parallax parallax = {0};
    //Carrega todas as texturas de uma vez
    Carregar_Texturas(&jogo);
    Carregar_Som(&som);
    Carrega_Ranking(&jogo);
    
    //Variáveis de inicialização
    jogo.player.pos.x = LARGURA_TELA / 2;
    jogo.player.pos.y = ALTURA_TELA / 2;
    jogo.player.vel.x = 0.0f;
    jogo.player.vel.y = 0.0f;
    jogo.player.angulo = 0.0f;
    jogo.player.vidas = 3;
    jogo.fase_atual = 1;
    jogo.frame_atual = 0;
    jogo.contador_tempo = 0;
    jogo.velocidade_animacao = 10;
    jogo.opcao_selecionada = 0;
    jogo.velocidade_animacao_seta = 5;
    jogo.contador = 60;
    jogo.frames_barra = 5;
    jogo.temporizador_logo = 0;
    som.marcador_som_engine = 0;
     
    while (!WindowShouldClose() && estado_atual != SAIR)
    {
        switch (estado_atual)
        {
            case LOGO:
                if (jogo.temporizador_logo == 0) {
                    PlaySound(som.logo_sound);
                }
                Atualizar_Logo(&estado_atual, &jogo.temporizador_logo);
                break;

            case MENU:
                if (!IsMusicStreamPlaying(som.theme_sound)){
                    PlayMusicStream(som.theme_sound);
                }
                UpdateMusicStream(som.theme_sound);

                // detecta navegacao e atualiza opcao_selecionada 
                // Navega_Menu retorna 1 se detectar mudanças
                if (Navega_Menu(&jogo.opcao_selecionada, 4, (ALTURA_TELA / 2) + 60, 50)) {

                    switch(jogo.opcao_selecionada) {
                        case 0: // START
                            StopMusicStream(som.theme_sound);
                            Resetar_Jogo(&jogo);
                            Carrega_Fase(&jogo, "fases/nivel_1.txt");
                            estado_atual = JOGANDO;
                            break;
                        case 1: // LOAD
                            estado_atual = LOAD;
                            break;
                        case 2: // BEST SCORES
                            estado_atual = BEST_SCORES;
                            break;
                        case 3: // EXIT
                            estado_atual = SAIR;
                            break;
                    }
                }
                
                Atualiza_Seta(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao_seta);
                break;

            case JOGANDO:
                HideCursor();
                DisableCursor();
                jogo.frames_jogados++;

                Move_Cenario(&parallax.nebulosa_pos, &jogo.player.vel, 0.2f);
                Move_Cenario(&parallax.estrelas_menores_pos, &jogo.player.vel, 0.4f);
                Move_Cenario(&parallax.estrelas_maiores_pos, &jogo.player.vel, 0.6f);
                
                Atualiza_Barra(jogo.contador, &jogo.frames_barra);
                Atualiza_Nave(&jogo, &som);
                Atualiza_Asteroides(&jogo); 
                Atualiza_Explosoes(&jogo);

                // detecta colisao e destroi asteroides
                Checa_Colisao_Tiro_Asteroide(&jogo, &som);

                // se o jogador nao estiver invencivel,
                if (jogo.player.tempo_invencivel <= 0) {
                    // detecta colisao da nave, tira vida e reseta posicao
                    if (Checa_Colisao_Nave_Asteroide(&jogo)) {
                        // diminui vida, confere se perdeu todas 
                        // e reseta posicao
                        Perde_Vida(&jogo, &estado_atual);
                    }
                } else { // se tiver invencivel, 
                    // diminui o timer da invencibilidade
                    jogo.player.tempo_invencivel--;
                }

                if (Checa_Fase_Concluida(&jogo) == 1) {

                    Passa_Proxima_Fase(&jogo, &estado_atual);
                    
                }
                
                //Entra no meu de pausa se apertar ESC
                if(IsKeyPressed(KEY_ESCAPE)){
                    ShowCursor();
                    EnableCursor();
                    jogo.opcao_selecionada = 0;
                    estado_atual = PAUSE; // Muda para o estado de pausa
                }
                break;

            case SAVE:
                if (!Sai_Menu(&estado_atual, PAUSE)) {
                    Escolhe_Slot(&jogo, &estado_atual, PAUSE);
                }
                break;


            case LOAD:
                // Decrescenta o timer de mensagem de erro
                if (jogo.timer_erro_load > 0) {
                    jogo.timer_erro_load--;
                }

                // testa se sairam do menu. 
                // se nao, roda logica de navegacao
                if (!Sai_Menu(&estado_atual, MENU)) {
                    Escolhe_Slot(&jogo, &estado_atual, MENU);
                }
                

                break;

            case PAUSE:
                // Detecta navegacao e atualiza opcao_selecionada 
                // Navega_Menu retorna 1 se detectar mudanças
                if (Navega_Menu(&jogo.opcao_selecionada, 4, (ALTURA_TELA / 2) + 60, 50)) {
                    switch(jogo.opcao_selecionada) {
                        case 0: // RESUME
                            estado_atual = JOGANDO;
                            HideCursor(); 
                            DisableCursor();
                            break;
                        case 1: // SAVE
                            estado_atual = SAVE;
                            break;
                        case 2: // MAIN MENU
                            estado_atual = MENU;
                            break;
                        case 3: // EXIT
                            estado_atual = SAIR;
                            break;
                    }
                }   
            
                Atualiza_Seta(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao_seta);
                Despausar_Jogo(&estado_atual); // Chama a função para checar se deve despausar
                break;

            case BEST_SCORES:
                // o jogador pode sair com esc, enter ou espaço
                if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                    estado_atual = MENU;
                    jogo.opcao_selecionada = 0;
                }
                
                // ou clicando no botão back
                Navega_Best_Scores(&jogo, &estado_atual);
                break;
        }

        BeginDrawing();
        ClearBackground(BLACK);

            switch (estado_atual)
            {
                case LOGO: //Desenha a tela de "launch" do game
                    Desenha_Texto_Centralizado("ASTEROIDZ REMAKE", (ALTURA_TELA / 2) - 25, 60, WHITE);
                    break;
                 
                case MENU: // Menu inicial
                {
                    const char* opcoes_menu[] = { "START", "LOAD", "BEST SCORES", "EXIT" };
                    Desenha_Menu("MAIN MENU", opcoes_menu, 4, jogo.opcao_selecionada);
                    Desenha_Seta_Menu(&jogo.frame_atual, &jogo.opcao_selecionada, jogo.Pink_Arrow, PIVO_SETA, opcoes_menu, 4);
                    break;
                }
                case JOGANDO://Aqui tem que trabalhar a aparência do jogo e o jogo xD
                    Desenha_Cenario(jogo.Nebulosa, parallax.nebulosa_pos);
                    Desenha_Cenario(jogo.Estrelas_Menores, parallax.estrelas_menores_pos);
                    Desenha_Cenario(jogo.Estrelas_Maiores, parallax.estrelas_maiores_pos);
                    
                    Desenha_Asteroides(&jogo);
                    Desenha_Explosoes(&jogo);
                    Desenha_Nave(&jogo, &som);
                    Atualiza_Tiro(&jogo.frame_atual, jogo.tiros, jogo.Projetil, PIVO_PROJETIL);
                    
                    // desenha barra de municao, vidas e fase atual
                    Desenha_Interface(&jogo);

                    

                    break;

                case SAVE:
                    Desenha_Menu_Slots(&jogo.opcao_selecionada, "SAVE GAME");
                    break;


                case PAUSE: 
                {   //Menu de pausa, ainda não sei se tudo vai ser perdido se pausar o jogo
                    const char* opcoes_pausa[] = { "RESUME", "SAVE", "MAIN MENU", "EXIT" };
                    Desenha_Menu("PAUSE", opcoes_pausa, 4, jogo.opcao_selecionada);
                    Desenha_Seta_Menu(&jogo.frame_atual, &jogo.opcao_selecionada, jogo.Pink_Arrow, PIVO_SETA, opcoes_pausa, 4);
                    break;
                }
                case LOAD:
                    Desenha_Menu_Slots(&jogo.opcao_selecionada, "LOAD GAME");
                    if (jogo.timer_erro_load > 0){
                        Desenha_Erro_Load_Vazia(jogo.slot_erro);
                    }
                    break;

                case BEST_SCORES:
                    Desenha_Best_Scores(&jogo);
                    break;
            }
            EndDrawing();
        }
        Descarrega_Som(&som);
        CloseAudioDevice();
        Descarregar_Texturas(&jogo);
        CloseWindow();
        return 0;
}
    
