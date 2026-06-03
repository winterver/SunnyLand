#include "sprite.h"
#include "content.h"
#include <SDL3/SDL_render.h>

Sprite::Sprite(Content* content, const std::string& path)
    : texture_(content->getTexture(path)), rect_({})
{
    SDL_GetTextureSize(texture_, &rect_.w, &rect_.h);
}

Sprite::Sprite(Content* content, const std::string& path, SDL_FRect rect)
    : Sprite(content, path) { rect_ = rect; }

SDL_Texture* Sprite::getTexture() const { return texture_; }
void Sprite::setRect(const SDL_FRect& rect) { rect_ = rect; }
const SDL_FRect* Sprite::getRect() const { return &rect_; }