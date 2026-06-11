#include "raylib.h"
#include "prototypes.h"
#include <math.h>


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

    //Carrega todas as texturas de uma vez
    Carregar_Texturas(&jogo);
    Carregar_Som(&som);
    
    //Variáveis de inicialização
    jogo.angulo_nave = 0.0f;
    jogo.frame_atual = 0;
    jogo.contador_tempo = 0;
    jogo.velocidade_animacao = 10;
    jogo.opcao_selecionada = 0;
    jogo.velocidade_animacao_seta = 5;
    jogo.pos_x_nave = LARGURA_TELA / 2;
    jogo.pos_y_nave = ALTURA_TELA / 2;
    jogo.vel_x_nave = 0.0f;
    jogo.vel_y_nave = 0.0f;
    jogo.contador = 60;
    jogo.frames_barra = 5;
    jogo.temporizador_logo = 0;
     
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

                Escolhe_Menu(&som.theme_sound, &jogo.opcao_selecionada, &estado_atual);
                Atualiza_Seta(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao_seta);
                break;

            case JOGANDO:
                HideCursor();
                DisableCursor();
                Atualiza_Barra(jogo.contador, &jogo.frames_barra);
                Gira_Nave(&jogo.angulo_nave);
                Acelera_Nave(&jogo.vel_x_nave, &jogo.vel_y_nave, &jogo.pos_x_nave, &jogo.pos_y_nave, &jogo.angulo_nave);
                Limites_Nave(&jogo.pos_x_nave, &jogo.pos_y_nave);
                Atualiza_Nave(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao);
                Atira_Nave(&jogo.contador, jogo.tiros, jogo.pos_x_nave, jogo.pos_y_nave, jogo.angulo_nave);
                
                //Entra no meu de pausa se apertar ESC
                if(IsKeyPressed(KEY_ESCAPE)){
                    ShowCursor();
                    EnableCursor();
                    estado_atual = PAUSE; // Muda para o estado de pausa
                }
                break;

            case SAVE:
                Sai_Menu(&estado_atual, PAUSE);
                break;

            case LOAD_IN_GAME:
                Sai_Menu(&estado_atual, PAUSE);
                Escolhe_Load_In_Game(&jogo.opcao_selecionada, &estado_atual);

                break;
            


            case PAUSE:
                Escolhe_Menu_Pausa(&jogo.opcao_selecionada, &estado_atual);
                Atualiza_Seta(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao_seta);
                Despausar_Jogo(&estado_atual); // Chama a função para checar se deve despausar
                break;

            case LOAD_OUT_GAME:
                Sai_Menu(&estado_atual, MENU);
                Escolhe_Load_Out_Game(&jogo.opcao_selecionada, &estado_atual);

                break;

            case BEST_SCORES:
                Sai_Menu(&estado_atual, MENU);
                break;
        }

        BeginDrawing();
        ClearBackground(BLACK);

            switch (estado_atual)
            {
                case LOGO: //Desenha a tela de "launch" do game
                    Desenha_Texto_Centralizado("ASTEROIDZ REMAKE", (ALTURA_TELA / 2) - 25, 60, WHITE);
                    break;
                 
                case MENU: //É o menu... é só isso mesmo
                    Desenha_Menu_Principal(&jogo.opcao_selecionada);
                    Desenha_Seta_Menu_Principal(&jogo.frame_atual, &jogo.opcao_selecionada, jogo.Pink_Arrow, jogo.pivo_seta);
                    
                    break;

                case JOGANDO://Aqui tem que trabalhar a aparência do jogo e o jogo xD
                    Anima_Propulsor(&jogo.angulo_nave, jogo.Nave, jogo.Nave_Propulsor, &jogo.frame_atual, jogo.pivo_nave, &jogo.pos_x_nave, &jogo.pos_y_nave);
                    Atualiza_Tiro(&jogo.frame_atual, jogo.tiros, jogo.Projetil, jogo.pivo_projetil);
                    Desenha_Barra(&jogo.frames_barra,jogo.pivo_barra, jogo.Barra_Carregamento);
                    break;

                case SAVE:
                    break;

                case LOAD_IN_GAME:
                    Desenha_Load(&jogo.opcao_selecionada);
                    break;

                case PAUSE: //Menu de pausa, ainda não sei se tudo vai ser perdido se pausar o jogo
                    Desenha_Menu_Pausa(&jogo.opcao_selecionada);
                    Desenha_Seta_Menu_Pausa(&jogo.frame_atual, &jogo.opcao_selecionada, jogo.Pink_Arrow, jogo.pivo_seta);
                 break;

                case LOAD_OUT_GAME:
                    Desenha_Load(&jogo.opcao_selecionada);
                    break;

                case BEST_SCORES:

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
    
