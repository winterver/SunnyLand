#pragma once

struct SDL_Renderer;

class GameApp;
class Sprite;

class Renderer
{
    SDL_Renderer* renderer_;

public:
    Renderer(GameApp* app);

    Renderer(Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void clear();
    void present();

    void drawSprite(const Sprite* sprite, float x, float y);
};