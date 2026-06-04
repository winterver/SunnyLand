#pragma once
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct MIX_Mixer;

class Content;
class Renderer;
class Time;
class Scene;

class GameApp
{
    struct LibSDL { bool success = false; LibSDL(); ~LibSDL(); } libsdl_;
    struct LibTTF { bool success = false; LibTTF(); ~LibTTF(); } libttf_;
    struct LibMIX { bool success = false; LibMIX(); ~LibMIX(); } libmix_;

    struct WindowDeleter { void operator()(SDL_Window* window) const; };
    struct RendererDeleter { void operator()(SDL_Renderer* renderer) const; };
    struct MixerDeleter { void operator()(MIX_Mixer* mixer) const; };

    std::unique_ptr<SDL_Window, WindowDeleter> sdl_window_;
    std::unique_ptr<SDL_Renderer, RendererDeleter> sdl_renderer_;
    std::unique_ptr<MIX_Mixer, MixerDeleter> mix_mixer_;

    std::unique_ptr<Content> content_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<Time> time_;

    std::shared_ptr<Scene> empty_scene_;
    std::shared_ptr<Scene> current_scene_;
    std::shared_ptr<Scene> next_scene_;

protected:
    bool is_running_ = false;
    bool exit_on_close_ = true;

public:
    SDL_Window* sdl_window();
    SDL_Renderer* sdl_renderer();
    MIX_Mixer* mix_mixer();
    Content* content();
    Renderer* renderer();
    Time* time();

    void changeScene(std::shared_ptr<Scene> scene_);

    const char* const initial_title;
    const int initial_width;
    const int initial_height;

protected:
    virtual void loadContent();
    virtual void initialize();
    virtual void update();
    virtual void render();

public:
    GameApp(const char* title, int width, int height);
    ~GameApp();

    GameApp(GameApp&) = delete;
    GameApp(GameApp&&) = delete;
    GameApp& operator=(GameApp&) = delete;
    GameApp& operator=(GameApp&&) = delete;

    int run();
};