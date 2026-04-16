#include "game_app.h"
#include "time.h"
#include "resource_manager.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

GameApp::GameApp() = default;
GameApp::~GameApp() = default;

int GameApp::run()
{
    int ret = -1;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        goto quit;

    if (!TTF_Init())
        goto sdl_quit;

    if (!MIX_Init())
        goto ttf_quit;

    window_ = SDL_CreateWindow("SunnyLand", 1360, 768, SDL_WINDOW_HIDDEN);
    if (window_ == nullptr)
        goto mix_quit;

    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (renderer_ == nullptr)
        goto win_quit;

    mixer_ = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (mixer_ == nullptr)
        goto ren_quit;

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

    ret = 0;
    MIX_StopAllTracks(mixer_, 0);
    MIX_DestroyMixer(mixer_);
ren_quit:
    SDL_DestroyRenderer(renderer_);
win_quit:
    SDL_DestroyWindow(window_);
mix_quit:
    MIX_Quit();
ttf_quit:
    TTF_Quit();
sdl_quit:
    SDL_Quit();
quit:
    renderer_ = nullptr;
    window_ = nullptr;
    return ret;
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