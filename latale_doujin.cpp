#include "latale_doujin.h"
#include "scene1.h"

LaTaleDoujin::LaTaleDoujin() : GameApp("La Tale Doujin", 1360, 768) { }
LaTaleDoujin::~LaTaleDoujin() = default;

void LaTaleDoujin::initialize()
{
    scene1_ = std::make_shared<Scene1>(this);
    scene1_->loadContent();
    scene1_->initialize();
    changeScene(scene1_);
}