#pragma once
#include <memory>

class GameApp;
class Content;
class Renderer;
class Time;

class Scene
{
public:
    GameApp* const app_;
    std::unique_ptr<Content> const content_;
    Renderer* const renderer_;
    Time* const time_;

    virtual void loadContent();
    virtual void initialize();
    virtual void update();
    virtual void render();

    Scene(GameApp* app);
    virtual ~Scene();

    Scene(Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(Scene&) = delete;
    Scene& operator=(Scene&&) = delete;
};