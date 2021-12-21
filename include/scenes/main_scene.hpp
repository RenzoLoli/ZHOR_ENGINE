#ifndef MAIN_SCENE_HPP
#define MAIN_SCENE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

#include "ZHOR_ENGINE/scene.hpp"

class MainScene : public Scene{
public:

    MainScene();
    ~MainScene();
    
    void init(GameContext *context);
    void update(GameContext* context, double& dt);
    void event(GameContext* context, double& dt);
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void free();

    void create(GameContext *context);

};

#endif