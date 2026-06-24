#include "raylib.h"
#include "prototypes.h"

void Carregar_Som(Som *ctx){
    ctx->logo_sound = LoadSound("sound/LOGO.wav");
    ctx->theme_sound = LoadMusicStream("sound/theme_song.wav");
    ctx->missile_sound = LoadSound("sound/missile.wav");
    ctx->engine = LoadMusicStream("sound/engine.wav");
    ctx->explosion_sound = LoadSound("sound/explosion_real.wav");
    ctx->menu_sound = LoadMusicStream("sound/menu_song.wav");
}

void Descarrega_Som(Som *ctx){
    UnloadSound(ctx->logo_sound);
    UnloadMusicStream(ctx->theme_sound);
    UnloadSound(ctx->missile_sound);
    UnloadMusicStream(ctx->engine);
    UnloadSound(ctx->explosion_sound);
    UnloadMusicStream(ctx->menu_sound);
}