#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Flappy
{
public:
    Flappy();
    void run();

protected:
    void events() const;
    void draw() const;
    void game();
    void movePipes();
    void setAnimeBird();

private:
    std::unique_ptr<sf::RenderWindow> m_window;
    float m_gravity, m_frame, m_space;
    int m_count;
    sf::Texture m_bg, m_flappy, m_pipe;
    std::unique_ptr<sf::Sprite> m_background, m_bird, m_pipeUp, m_pipeDown;
    std::vector<sf::Sprite> m_pipes;
};

