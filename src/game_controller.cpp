#include "game_controller.hpp"

#include "main_scene.hpp"
#include "game_context.hpp"
#include "scene_tree.hpp"

GameController::GameController(WindowSettings settings)
{
    this->window = new sf::RenderWindow();
    this->event = new sf::Event();
    this->deltaClock = new sf::Clock();
    this->sceneTree = new SceneTree();
    this->mainScene = new MainScene();

    createWindow(settings);
}
GameController::~GameController()
{
    delete this->window;
    delete this->sceneTree;
    delete this->event;
    delete this->mainScene;
}

void GameController::createWindow(WindowSettings settings)
{
    this->window->create(
        sf::VideoMode(
            settings.windowSize.x,
            settings.windowSize.y),
        settings.title,
        settings.style,
        settings.contextSettings
    );

    sf::VideoMode windowVideoMode = sf::VideoMode::getDesktopMode();
    sf::Vector2i windowPos = {
        (windowVideoMode.width - settings.windowSize.x) * settings.windowPos.x,
        (windowVideoMode.height - settings.windowSize.x) * settings.windowPos.y
    };
    this->window->setPosition(windowPos);
    this->window->setFramerateLimit(settings.fps);

    //zona de pruebas
    this->sceneTree->setMainScene(this->mainScene);
}

void GameController::run()
{
    double dt = 0;

    this->sceneTree->init(this);

    while (this->window->isOpen())
    {
        while (this->window->pollEvent(*this->event))
        {
            this->sceneTree->event(this, dt);
        }

        this->sceneTree->update(this, dt);

        this->window->clear();

        this->sceneTree->draw(this, dt);

        this->window->display();

        dt = deltaClock->restart().asSeconds();
        this->fps = 1.f / (dt);
    }
}