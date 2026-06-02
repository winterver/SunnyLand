#pragma once
#include <string>
#include <SDL3/SDL_rect.h>

class ResourceManager;

struct SDL_Texture;

class Sprite
{
    ResourceManager* resource_manager_;
    SDL_Texture* texture_;
    SDL_FRect rect_;
    bool flipped_;

public:
    Sprite(ResourceManager* resource_manager, const std::string& path, bool flipped = false);
    Sprite(ResourceManager* resource_manager, const std::string& path, SDL_FRect rect, bool flipped = false);

    ResourceManager* getResourceManager() const;
    SDL_Texture* getTexture() const;

    void setRect(const SDL_FRect& rect);
    const SDL_FRect* getRect() const;

    void setFlipped(bool flipped);
    bool isFlipped() const;
};