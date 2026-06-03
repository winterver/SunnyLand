#include "game_app.h"
#include "content.h"
#include "renderer.h"
#include "time.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

GameApp::LibSDL::LibSDL() { success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); }
GameApp::LibSDL::~LibSDL() { if (success) SDL_Quit(); }

GameApp::LibTTF::LibTTF() { success = TTF_Init(); }
GameApp::LibTTF::~LibTTF() { if (success) TTF_Quit(); }

GameApp::LibMIX::LibMIX() { success = MIX_Init(); }
GameApp::LibMIX::~LibMIX() { if (success) MIX_Quit(); }

void GameApp::WindowDeleter::operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
void GameApp::RendererDeleter::operator()(SDL_Renderer* renderer) const { SDL_DestroyRenderer(renderer); }
void GameApp::MixerDeleter::operator()(MIX_Mixer* mixer) const { MIX_DestroyMixer(mixer); }

void GameApp::loadContent() { }
void GameApp::initialize() { }
void GameApp::update() { }
void GameApp::render() { }

GameApp::GameApp(const char* title, int width, int height)
    : initial_title(title), initial_width(width), initial_height(height) { }

GameApp::~GameApp() = default;

int GameApp::run()
{
    if (!libsdl_.success || !libttf_.success || !libmix_.success)
        return -1;

    sdl_window_.reset(SDL_CreateWindow(initial_title, initial_width, initial_height, SDL_WINDOW_HIDDEN));
    sdl_renderer_.reset(SDL_CreateRenderer(sdl_window_.get(), nullptr));
    mix_mixer_.reset(MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr));

    if (sdl_window_ == nullptr || sdl_renderer_ == nullptr || mix_mixer_ == nullptr)
        return -1;

    content_ = std::make_unique<Content>(this);
    renderer_ = std::make_unique<Renderer>(this);

    this->loadContent();
    this->initialize();

    SDL_ShowWindow(sdl_window_.get());
    time_ = std::make_unique<Time>(120);
    is_running_ = true;

    while (is_running_) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            if (event.type == SDL_EVENT_QUIT)
                is_running_ = false;

        time_->update();
        this->update();
        this->render();
    }

    return 0;
}