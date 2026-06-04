#include "empty_scene.h"
#include "renderer.h"

EmptyScene::EmptyScene(GameApp* app) : Scene(app) { }
EmptyScene::~EmptyScene() = default;

void EmptyScene::render()
{
    renderer_->clear();
    renderer_->present();
}