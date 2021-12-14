#include "main_scene.hpp"

#include "game_context.hpp"

float x = 0, y = 0;
float velx = 0, vely = 0;
sf::RectangleShape rect;

MainScene::MainScene() : Scene("root")
{
}

MainScene::~MainScene()
{
}

void MainScene::init(GameContext *context)
{
    this->setPosition({50,50});
    x = y = velx = vely = 0;
    rect.setFillColor(sf::Color::Blue);
    rect.setSize({50, 50});
}

void MainScene::update(GameContext *context, double &dt)
{
    rect.setPosition({x, y});

    int8_t left  = (sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    int8_t right = (sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
    int8_t up    = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    int8_t down  = (sf::Keyboard::isKeyPressed(sf::Keyboard::Down));

    int8_t dirX = right - left;
    int8_t dirY = down - up;

    float roz = 0.98f;

    if(dirX != 0) velx += dirX * 200 * dt; else velx *= roz;
    if(dirY != 0) vely += dirY * 200 * dt; else vely *= roz;

  /*  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        velx -= 200*dt;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        velx += 200*dt;
    }else{
        velx *= .98f;
    }
*/
    x += velx*dt;
    y += vely*dt;
}
void MainScene::event(GameContext *context, double &dt)
{
    sf::Event *e = context->event;
    if (e->type == sf::Event::Closed)
    {
        context->window->close();
        //reloadScene(context);
    }

    if(e->type == sf::Event::KeyPressed){
        switch (e->key.code)
        {
        case sf::Keyboard::R: {
            reloadScene(context);
        }
            break;
        
        default:
            break;
        }
    }
}
void MainScene::draw(GameContext *context, double &dt)
{
    sf::RenderTexture *gfx = this->getGraphics();

    gfx->clear(sf::Color::Red);

    gfx->draw(rect);
}
void MainScene::free()
{
}