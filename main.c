#include "raylib.h"
#include "prototypes.h"


int main(void){
    //Incialização
    const int largura_tela = 1200;
    const int altura_tela = 800;
    
    GameState estado_atual = LOGO;
    int temporizador_logo = 0;

    InitWindow(largura_tela, altura_tela, "Asteroidz_Remake");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        switch (estado_atual)
        {
            case LOGO:
                AtualizarLogo(&estado_atual, &temporizador_logo);
                break;
            case MENU:
                AtualizarMenu(&estado_atual);
                break;
            case JOGANDO:
                if (IsKeyPressed(KEY_SPACE)) {
                    estado_atual = LOGO; // Reinicia para demonstração
                    temporizador_logo = 0;
                }
        }
        {
        BeginDrawing();
        ClearBackground(BLACK);

            switch (estado_atual)
            {
                case LOGO:
                    int tamanho_fonte = 50;
                    const char* titulo = "ASTEROIDZ REMAKE";
                    int largura_texto = MeasureText(titulo, tamanho_fonte);

                    DrawText(titulo, (largura_tela / 2) - (largura_texto / 2), (altura_tela / 2) - (tamanho_fonte / 2), tamanho_fonte, WHITE);
                    break;

                case MENU:
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

                    // BEST SCORES
                    const char* texto_scores = "BEST SCORES";
                    int largura_scores = MeasureText(texto_scores, tamanho_opcao);
                    DrawText(texto_scores, (largura_tela / 2) - (largura_scores / 2), inicio_y_opcoes + espacamento, tamanho_opcao, WHITE);

                    // EXIT
                    const char* texto_exit = "EXIT";
                    int largura_exit = MeasureText(texto_exit, tamanho_opcao);
                    DrawText(texto_exit, (largura_tela / 2) - (largura_exit / 2), inicio_y_opcoes + (espacamento * 2), tamanho_opcao, WHITE);
                        break;

                case JOGANDO:
                    DrawText("Jogo Rodando (Aperte Espaço para reiniciar)", largura_tela/2 - 200, altura_tela/2 - 20, 30, WHITE);
                    break;

            }

        EndDrawing();
        }   

    }
    CloseWindow();
    return 0; 
}
