#include "latale_doujin.h"
#include "sprite.h"
#include "content.h"
#include "renderer.h"

LaTaleDoujin::LaTaleDoujin() : GameApp("La Tale Doujin", 1360, 768) { }
LaTaleDoujin::~LaTaleDoujin() = default;

void LaTaleDoujin::loadContent()
{
    content_->loadTexture("C:/Data/Develop/LaTaleDoujin/LaTaleDoujin/resources/IRIS.PNG");
}

void LaTaleDoujin::initialize()
{
    sprite_ = std::make_unique<Sprite>(content_.get(), "C:/Data/Develop/LaTaleDoujin/LaTaleDoujin/resources/IRIS.PNG");
}

void LaTaleDoujin::render()
{
    renderer_->clear();
    renderer_->drawSprite(sprite_.get(), 0, 0);
    renderer_->present();
}