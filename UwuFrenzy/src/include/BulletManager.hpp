#pragma once 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Bullet.hpp"

class BulletManager
{
    private:
        sf::Texture bulletTex;
        std::vector<Bullet> bullets;
        sf::Vector2f windowSize;
        sf::Vector2f gunPos;
        float rotation;
        bool leftInput;
        short reloadTimer;
        int bulletSize;
    public:
        BulletManager();    
        void getWindowSize(short win_x, short win_y);
        void processInput(sf::Event& event);
        void setGunRotation(float p_rotation);
        void setGunPosition(sf::Vector2f p_gunPos);
        void update(sf::Time deltaTime);
        void drawTo(sf::RenderWindow& window);
    public: 
        std::vector<Bullet>& getBulletVector()
        {
            return bullets;
        }
};
