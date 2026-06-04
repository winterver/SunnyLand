#include "renderer.h"
#include "game_app.h"
#include "sprite.h"
#include <SDL3/SDL_render.h>

Renderer::Renderer(GameApp* app) : renderer_(app->sdl_renderer()) { }

void Renderer::clear() { SDL_RenderClear(renderer_); }
void Renderer::present() { SDL_RenderPresent(renderer_); }

void Renderer::drawSprite(const Sprite* sprite, float x, float y)
{
    SDL_FRect dst = { x, y, sprite->getRect()->w, sprite->getRect()->h };
    SDL_RenderTextureRotated(renderer_, sprite->getTexture(), sprite->getRect(), &dst, 0, nullptr, SDL_FLIP_NONE);
}