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
    jogo.opcao_selecionada = 0;

     
    while (!WindowShouldClose() && estado_atual != SAIR)
    {
        switch (estado_atual)
        {
            case LOGO:
                Atualizar_Logo(&estado_atual, &temporizador_logo);
                break;

            case MENU:
                Atualizar_Menu(&estado_atual);
                Escolhe_Menu(&jogo.opcao_selecionada, &estado_atual);
                break;

            case JOGANDO:
                HideCursor();
                DisableCursor();
                Gira_Nave(&jogo.angulo_nave);
                Atualiza_Nave(&jogo.frame_atual, &jogo.contador_tempo, jogo.velocidade_animacao);

                //Entra no meu de pausa se apertar ESC
                if(IsKeyPressed(KEY_ESCAPE)){
                    ShowCursor();
                    EnableCursor();
                    estado_atual = PAUSE; // Muda para o estado de pausa
                }
                break;

            case PAUSE:
                Escolhe_Menu_Pausa(&jogo.opcao_selecionada, &estado_atual);
                Despausar_Jogo(&estado_atual); // Chama a função para checar se deve despausar
                break;

            case SAVE:
                
                break;

            case LOAD:

                break;

            case BEST_SCORES:

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
                    Desenha_Menu_Principal(&jogo.opcao_selecionada);
                    int inicio_y = (ALTURA_TELA / 2) + 60;
                    
                    switch(jogo.opcao_selecionada){//tem que dar um jeito de empurrar isso dentro de uma função mas ta tarde
                        case 0://seta apontando para o start
                            DrawTexture(jogo.Pink_Arrow, (LARGURA_TELA / 2) - (MeasureText("LOAAD", 30)), inicio_y, WHITE);
                            break;

                        case 1://seta apontando para o load
                            DrawTexture(jogo.Pink_Arrow, (LARGURA_TELA / 2) - (MeasureText("LOAD", 30)), inicio_y + 50, WHITE);
                            break;

                        case 2://seta apontando para o best scores
                            DrawTexture(jogo.Pink_Arrow, (LARGURA_TELA / 2) - (MeasureText("LOADLOAA", 30)), inicio_y + 100, WHITE);
                            break;

                        case 3://seta apontando para o exit
                            DrawTexture(jogo.Pink_Arrow, (LARGURA_TELA / 2) - (MeasureText("EXIT", 30)), inicio_y + 150, WHITE);
                            break;
                    }
                    break;

                case JOGANDO://Aqui tem que trabalhar a aparência do jogo e o jogo xD
                    Rectangle nave_hitbox_source = {jogo.frame_atual * 64, 0, 64, 64 };
                    Rectangle nave_hitbox_dest = { LARGURA_TELA / 2, ALTURA_TELA / 2, 64, 64 };
                    DrawTexturePro(jogo.Nave, nave_hitbox_source, nave_hitbox_dest, jogo.pivo_nave, jogo.angulo_nave, WHITE);
                    break;

                case PAUSE: //Menu de pausa, ainda não sei se tudo vai ser perdido se pausar o jogo
                    Desenha_Menu_Pausa(&jogo.opcao_selecionada);
                 break;

                case SAVE:
                
                    break;

                case LOAD:

                    break;

                case BEST_SCORES:

                    break;
            }
        EndDrawing();
    }
    
    }
    
