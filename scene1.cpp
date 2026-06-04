#include "scene1.h"
#include "jewelstar/content.h"
#include "jewelstar/sprite.h"
#include "jewelstar/renderer.h"

Scene1::Scene1(GameApp* app) : Scene(app) { }
Scene1::~Scene1() = default;

void Scene1::loadContent()
{
    content_->loadTexture("C:/Data/Develop/LaTaleDoujin/LaTaleDoujin/resources/IRIS.PNG");
}

void Scene1::initialize()
{
    sprite_ = std::make_unique<Sprite>(content_.get(), "C:/Data/Develop/LaTaleDoujin/LaTaleDoujin/resources/IRIS.PNG");
}

void Scene1::render()
{
    renderer_->clear();
    renderer_->drawSprite(sprite_.get(), 0, 0);
    renderer_->present();
}