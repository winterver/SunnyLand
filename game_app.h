#pragma once
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct MIX_Mixer;

class Time;
class ResourceManager;

class GameApp
{
    struct LibSDL { bool success = false; LibSDL(); ~LibSDL(); } libsdl_;
    struct LibTTF { bool success = false; LibTTF(); ~LibTTF(); } libttf_;
    struct LibMIX { bool success = false; LibMIX(); ~LibMIX(); } libmix_;

    struct WindowDeleter { void operator()(SDL_Window* window) const; };
    struct RendererDeleter { void operator()(SDL_Renderer* renderer) const; };
    struct MixerDeleter { void operator()(MIX_Mixer* mixer) const; };

    std::unique_ptr<SDL_Window, WindowDeleter> window_;
    std::unique_ptr<SDL_Renderer, RendererDeleter> renderer_;
    std::unique_ptr<MIX_Mixer, MixerDeleter> mixer_;

    std::unique_ptr<Time> time_;
    std::unique_ptr<ResourceManager> resource_manager_;

    bool is_running_ = false;

public:
    GameApp();
    ~GameApp();

    GameApp(GameApp&) = delete;
    GameApp(GameApp&&) = delete;
    GameApp& operator=(GameApp&) = delete;
    GameApp& operator=(GameApp&&) = delete;

    int run();

private:
    void update(float delta_time);
    void render();
};