#pragma once
#include "scene.h"
#include <memory>

class Sprite;
class GameApp;

class Scene1 : public Scene
{
    std::unique_ptr<Sprite> sprite_;

public:
    virtual void loadContent();
    virtual void initialize();
    virtual void render();

    Scene1(GameApp* app);
    ~Scene1();
};