#pragma once
#include "game_app.h"
#include <memory>

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