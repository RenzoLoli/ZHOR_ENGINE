#ifndef SCENE_TREE_HPP
#define SCENE_TREE_HPP

#include <sstream>

struct GameContext;

class Scene;
class GameController;

class SceneTree
{
private:
    friend class GameController;
    Scene* mainScene;

    void init(GameContext* context);
    void update(GameContext* context, double& dt);
    void event(GameContext* context, double& dt);
    void draw(GameContext* context, double& dt);
    void free();
    
    void setMainScene(Scene* _scene);

public:

    SceneTree();
    ~SceneTree();
    template<class SCENE>
    SCENE* findChild(std::string _path);

    Scene* findScene(std::string _path);

};

#endif