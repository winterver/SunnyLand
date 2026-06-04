#include "scene.h"
#include "game_app.h"
#include "content.h"

void Scene::loadContent() { }
void Scene::initialize() { }
void Scene::update() { }
void Scene::render() { }

Scene::Scene(GameApp* app)
    : app_(app)
    , content_(std::make_unique<Content>(app))
    , renderer_(app->renderer())
    , time_(app->time()) { }

Scene::~Scene() = default;