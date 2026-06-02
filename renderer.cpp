#include "renderer.h"
#include "sprite.h"
#include <SDL3/SDL_render.h>

Renderer::Renderer(SDL_Renderer* renderer)
    : renderer_(renderer) { }

void Renderer::drawSprite(const Sprite* sprite, float x, float y)
{
    SDL_FRect dst = { x, y, sprite->getRect()->w, sprite->getRect()->h };
    auto flip = sprite->isFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderTextureRotated(renderer_, sprite->getTexture(), sprite->getRect(), &dst, 0, nullptr, flip);
}