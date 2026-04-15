#include "game_app.h"

#if defined(_WIN32) && !defined(_DEBUG)
 #pragma comment(linker, "/subsystem:windows")
 #define main WinMain
#endif

int main()
{
    GameApp game_app;
    game_app.run();
}