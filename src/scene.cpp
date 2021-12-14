#include "scene.hpp"

#include "game_context.hpp"
#include "scene_tree.hpp"

Scene::Scene(std::string _sceneName) : sceneName(_sceneName) {
    this->graphics = new sf::RenderTexture();
    this->graphics->create(500,500);
}

std::string Scene::getName(){return this->sceneName;}

sf::RenderTexture* Scene::createGraphics(uint32_t width, uint32_t height){
    this->graphics->create(width,height);
    return this->getGraphics();
}

sf::RenderTexture* Scene::getGraphics(){
    return this->graphics;
}

void Scene::reloadScene(GameContext *context){
    _init(context);
}

void Scene::_init(GameContext *context)
{
    for (auto [_, child] : sceneChildren)
    {
        child->_init(context);
    }
    this->init(context);
}

void Scene::_update(GameContext *context, double &dt)
{
    for (auto [_, child] : sceneChildren)
    {
        child->_update(context, dt);
    }
    this->update(context, dt);
}

void Scene::_draw(GameContext *context, double &dt)
{
    sf::RenderTexture* gfx = nullptr;
    sf::RenderWindow* _window = context->window;
    sf::Sprite _buffer;

    for (auto [_, child] : sceneChildren)
    {
        child->_draw(context, dt);
        gfx = child->getGraphics();
        gfx->display();
        _buffer.setTexture(gfx->getTexture());
        _buffer.setPosition(child->getPosition());
        _window->draw(_buffer);
    }
    this->draw(context, dt);
    gfx = this->getGraphics();
    gfx->display();
    _buffer.setTexture(gfx->getTexture());
    _buffer.setPosition(this->getPosition());
    _window->draw(_buffer);
}

void Scene::_event(GameContext *context, double &dt)
{
    for (auto [_, child] : sceneChildren)
    {
        child->_event(context, dt);
    }
    this->event(context, dt);
}

void Scene::_free()
{
    for (auto [_, child] : sceneChildren)
    {
        child->_free();
    }
    this->free();
    
    delete this->graphics;
}

SceneTree* Scene::getSceneTree(){
    return this->sceneRoot;
}

void Scene::addChild(Scene *nScene)
{

    if (nScene == nullptr)
        throw StringError("insertar escena hija fue NULL");

    nScene->sceneRoot = this->sceneRoot;
    nScene->parent = this;
    this->sceneChildren.insert(
        std::make_pair(nScene->sceneName, nScene)
    );
}

void Scene::eraseChild(std::string _sceneName)
{
    if (this->sceneChildren.count(_sceneName) > 0)
    {
        Scene *&dScene = this->sceneChildren[_sceneName];
        this->sceneChildren.erase(_sceneName);
    }
}

template <class SCENE>
SCENE* Scene::getChild(std::string _sceneName)
{
    if (this->sceneChildren.count(_sceneName) > 0)
    {
        return dynamic_cast<SCENE *>(this->sceneChildren[_sceneName]);
    }

    throw StringError("no existe la escena hija");
}

Scene* Scene::getSceneChild(std::string _sceneName)
{
    if (this->sceneChildren.count(_sceneName) > 0)
    {
        return this->sceneChildren[_sceneName];
    }

    throw StringError("no existe la escena hija");
}

