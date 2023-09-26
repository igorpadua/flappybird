#include "flappy.hpp"

Flappy::Flappy() :
    m_window(std::make_unique<sf::RenderWindow>(
               sf::VideoMode(1000, 600),
               "Flappy Bird",
                sf::Style::Titlebar | sf::Style::Close))
  , m_gravity(0)
  , m_frame(0)
  , m_space(160.f)
  , m_count(0)
  , m_background(std::make_unique<sf::Sprite>())
  , m_bird(std::make_unique<sf::Sprite>())
  , m_pipeUp(std::make_unique<sf::Sprite>())
  , m_pipeDown(std::make_unique<sf::Sprite>())
{
    m_window->setPosition(sf::Vector2i(0, 0));
    m_window->setFramerateLimit(60);

    m_bg.loadFromFile("./resources/img/background.png");
    m_flappy.loadFromFile("./resources/img/flappy.png");
    m_pipe.loadFromFile("./resources/img/pipe.png");

    m_background->setTexture(m_bg);
    m_bird->setTexture(m_flappy);
    m_pipeUp->setTexture(m_pipe);
    m_pipeDown->setTexture(m_pipe);

    m_bird->setPosition(500.f - m_flappy.getSize().x / 2, 300.f - m_flappy.getSize().y / 2);

    m_bird->setScale(2.f, 2.f);
    m_bird->setTextureRect(sf::IntRect(0, 0, 34, 24));

    m_pipeDown->setScale(1.5f, 1.5f);
    m_pipeUp->setScale(1.5f, -1.5f);
}

void Flappy::run() const
{
    while (m_window->isOpen()) {
        events();
        draw();
    }
}

void Flappy::events() const
{
    auto event = std::make_unique<sf::Event>();

    while (m_window->pollEvent(*event)) {
        if (event->type == sf::Event::Closed) {
            m_window->close();
        }
    }
}

void Flappy::draw() const
{
    m_window->clear(sf::Color::Black);
    m_window->draw(*m_background);
    m_window->draw(*m_bird);
    m_window->display();
}
