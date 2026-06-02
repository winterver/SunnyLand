#include "sprite.h"
#include "resource_manager.h"
#include <SDL3/SDL_render.h>

Sprite::Sprite(ResourceManager* resource_manager, const std::string& path, bool flipped)
    : resource_manager_(resource_manager), rect_({}), flipped_(flipped)
{
    texture_ = resource_manager->getTexture(path);
    SDL_GetTextureSize(texture_, &rect_.w, &rect_.h);
}

Sprite::Sprite(ResourceManager* resource_manager, const std::string& path, SDL_FRect rect, bool flipped)
    : Sprite(resource_manager, path, flipped) { rect_ = rect; }

ResourceManager* Sprite::getResourceManager() const { return resource_manager_; }
SDL_Texture* Sprite::getTexture() const { return texture_; }

void Sprite::setRect(const SDL_FRect& rect) { rect_ = rect; }
const SDL_FRect* Sprite::getRect() const { return &rect_; }

void Sprite::setFlipped(bool flipped) { flipped_ = flipped; }
bool Sprite::isFlipped() const { return flipped_; }