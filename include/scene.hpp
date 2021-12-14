#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <string>
#include <map>

#include "errors/string_error.hpp"
#include "game_context.hpp"

class SceneTree;

class Scene : protected sf::Transformable
{
private:
    friend class SceneTree;
    
    std::map<std::string, Scene *> sceneChildren;

    void _init(GameContext *context);

    void _update(GameContext *context, double &dt);

    void _draw(GameContext *context, double &dt);

    void _event(GameContext *context, double &dt);

    void _free();

    Scene *parent;
    SceneTree *sceneRoot;
    sf::RenderTexture* graphics;
    std::string sceneName;

protected:

public:
    Scene(std::string _sceneName);
    virtual ~Scene() = default;

    std::string getName();

    virtual void init(GameContext *context) = 0;
    virtual void update(GameContext *context, double &dt) = 0;
    virtual void event(GameContext *context, double &dt) = 0;
    virtual void draw(GameContext *context, double &dt) = 0;
    virtual void free() = 0;

    sf::RenderTexture* createGraphics(uint32_t width, uint32_t height);
    sf::RenderTexture* getGraphics();

    void reloadScene(GameContext *context);

    void addChild(Scene *nScene);

    void eraseChild(std::string _sceneName);

    template <class SCENE>
    SCENE *getChild(std::string _sceneName);

    SceneTree* getSceneTree();

    Scene *getSceneChild(std::string _sceneName);

   template <class SCENE>
    SCENE* findOnChild(std::string _path)
    {

        if (_path.empty())
            throw StringError("path erroneo");
        if (_path.front() == '/')
            _path.erase(_path.begin());
        if (_path.back() == '/')
            _path.pop_back();

        std::stringstream stream(_path);
        std::string word = "";

        Scene *aux = this;

        std::getline(stream, word, '/');
        if(word.compare("root") == 0) aux = this;
        else throw StringError("path erroneo");

        while (std::getline(stream, word, '/'))
        {
            if (word.empty()){
                continue;
            }
            aux = aux->getSceneChild(word);
            if(aux == nullptr) 
                throw StringError("no existe la escena hija");
        }

        return dynamic_cast<SCENE *>(aux);
    }

};

#endif