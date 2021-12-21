#include "scenes/main_scene.hpp"

#include "ZHOR_ENGINE/game_context.hpp"

MainScene::MainScene() : Scene("root")
{
}

MainScene::~MainScene()
{
}

void MainScene::create(GameContext *context){
}

void MainScene::init(GameContext *context)
{
}

void MainScene::update(GameContext *context, double &dt)
{
}
void MainScene::event(GameContext *context, double &dt)
{
    sf::Event e = *context->event;
    if(e.type == sf::Event::Closed){
        context->window->close();
        exit(0);
    }
}
void MainScene::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void MainScene::free()
{
}