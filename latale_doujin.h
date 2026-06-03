#pragma once
#include "game_app.h"
#include <memory>

class Sprite;

class LaTaleDoujin : public GameApp
{
    std::unique_ptr<Sprite> sprite_;

protected:
    virtual void loadContent();
    virtual void initialize();
    virtual void render();

public:
    LaTaleDoujin();
    ~LaTaleDoujin();
};