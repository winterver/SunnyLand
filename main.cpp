#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#if defined(_WIN32) && !defined(_DEBUG)
 #pragma comment(linker, "/subsystem:windows")
 #define main WinMain
#endif

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    MIX_Init();
    MIX_Quit();
    TTF_Quit();
    SDL_Quit();
}