/*
Arquivo principal do jogo. Carrega a biblioteca raylib e os 
prototipos das funções e controla as transiçoes entre estados 
e todos passos do loop. 
*/

#include "raylib.h"
#include "prototypes.h"
#include <math.h>

/*
Tarefas:
Fazer o struct da fase com base no que ta no documento
Fazer os níveis com base nos structs
Fazer uma função pra desenhar e mover os asteroides
Fazer a nave ter colisão com os asteroides e perder uma vida
Fazer as 3 vidas do jogo
Fazer os mísseis terem colisão com os asteroides e destruir eles
Fazer o player poder salvar o jogo em um documento de txt com base no nível que ele ta e salvar em um dos slots
Carregar o jogo pelos slots de save
Fazer o menu de save igual o de load
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
    
    //Variáveis de inicialização
    jogo.player.pos_x = LARGURA_TELA / 2;
    jogo.player.pos_y = ALTURA_TELA / 2;
    jogo.player.vel_x = 0.0f;
    jogo.player.vel_y = 0.0f;
    jogo.player.angulo = 0.0f;
    jogo.player.vidas = 3;
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

                Escolhe_Menu(&som.theme_sound, &jogo.opcao_selecionada, &estado_atual);
                Atualiza_Seta(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao_seta);
                break;

            case JOGANDO:
                HideCursor();
                DisableCursor();
                Move_Cenario(&parallax.nebulosa_pos_y, &parallax.nebulosa_pos_x, &jogo.player.vel_x, &jogo.player.vel_y, 0.2f);
                Move_Cenario(&parallax.estrelas_menores_pos_y, &parallax.estrelas_menores_pos_x, &jogo.player.vel_x, &jogo.player.vel_y, 0.4f);
                Move_Cenario(&parallax.estrelas_maiores_pos_y, &parallax.estrelas_maiores_pos_x, &jogo.player.vel_x, &jogo.player.vel_y, 0.6f);
                Atualiza_Barra(jogo.contador, &jogo.frames_barra);
                Gira_Nave(&jogo.player.angulo);
                Som_Motor(som.engine, &som.marcador_som_engine, &som.volume_engine);
                Acelera_Nave(&jogo.player.vel_x, &jogo.player.vel_y, &jogo.player.pos_x, &jogo.player.pos_y, &jogo.player.angulo);
                Aplica_Limites_Circulares(&jogo.player.pos_x, &jogo.player.pos_y, TAMANHO_NAVE);
                Atualiza_Nave(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao);
                Atira_Nave(som.missile_sound, &jogo.contador, jogo.tiros, jogo.player.pos_x, jogo.player.pos_y, jogo.player.angulo);
                Atualiza_Asteroides(&jogo);
                
                //Entra no meu de pausa se apertar ESC
                if(IsKeyPressed(KEY_ESCAPE)){
                    ShowCursor();
                    EnableCursor();
                    estado_atual = PAUSE; // Muda para o estado de pausa
                }
                break;

            case SAVE:
                Sai_Menu(&estado_atual, PAUSE);
                Escolhe_Slot(&jogo.opcao_selecionada, &estado_atual, PAUSE);
                break;

            case LOAD_IN_GAME:
                Sai_Menu(&estado_atual, PAUSE);
                Escolhe_Slot(&jogo.opcao_selecionada, &estado_atual, PAUSE);
                break;

            case PAUSE:
                Escolhe_Menu_Pausa(&jogo.opcao_selecionada, &estado_atual);
                Atualiza_Seta(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao_seta);
                Despausar_Jogo(&estado_atual); // Chama a função para checar se deve despausar
                break;

            case LOAD_OUT_GAME:
                Sai_Menu(&estado_atual, MENU);
                Escolhe_Slot(&jogo.opcao_selecionada, &estado_atual, MENU);
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
                    Desenha_Cenario(jogo.Nebulosa, &parallax.nebulosa_pos_x, &parallax.nebulosa_pos_y);
                    Desenha_Cenario(jogo.Estrelas_Menores, &parallax.estrelas_menores_pos_x, &parallax.estrelas_menores_pos_y);
                    Desenha_Cenario(jogo.Estrelas_Maiores, &parallax.estrelas_maiores_pos_x, &parallax.estrelas_maiores_pos_y);
                    Desenha_Nave(&som.marcador_som_engine, &jogo.player.angulo, jogo.Nave, jogo.Nave_Propulsor, &jogo.frame_atual, jogo.pivo_nave, &jogo.player.pos_x, &jogo.player.pos_y);
                    Atualiza_Tiro(&jogo.frame_atual, jogo.tiros, jogo.Projetil, jogo.pivo_projetil);
                    Desenha_Barra(&jogo.frames_barra,jogo.pivo_barra, jogo.Barra_Carregamento);
                    Desenha_Asteroides(&jogo);

                    break;

                case SAVE:
                    Desenha_Menu_Slots(&jogo.opcao_selecionada, "SAVE GAME");
                    break;

                case LOAD_IN_GAME:
                    Desenha_Menu_Slots(&jogo.opcao_selecionada, "LOAD GAME");
                    break;

                case PAUSE: //Menu de pausa, ainda não sei se tudo vai ser perdido se pausar o jogo
                    Desenha_Menu_Pausa(&jogo.opcao_selecionada);
                    Desenha_Seta_Menu_Pausa(&jogo.frame_atual, &jogo.opcao_selecionada, jogo.Pink_Arrow, jogo.pivo_seta);
                 break;

                case LOAD_OUT_GAME:
                    Desenha_Menu_Slots(&jogo.opcao_selecionada, "LOAD GAME");
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
    
