#include "raylib.h"
#include "prototypes.h"

void Carregar_Texturas(Contextos_Jogo *ctx) {
    ctx->Nave = LoadTexture("sprites/nave.png");
    SetTextureFilter(ctx->Nave, TEXTURE_FILTER_POINT);
    
    ctx->pivo_nave = (Vector2){ 16, 16 };
    
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
}

void Descarregar_Texturas(Contextos_Jogo *ctx){
    UnloadTexture(ctx->Nave);
    UnloadTexture(ctx->Asteroid_1);
    UnloadTexture(ctx->Asteroid_2);
    UnloadTexture(ctx->Asteroid_3);

}