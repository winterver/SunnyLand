#pragma once
#include "jewelstar/game_app.h"

class Scene;

class LaTaleDoujin : public GameApp
{
    std::shared_ptr<Scene> scene1_;

protected:
    virtual void initialize();

public:
    LaTaleDoujin();
    ~LaTaleDoujin();
};