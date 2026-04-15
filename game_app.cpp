#include "game_app.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "time.h"

GameApp::GameApp() = default;
GameApp::~GameApp() = default;

void GameApp::run()
{
    if (!init()) {
        return;
    }

    while (is_running_) {
        time_->update();
        float delta_time = time_->getDeltaTime();

        handleEvents();
        update(delta_time);
        render();
    }

    close();
}

bool GameApp::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        return false;
    }
    TTF_Init();
    MIX_Init();

    window_ = SDL_CreateWindow("SunnyLand", 1360, 768, SDL_WINDOW_HIDDEN);
    if (window_ == nullptr) {
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (renderer_ == nullptr) {
        return false;
    }

    time_ = std::make_unique<Time>();

    SDL_ShowWindow(window_);
    is_running_ = true;
    return true;
}

void GameApp::close()
{
    time_.release();

    if (renderer_ != nullptr) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_ != nullptr) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    MIX_Quit();
    TTF_Quit();
    SDL_Quit();
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