#include "resource_manager.h"
#include <SDL3/SDL_render.h> 
#include <SDL3_ttf/SDL_ttf.h> 
#include <SDL3_mixer/SDL_mixer.h>

#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

ResourceManager::ResourceManager(SDL_Renderer* renderer, MIX_Mixer* mixer)
    : renderer_(renderer)
    , mixer_(mixer)
{ }

ResourceManager::~ResourceManager() = default;

void ResourceManager::clear()
{
    textures_.clear();
    fonts_.clear();
    audios_.clear();
}

SDL_Texture* ResourceManager::loadTexture(const std::string& file_path)
{
    auto it = textures_.find(file_path);
    if (it != textures_.end())
        return it->second.get();

    int x, y, channels;
    stbi_uc* pixels = stbi_load(file_path.c_str(), &x, &y, &channels, STBI_rgb_alpha);

    if (!pixels)
        return nullptr;

    SDL_Surface* surface = SDL_CreateSurfaceFrom(x, y, SDL_PIXELFORMAT_RGBA8888, pixels, x*4);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);

    SDL_DestroySurface(surface);
    stbi_image_free(pixels);

    if (!texture)
        return nullptr;

    textures_.emplace(file_path, UniquePtrTexture(texture, SDL_DestroyTexture));
    return texture;
}

void ResourceManager::unloadTexture(const std::string& file_path)
{
    auto it = textures_.find(file_path);
    if (it != textures_.end())
        textures_.erase(it);
}

TTF_Font* ResourceManager::loadFont(const std::string& file_path, float point_size)
{
    FontKey key = { file_path, point_size };
    auto it = fonts_.find(key);
    if (it != fonts_.end())
        return it->second.get();

    TTF_Font* font = TTF_OpenFont(file_path.c_str(), point_size);

    if (!font)
        return nullptr;

    fonts_.emplace(key, UniquePtrFont(font, TTF_CloseFont));
    return font;
}

void ResourceManager::unloadFont(const std::string& file_path, float point_size)
{
    auto it = fonts_.find({file_path, point_size});
    if (it != fonts_.end())
        fonts_.erase(it);
}

MIX_Audio* ResourceManager::loadAudio(const std::string& file_path, bool predecode)
{
    auto it = audios_.find(file_path);
    if (it != audios_.end())
        return it->second.get();

    MIX_Audio* audio = MIX_LoadAudio(mixer_, file_path.c_str(), predecode);

    if (!audio)
        return nullptr;

    audios_.emplace(file_path, UniquePtrAudio(audio, MIX_DestroyAudio));
    return audio;
}

void ResourceManager::unloadAudio(const std::string& file_path)
{
    auto it = audios_.find(file_path);
    if (it != audios_.end())
        audios_.erase(it);
}