#pragma once

struct SDL_Renderer;

class Sprite;

class Renderer
{
    SDL_Renderer* renderer_;

public:
    Renderer(SDL_Renderer* renderer);

    Renderer(Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void drawSprite(const Sprite* sprite, float x, float y);
};