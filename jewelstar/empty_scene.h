#pragma once
#include "scene.h"

class GameApp;

class EmptyScene : public Scene
{
public:
    virtual void render();

    EmptyScene(GameApp* app);
    ~EmptyScene();
};