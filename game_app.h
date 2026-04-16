#pragma once
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct MIX_Mixer;

class Time;
class ResourceManager;

class GameApp
{
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    MIX_Mixer* mixer_ = nullptr;
    bool is_running_ = false;

    std::unique_ptr<Time> time_;
    std::unique_ptr<ResourceManager> resource_manager_;

public:
    GameApp();
    ~GameApp();

    GameApp(GameApp&) = delete;
    GameApp(GameApp&&) = delete;
    GameApp& operator=(GameApp&) = delete;
    GameApp& operator=(GameApp&&) = delete;

    int run();

private:
    void handleEvents();
    void update(float delta_time);
    void render();
};