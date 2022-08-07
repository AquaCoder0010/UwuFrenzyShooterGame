#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Player
{
    private:
        sf::Texture playerRectTex;
        sf::Texture gunTex;
        sf::Sprite playerRect;
        sf::Sprite gun;
        sf::Vector2f gunPos;
        sf::Vector2f playerRectPos;
        sf::Vector2f playerRectMotion;
        sf::Vector2f mousePos;
        sf::Vector2f windowSize;
        bool left;
        bool right;
        float mouseDistance;
        float tIndex;
        float gunAngle;
    public: 
        Player();
        sf::Vector2f returnGunPos();
        float returnGunAngle();
        void setPosition(sf::Vector2f p_playerRectPos);
        void getMousePosition(sf::Vector2i p_mousePos);
        void getWindowSize(sf::Vector2f p_windowSize);
        void processEvent(sf::Event& event);
        void update(sf::Time deltaTime);
        void drawTo(sf::RenderWindow& window);
    private:
        void moveGun();
        
};