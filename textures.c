#include "raylib.h"
#include "prototypes.h"

void Carregar_Texturas(Contextos_Jogo *ctx) {
    ctx->Nave = LoadTexture("sprites/nave.png");
    SetTextureFilter(ctx->Nave, TEXTURE_FILTER_POINT);
    
    ctx->pivo_nave = (Vector2){ 32, 32 };
    ctx->pivo_barra = (Vector2){32, 2.5};
    
    ctx->Nave_Propulsor = LoadTexture("sprites/nave_propulsor.png");
    SetTextureFilter(ctx->Nave_Propulsor, TEXTURE_FILTER_POINT);

    ctx->Asteroid_1 = LoadTexture("sprites/full_asteroid.png");
    SetTextureFilter(ctx->Asteroid_1, TEXTURE_FILTER_POINT);

    ctx->Asteroid_2 = LoadTexture("sprites/full_asteroid_2.png");
    SetTextureFilter(ctx->Asteroid_2, TEXTURE_FILTER_POINT);

    ctx->Asteroid_3 = LoadTexture("sprites/full_asteroid_3.png");
    SetTextureFilter(ctx->Asteroid_3, TEXTURE_FILTER_POINT);

    ctx->Pink_Arrow = LoadTexture("sprites/pink_arrow.png");
    SetTextureFilter(ctx->Pink_Arrow, TEXTURE_FILTER_POINT);

    ctx->Projetil = LoadTexture("sprites/projectile.png");
    SetTextureFilter(ctx-> Projetil, TEXTURE_FILTER_POINT);

    ctx->Barra_Carregamento = LoadTexture("sprites/barra_carregamento_6_frames.png");
    SetTextureFilter(ctx-> Barra_Carregamento, TEXTURE_FILTER_POINT);
}

void Descarregar_Texturas(Contextos_Jogo *ctx){
    UnloadTexture(ctx->Nave);
    UnloadTexture(ctx->Nave_Propulsor);
    UnloadTexture(ctx->Asteroid_1);
    UnloadTexture(ctx->Asteroid_2);
    UnloadTexture(ctx->Asteroid_3);
    UnloadTexture(ctx->Pink_Arrow);
    UnloadTexture(ctx->Projetil);
    UnloadTexture(ctx->Barra_Carregamento);
}