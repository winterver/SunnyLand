#pragma once
#include <string>
#include <memory>
#include <unordered_map>

struct SDL_Renderer;
struct MIX_Mixer;
struct SDL_Texture;
struct TTF_Font;
struct MIX_Audio;

class ResourceManager
{
    using UniquePtrTexture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>;
    using UniquePtrFont = std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>;
    using UniquePtrAudio = std::unique_ptr<MIX_Audio, void(*)(MIX_Audio*)>;

    using FontKey = std::pair<std::string, float>;
    struct FontKeyHash {
        std::size_t operator() (const FontKey& key) const {
            return std::hash<std::string>()(key.first) ^ std::hash<float>()(key.second);
        }
    };

    std::unordered_map<std::string, UniquePtrTexture> textures_;
    std::unordered_map<FontKey, UniquePtrFont, FontKeyHash> fonts_;
    std::unordered_map<std::string, UniquePtrAudio> audios_;

    SDL_Renderer* renderer_;
    MIX_Mixer* mixer_;

public:
    ResourceManager(SDL_Renderer* renderer, MIX_Mixer* mixer);
    ~ResourceManager();

    ResourceManager(ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    void clear();

    SDL_Texture* loadTexture(const std::string& file_path);
    void unloadTexture(const std::string& file_path);

    TTF_Font* loadFont(const std::string& file_path, float point_size);
    void unloadFont(const std::string& file_path, float point_size);

    MIX_Audio* loadAudio(const std::string& file_path, bool predecode);
    void unloadAudio(const std::string& file_path);
};