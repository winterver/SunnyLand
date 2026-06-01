#include "game_app.h"

//#if defined(_WIN32) && !defined(_DEBUG)
// #define main WinMain
//#endif

int main()
{
    GameApp game_app;
    return game_app.run();
}