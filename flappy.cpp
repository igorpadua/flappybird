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
  , m_gameover(false)
  , m_add(false)
  , m_score(0)
{
    m_window->setPosition(sf::Vector2i(0, 0));
    m_window->setFramerateLimit(60);

    m_bg.loadFromFile("./resources/img/background.png");
    m_flappy.loadFromFile("./resources/img/flappy.png");
    m_pipe.loadFromFile("./resources/img/pipe.png");

    m_font.loadFromFile("./resources/font/flappybird.ttf");

    m_txt_gameover.setFont(m_font);
    m_txt_gameover.setString("Press SPACE to restart");
    m_txt_gameover.setPosition(200, 300);
    m_txt_gameover.setCharacterSize(50);
    m_txt_gameover.setOutlineThickness(3);

    m_txt_score.setFont(m_font);
    m_txt_score.setString(std::to_string(m_score));
    m_txt_score.setPosition(10.f, 10.f);
    m_txt_score.setCharacterSize(50);
    m_txt_score.setOutlineThickness(3);

    m_background->setTexture(m_bg);
    m_bird->setTexture(m_flappy);
    m_pipeUp->setTexture(m_pipe);
    m_pipeDown->setTexture(m_pipe);

    m_bird->setPosition(500.f - m_flappy.getSize().x / 2, 300.f - m_flappy.getSize().y / 2);

    m_bird->setScale(2.f, 2.f);
    m_bird->setTextureRect(sf::IntRect(0, 0, 34, 24));

    m_pipeDown->setScale(1.5f, 1.5f);
    m_pipeUp->setScale(1.5f, -1.5);
}

void Flappy::run()
{
    while (m_window->isOpen()) {
        events();
        game();
        draw();

        ++m_count;

        if (m_count == 300) {
            m_count = 0;
        }
    }
}

void Flappy::events()
{
    auto event = std::make_unique<sf::Event>();

    while (m_window->pollEvent(*event)) {
        if (event->type == sf::Event::Closed) {
            m_window->close();
        }
    }

    if (m_gameover and sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_score = 0;
        m_txt_score.setString(std::to_string(m_score));
        m_pipes.clear();
        m_bird->setPosition(500.f - m_flappy.getSize().x / 2, 300.f - m_flappy.getSize().y / 2);
        m_gameover = false;
    }
}

void Flappy::draw() const
{
    m_window->clear(sf::Color::Black);
    m_window->draw(*m_background);
    for (auto &p : m_pipes) {
        m_window->draw(p);
    }
    m_window->draw(*m_bird);

    if (m_gameover) {
        m_window->draw(m_txt_gameover);
    }

    m_window->draw(m_txt_score);

    m_window->display();
}

void Flappy::game()
{
    if (!m_gameover) {
        setAnimeBird();
        movieBird();
        movePipes();
    }
}

void Flappy::movePipes()
{


    if (m_count % 150 == 0) {
        auto pos = std::rand() % 275 + 175;

        m_pipeDown->setPosition(1000, pos + m_space);
        m_pipeUp->setPosition(1000, pos);

        m_pipes.push_back(*m_pipeDown);
        m_pipes.push_back(*m_pipeUp);
    }

    for (int i = 0; i < m_pipes.size(); ++i) {

        if (m_pipes[i].getGlobalBounds().intersects(m_bird->getGlobalBounds())) {
            m_bird->move(15.f, 0);

            if (m_pipes[i].getScale().y < 0) {
                m_bird->move(0, -15.f);
            } else {
                m_bird->move(0, 15.f);
            }

            m_gameover = true;
        }

        if (m_pipes[i].getPosition().x < -100) {
            m_pipes.erase(m_pipes.begin() + i);
        }

        m_pipes[i].move(-4.f, 0);

        if (m_pipes[i].getPosition().x == 448 and !m_add) {
            ++m_score;
            m_txt_score.setString(std::to_string(++m_score));
            m_add = true;
        } else {
            m_add = false;
        }
    }
}

void Flappy::setAnimeBird()
{
    m_frame += 0.15f;

    if (m_frame > 3) {
        m_frame -= 3;
    }

    m_bird->setTextureRect(sf::IntRect(34 * static_cast<int>(m_frame), 0, 34, 24));
}

void Flappy::movieBird()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        m_gravity = -8.f;
        m_bird->setRotation(-m_frame - 10.f);
    } else {
        m_bird->setRotation(m_frame - 10.f);
    }

    m_bird->move(0, m_gravity);
    m_gravity += 0.5f;
}
