#include "content.h"
#include "game_app.h"
#include <SDL3/SDL_render.h> 
#include <SDL3_ttf/SDL_ttf.h> 
#include <SDL3_mixer/SDL_mixer.h>

void Content::TextureDeleter::operator()(SDL_Texture* texture) const { SDL_DestroyTexture(texture); }
void Content::FontDeleter::operator()(TTF_Font* font) const { TTF_CloseFont(font); }
void Content::AudioDeleter::operator()(MIX_Audio* audio) const { MIX_DestroyAudio(audio); }

std::size_t Content::FontKeyHash::operator()(const FontKey& key) const {
    return std::hash<std::string>()(key.first) ^ std::hash<float>()(key.second);
}

Content::Content(GameApp* app) : renderer_(app->sdl_renderer_.get()), mixer_(app->mix_mixer_.get()) { }
Content::~Content() = default;

void Content::clear()
{
    textures_.clear();
    fonts_.clear();
    audios_.clear();
}

SDL_Texture* Content::loadTexture(const std::string& file_path)
{
    if (getTexture(file_path)) return getTexture(file_path);

    SDL_Surface* surface = SDL_LoadPNG(file_path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (texture) textures_.emplace(file_path, UniquePtrTexture(texture));

    SDL_DestroySurface(surface);
    return texture;
}

SDL_Texture* Content::getTexture(const std::string& file_path)
{
    auto it = textures_.find(file_path);
    return it != textures_.end() ? it->second.get() : nullptr;
}

TTF_Font* Content::loadFont(const std::string& file_path, float point_size)
{
    if (getFont(file_path, point_size)) return getFont(file_path, point_size);

    TTF_Font* font = TTF_OpenFont(file_path.c_str(), point_size);
    if (font) fonts_.emplace(FontKey{file_path, point_size}, UniquePtrFont(font));

    return font;
}

TTF_Font* Content::getFont(const std::string& file_path, float point_size)
{
    auto it = fonts_.find({file_path, point_size});
    return it != fonts_.end() ? it->second.get() : nullptr;
}

MIX_Audio* Content::loadAudio(const std::string& file_path, bool predecode)
{
    if (getAudio(file_path)) return getAudio(file_path);

    MIX_Audio* audio = MIX_LoadAudio(mixer_, file_path.c_str(), predecode);
    if (audio) audios_.emplace(file_path, UniquePtrAudio(audio));

    return audio;
}

MIX_Audio* Content::getAudio(const std::string& file_path)
{
    auto it = audios_.find(file_path);
    return it != audios_.end() ? it->second.get() : nullptr;
}