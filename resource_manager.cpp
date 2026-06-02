#include "resource_manager.h"
#include <SDL3/SDL_render.h> 
#include <SDL3_ttf/SDL_ttf.h> 
#include <SDL3_mixer/SDL_mixer.h>

void ResourceManager::TextureDeleter::operator()(SDL_Texture* texture) const { SDL_DestroyTexture(texture); }
void ResourceManager::FontDeleter::operator()(TTF_Font* font) const { TTF_CloseFont(font); }
void ResourceManager::AudioDeleter::operator()(MIX_Audio* audio) const { MIX_DestroyAudio(audio); }

std::size_t ResourceManager::FontKeyHash::operator()(const FontKey& key) const {
    return std::hash<std::string>()(key.first) ^ std::hash<float>()(key.second);
}

ResourceManager::ResourceManager(SDL_Renderer* renderer, MIX_Mixer* mixer)
    : renderer_(renderer), mixer_(mixer) { }

ResourceManager::~ResourceManager() = default;

void ResourceManager::clear()
{
    textures_.clear();
    fonts_.clear();
    audios_.clear();
}

SDL_Texture* ResourceManager::loadTexture(const std::string& file_path)
{
    if (getTexture(file_path)) return getTexture(file_path);

    SDL_Surface* surface = SDL_LoadPNG(file_path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (texture) textures_.emplace(file_path, UniquePtrTexture(texture));

    SDL_DestroySurface(surface);
    return texture;
}

SDL_Texture* ResourceManager::getTexture(const std::string& file_path)
{
    auto it = textures_.find(file_path);
    return it != textures_.end() ? it->second.get() : nullptr;
}

TTF_Font* ResourceManager::loadFont(const std::string& file_path, float point_size)
{
    if (getFont(file_path, point_size)) return getFont(file_path, point_size);

    TTF_Font* font = TTF_OpenFont(file_path.c_str(), point_size);
    if (font) fonts_.emplace(FontKey{file_path, point_size}, UniquePtrFont(font));

    return font;
}

TTF_Font* ResourceManager::getFont(const std::string& file_path, float point_size)
{
    auto it = fonts_.find({file_path, point_size});
    return it != fonts_.end() ? it->second.get() : nullptr;
}

MIX_Audio* ResourceManager::loadAudio(const std::string& file_path, bool predecode)
{
    if (getAudio(file_path)) return getAudio(file_path);

    MIX_Audio* audio = MIX_LoadAudio(mixer_, file_path.c_str(), predecode);
    if (audio) audios_.emplace(file_path, UniquePtrAudio(audio));

    return audio;
}

MIX_Audio* ResourceManager::getAudio(const std::string& file_path)
{
    auto it = audios_.find(file_path);
    return it != audios_.end() ? it->second.get() : nullptr;
}