#ifndef MAIN_SCENE_HPP
#define MAIN_SCENE_HPP

#include <SFML/Graphics.hpp>

#include "scene.hpp"

class MainScene : public Scene{
public:
    
    MainScene();
    ~MainScene();
    
    void init(GameContext *context);
    void update(GameContext* context, double& dt);
    void event(GameContext* context, double& dt);
    void draw(GameContext* context, double& dt);
    void free();

};

#endif