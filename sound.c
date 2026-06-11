#include "raylib.h"
#include "prototypes.h"

void Carregar_Som(Som *ctx){
    ctx->logo_sound = LoadSound("sound/LOGO.wav");
    ctx->theme_sound = LoadMusicStream("sound/theme.wav");
}

void Descarrega_Som(Som *ctx){
    UnloadSound(ctx->logo_sound);
    UnloadMusicStream(ctx->theme_sound);
}