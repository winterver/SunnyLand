#include "sprite.h"
#include "resource_manager.h"
#include <SDL3/SDL_render.h>

Sprite::Sprite(ResourceManager* resource_manager, const std::string& path)
    : texture_(resource_manager->getTexture(path)), rect_({})
{
    SDL_GetTextureSize(texture_, &rect_.w, &rect_.h);
}

Sprite::Sprite(ResourceManager* resource_manager, const std::string& path, SDL_FRect rect)
    : Sprite(resource_manager, path) { rect_ = rect; }

SDL_Texture* Sprite::getTexture() const { return texture_; }
void Sprite::setRect(const SDL_FRect& rect) { rect_ = rect; }
const SDL_FRect* Sprite::getRect() const { return &rect_; }