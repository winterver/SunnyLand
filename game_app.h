#pragma once
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
class Time;

class GameApp
{
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    bool is_running_ = false;

    std::unique_ptr<Time> time_;

public:
    GameApp();
    ~GameApp();

    GameApp(GameApp&) = delete;
    GameApp(GameApp&&) = delete;
    GameApp& operator=(GameApp&) = delete;
    GameApp& operator=(GameApp&&) = delete;

    void run();

private:
    bool init();
    void close();
    void handleEvents();
    void update(float delta_time);
    void render();
};