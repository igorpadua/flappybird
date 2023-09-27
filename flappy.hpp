#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Flappy
{
public:
    Flappy();
    void run();

protected:
    void events();
    void draw() const;
    void game();
    void movePipes();
    void setAnimeBird();
    void movieBird();

private:
    std::unique_ptr<sf::RenderWindow> m_window;
    float m_gravity, m_frame, m_space;
    int m_count, m_score;
    sf::Texture m_bg, m_flappy, m_pipe;
    std::unique_ptr<sf::Sprite> m_background, m_bird, m_pipeUp, m_pipeDown;
    std::vector<sf::Sprite> m_pipes;
    bool m_gameover, m_add;
    sf::Font m_font;
    sf::Text m_txt_score, m_txt_gameover;
};

