#include "scene_tree.hpp"

#include "game_controller.hpp"
#include "game_context.hpp"
#include "scene.hpp"

void SceneTree::init(GameContext* context){
    this->mainScene->_init(context);
}

void SceneTree::update(GameContext *context, double &dt)
{
    this->mainScene->_update(context, dt);
}
void SceneTree::event(GameContext *context, double &dt)
{
    this->mainScene->_event(context, dt);
}
void SceneTree::draw(GameContext *context, double &dt)
{
    this->mainScene->_draw(context, dt);
}
void SceneTree::free()
{
    this->mainScene->_free();
}

void SceneTree::setMainScene(Scene *_scene)
{
    if (_scene == nullptr)
        throw "no hay una escena principal definida";
    this->mainScene = _scene;
}

SceneTree::SceneTree()
{
    this->mainScene = nullptr;
}
SceneTree::~SceneTree()
{
    free();
}

template <class SCENE>
SCENE *SceneTree::findChild(std::string _path)
{

    if (_path.empty())
        throw StringError("path erroneo");
    if (_path.front() == '/')
        _path.erase(_path.begin());
    if (_path.back() == '/')
        _path.pop_back();

    std::stringstream stream(_path);
    std::string word;

    Scene *aux = nullptr;

    std::getline(stream, word, '/');
    if(word.compare("root") == 0) aux = this->mainScene;
    else throw StringError("path erroneo");

    while (std::getline(stream, word, '/'))
    {
        if (word.empty()) continue;
        aux = aux->getSceneChild(word);
    }

    return dynamic_cast<SCENE *>(aux);
}

Scene *SceneTree::findScene(std::string _path)
{

    if (_path.empty())
        throw StringError("path erroneo");
    if (_path.front() == '/')
        _path.erase(_path.begin());
    if (_path.back() == '/')
        _path.pop_back();

    std::stringstream stream(_path);
    std::string word;

    Scene *aux = nullptr;

    std::getline(stream, word, '/');
    if(word.compare("root") == 0) aux = this->mainScene;
    else throw StringError("path erroneo");
    
    while (std::getline(stream, word, '/'))
    {
        if (word.empty()) continue;
        aux = aux->getSceneChild(word);
    }

    return aux;
}