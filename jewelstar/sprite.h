#pragma once
#include <string>
#include <SDL3/SDL_rect.h>

struct SDL_Texture;

class Content;

class Sprite
{
    SDL_Texture* texture_;
    SDL_FRect rect_;

public:
    Sprite(Content* content, const std::string& path);
    Sprite(Content* content, const std::string& path, SDL_FRect rect);

    SDL_Texture* getTexture() const;
    void setRect(const SDL_FRect& rect);
    const SDL_FRect* getRect() const;
};