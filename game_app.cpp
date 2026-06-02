#include "game_app.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "resource_manager.h"
#include "time.h"

GameApp::LibSDL::LibSDL() { success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); }
GameApp::LibSDL::~LibSDL() { if (success) SDL_Quit(); }

GameApp::LibTTF::LibTTF() { success = TTF_Init(); }
GameApp::LibTTF::~LibTTF() { if (success) TTF_Quit(); }

GameApp::LibMIX::LibMIX() { success = MIX_Init(); }
GameApp::LibMIX::~LibMIX() { if (success) MIX_Quit(); }

void GameApp::WindowDeleter::operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
void GameApp::RendererDeleter::operator()(SDL_Renderer* renderer) const { SDL_DestroyRenderer(renderer); }
void GameApp::MixerDeleter::operator()(MIX_Mixer* mixer) const { MIX_DestroyMixer(mixer); }

GameApp::GameApp() = default;
GameApp::~GameApp() = default;

int GameApp::run()
{
    if (!libsdl_.success || !libttf_.success || !libmix_.success)
        return -1;

    window_.reset(SDL_CreateWindow("SunnyLand", 1360, 768, SDL_WINDOW_HIDDEN));
    renderer_.reset(SDL_CreateRenderer(window_.get(), nullptr));
    mixer_.reset(MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr));

    if (window_ == nullptr || renderer_ == nullptr || mixer_ == nullptr)
        return -1;

    resource_manager_ = std::make_unique<ResourceManager>(renderer_.get(), mixer_.get());
    time_ = std::make_unique<Time>(120);

    SDL_ShowWindow(window_.get());
    is_running_ = true;

    while (is_running_) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            if (event.type == SDL_EVENT_QUIT)
                is_running_ = false;

        update(time_->update());
        render();
    }

    return 0;
}

void GameApp::update(float delta_time)
{
}

void GameApp::render()
{
}