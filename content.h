#pragma once
#include <string>
#include <memory>
#include <unordered_map>

struct SDL_Renderer;
struct MIX_Mixer;
struct SDL_Texture;
struct TTF_Font;
struct MIX_Audio;

class Content
{
    struct TextureDeleter { void operator()(SDL_Texture* texture) const; };
    struct FontDeleter { void operator()(TTF_Font* font) const; };
    struct AudioDeleter { void operator()(MIX_Audio* audio) const; };

    using UniquePtrTexture = std::unique_ptr<SDL_Texture, TextureDeleter>;
    using UniquePtrFont = std::unique_ptr<TTF_Font, FontDeleter>;
    using UniquePtrAudio = std::unique_ptr<MIX_Audio, AudioDeleter>;

    using FontKey = std::pair<std::string, float>;
    struct FontKeyHash { std::size_t operator()(const FontKey& key) const; };

    std::unordered_map<std::string, UniquePtrTexture> textures_;
    std::unordered_map<FontKey, UniquePtrFont, FontKeyHash> fonts_;
    std::unordered_map<std::string, UniquePtrAudio> audios_;

    SDL_Renderer* renderer_;
    MIX_Mixer* mixer_;

public:
    Content(SDL_Renderer* renderer, MIX_Mixer* mixer);
    ~Content();

    Content(Content&) = delete;
    Content(Content&&) = delete;
    Content& operator=(Content&) = delete;
    Content& operator=(Content&&) = delete;

    void clear();

    SDL_Texture* loadTexture(const std::string& file_path);
    SDL_Texture* getTexture(const std::string& file_path);

    TTF_Font* loadFont(const std::string& file_path, float point_size);
    TTF_Font* getFont(const std::string& file_path, float point_size);

    MIX_Audio* loadAudio(const std::string& file_path, bool predecode = false);
    MIX_Audio* getAudio(const std::string& file_path);
};