#include "game_app.h"
#include "time.h"
#include "resource_manager.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

GameApp::GameApp() = default;
GameApp::~GameApp() = default;

namespace {

struct LibSDL
{
    bool success = false;
    LibSDL() { success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); }
    ~LibSDL() { if (success) SDL_Quit(); }
};

struct LibTTF
{
    bool success = false;
    LibTTF() { success = TTF_Init(); }
    ~LibTTF() { if (success) TTF_Quit(); }
};

struct LibMIX
{
    bool success = false;
    LibMIX() { success = MIX_Init(); }
    ~LibMIX() { if (success) MIX_Quit(); }
};

}

int GameApp::run()
{
    LibSDL libsdl;
    if (!libsdl.success)
        return -1;

    LibTTF libttf;
    if (!libttf.success)
        return -1;

    LibMIX libmix;
    if (!libmix.success)
        return -1;

    window_ = SDL_CreateWindow("SunnyLand", 1360, 768, SDL_WINDOW_HIDDEN);
    if (window_ == nullptr)
        return -1;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window(window_, SDL_DestroyWindow);

    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (renderer_ == nullptr)
        return -1;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer(renderer_, SDL_DestroyRenderer);

    mixer_ = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (mixer_ == nullptr)
        return -1;
    std::unique_ptr<MIX_Mixer, void(*)(MIX_Mixer*)> mixer(mixer_, MIX_DestroyMixer);

    time_ = std::make_unique<Time>();
    resource_manager_ = std::make_unique<ResourceManager>(renderer_, mixer_);

    SDL_ShowWindow(window_);
    is_running_ = true;

    while (is_running_) {
        time_->update();
        float delta_time = time_->getDeltaTime();

        handleEvents();
        update(delta_time);
        render();
    }

    resource_manager_.release();
    time_.release();

    return 0;
}

void GameApp::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            is_running_ = false;
        }
    }
}

void GameApp::update(float delta_time)
{
}

void GameApp::render()
{
}