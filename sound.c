/*
Arquivo especifico para definicao de funcoes de audio
*/

#include "raylib.h"
#include "prototypes.h"

void Carregar_Som(Som *ctx){
    ctx->logo_sound = LoadSound("sound/LOGO.mp3");
    ctx->theme_sound = LoadMusicStream("sound/theme_song.mp3");
    ctx->missile_sound = LoadSound("sound/missile.mp3");
    ctx->engine = LoadMusicStream("sound/engine.mp3");
    ctx->explosion_sound = LoadSound("sound/explosion_real.mp3");
    ctx->menu_sound = LoadMusicStream("sound/menu_song.mp3");
}

void Descarrega_Som(Som *ctx){
    UnloadSound(ctx->logo_sound);
    UnloadMusicStream(ctx->theme_sound);
    UnloadSound(ctx->missile_sound);
    UnloadMusicStream(ctx->engine);
    UnloadSound(ctx->explosion_sound);
    UnloadMusicStream(ctx->menu_sound);
}