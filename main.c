#include "raylib.h"
#include "prototypes.h"
#include <math.h>


int main(void){
    //Incialização
    GameState estado_atual = LOGO;
    int temporizador_logo = 0;

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Asteroidz_Remake");
    SetExitKey(KEY_NULL); // Impede que a tecla ESC feche o jogo
    SetTargetFPS(60);

    //Carrega o Struct com as "infos" do jogo
    Contextos_Jogo jogo = { 0 };

    //Carrega todas as texturas de uma vez
    Carregar_Texturas(&jogo);
    
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

     
    while (!WindowShouldClose() && estado_atual != SAIR)
    {
        switch (estado_atual)
        {
            case LOGO:
                Atualizar_Logo(&estado_atual, &temporizador_logo);
                break;

            case MENU:
                Escolhe_Menu(&jogo.opcao_selecionada, &estado_atual);
                Atualiza_Seta(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao_seta);
                break;

            case JOGANDO:
                HideCursor();
                DisableCursor();
                Gira_Nave(&jogo.angulo_nave);
                Acelera_Nave(&jogo.vel_x_nave, &jogo.vel_y_nave, &jogo.pos_x_nave, &jogo.pos_y_nave, &jogo.angulo_nave);
                Limites_Nave(&jogo.pos_x_nave, &jogo.pos_y_nave);
                Atualiza_Nave(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao);

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
        CloseWindow();
        return 0;
}
    
