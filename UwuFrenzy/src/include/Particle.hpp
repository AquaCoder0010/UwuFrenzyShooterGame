#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
    private:
        sf::RectangleShape particleRect;
        sf::Vector2f particleRectPos;
        sf::Time timer;
        float speed;
    public:
        Particle();
        void setParticlePos(sf::Vector2f p_particlePos);
        void update(sf::Time fixedTimeSteps);   
        void drawTo(sf::RenderWindow window);
};