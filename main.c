#include "raylib.h"
#include "prototypes.h"


int main(void){
    //Incialização
    const int largura_tela = 1200;//constate interior é considerado variável global?
    const int altura_tela = 800;
 
    GameState estado_atual = LOGO;
    int temporizador_logo = 0;

    InitWindow(largura_tela, altura_tela, "Asteroidz_Remake");
    SetExitKey(KEY_NULL); // Impede que a tecla ESC feche o jogo
    SetTargetFPS(60);

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
                case LOGO: {//Desenha a tela de "launch" do game
                    int tamanho_fonte = 50;
                    const char* titulo = "ASTEROIDZ REMAKE";
                    int largura_texto = MeasureText(titulo, tamanho_fonte);//Em todos os Measure el vai definir o tamanho total do texto naquele tamanhho de fonte pra alinhar

                    DrawText(titulo, (largura_tela / 2) - (largura_texto / 2), (altura_tela / 2) - (tamanho_fonte / 2), tamanho_fonte, WHITE);
                } break;

                case MENU: {//É o meny... é só isso mesmo
                    int tamanho_titulo = 60;
                    const char* texto_titulo = "MAIN MENU";
                    int largura_titulo = MeasureText(texto_titulo, tamanho_titulo);

                    DrawText(texto_titulo, (largura_tela / 2) - (largura_titulo / 2), altura_tela / 4, tamanho_titulo, WHITE);

                    int tamanho_opcao = 30;
                    int espacamento = 50;

                    int inicio_y_opcoes = (altura_tela / 2) + 60;

                    // START
                    const char* texto_start = "START";
                    int largura_start = MeasureText(texto_start, tamanho_opcao);
                    DrawText(texto_start, (largura_tela / 2) - (largura_start / 2), inicio_y_opcoes, tamanho_opcao, WHITE);

                    // LOAD
                    const char* texto_load = "LOAD";
                    int largura_load = MeasureText(texto_load, tamanho_opcao);
                    DrawText(texto_load, (largura_tela / 2) - (largura_load / 2), inicio_y_opcoes + espacamento, tamanho_opcao, WHITE);

                    // BEST SCORES
                    const char* texto_scores = "BEST SCORES";
                    int largura_scores = MeasureText(texto_scores, tamanho_opcao);
                    DrawText(texto_scores, (largura_tela / 2) - (largura_scores / 2), inicio_y_opcoes + (espacamento * 2), tamanho_opcao, WHITE);

                    // EXIT
                    const char* texto_exit = "EXIT";
                    int largura_exit = MeasureText(texto_exit, tamanho_opcao);
                    DrawText(texto_exit, (largura_tela / 2) - (largura_exit / 2), inicio_y_opcoes + (espacamento * 3), tamanho_opcao, WHITE);
                } break;

                case JOGANDO:{//Aqui tem que trabalhar a aparência do jogo
                    DrawText("Jogo Rodando (Aperte Espaço para reiniciar)", largura_tela/2 - 200, altura_tela/2 - 20, 30, WHITE);
                } break;

                case PAUSE: {//Menu de pausa, ainda não sei se tudo vai ser perdido se pausar o jogo
                    int tamanho_titulo = 60;
                    const char* texto_titulo = "PAUSE";
                    int largura_titulo = MeasureText(texto_titulo, tamanho_titulo);

                    DrawText(texto_titulo, (largura_tela / 2) - (largura_titulo / 2), altura_tela / 4, tamanho_titulo, WHITE);

                    int tamanho_opcao = 30;
                    int espacamento = 50;

                    int inicio_y_opcoes = (altura_tela / 2) + 60;

                    // START
                    const char* texto_resume = "RESUME";
                    int largura_resume = MeasureText(texto_resume, tamanho_opcao);
                    DrawText(texto_resume, (largura_tela / 2) - (largura_resume / 2), inicio_y_opcoes, tamanho_opcao, WHITE);

                    // LOAD
                    const char* texto_load = "LOAD";
                    int largura_load = MeasureText(texto_load, tamanho_opcao);
                    DrawText(texto_load, (largura_tela / 2) - (largura_load / 2), inicio_y_opcoes + espacamento, tamanho_opcao, WHITE);

                    // BEST SCORES
                    const char* texto_save = "SAVE";
                    int largura_save = MeasureText(texto_save, tamanho_opcao);
                    DrawText(texto_save, (largura_tela / 2) - (largura_save / 2), inicio_y_opcoes + (espacamento * 2), tamanho_opcao, WHITE);

                    // EXIT
                    const char* texto_exit = "EXIT";
                    int largura_exit = MeasureText(texto_exit, tamanho_opcao);
                    DrawText(texto_exit, (largura_tela / 2) - (largura_exit / 2), inicio_y_opcoes + (espacamento * 3), tamanho_opcao, WHITE);
                } break;
            }
        EndDrawing();
    }

    CloseWindow();
    return 0; 
    }
    
