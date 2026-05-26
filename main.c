#include "raylib.h"
#include "prototypes.h"


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

     
    while (!WindowShouldClose())
    {
        switch (estado_atual)
        {
            case LOGO:
                Atualizar_Logo(&estado_atual, &temporizador_logo);
                break;

            case MENU:
                Atualizar_Menu(&estado_atual);
                break;

            case JOGANDO:
                HideCursor();
                DisableCursor();
                Gira_Nave(&jogo.angulo_nave);
                Atualiza_Nave(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao);

                //Entra no meu de pausa de aperta ESC
                if(IsKeyPressed(KEY_ESCAPE)){
                    ShowCursor();
                    EnableCursor();
                    estado_atual = PAUSE; // Muda para o estado de pausa
                }
                break;

            case PAUSE:
                Pausar_Jogo(&estado_atual); // Chama a função para checar se deve despausar
                break;
        }

        BeginDrawing();
        ClearBackground(BLACK);

            switch (estado_atual)
            {
                case LOGO: //Desenha a tela de "launch" do game
                    Desenha_Texto_Centralizado("ASTEROIDZ REMAKE", (ALTURA_TELA / 2) - 25, 50, WHITE);
                    break;
                 
                case MENU: //É o menu... é só isso mesmo
                    Desenha_Menu_Principal();
                    break;

                case JOGANDO://Aqui tem que trabalhar a aparência do jogo e o jogo xD
                    Rectangle nave_hitbox_source = {jogo.frame_atual * 64, 0, 64, 64 };
                    Rectangle nave_hitbox_dest = { LARGURA_TELA / 2, ALTURA_TELA / 2, 64, 64 };
                    DrawTexturePro(jogo.Nave, nave_hitbox_source, nave_hitbox_dest, jogo.pivo_nave, jogo.angulo_nave, WHITE);
                    break;

                case PAUSE: //Menu de pausa, ainda não sei se tudo vai ser perdido se pausar o jogo
                    Desenha_Menu_Pausa();
                 break;
            }
        EndDrawing();
    }
    Descarregar_Texturas(&jogo);
    CloseWindow();
    return 0; 
    }
    
