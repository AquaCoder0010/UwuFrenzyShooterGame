#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <array>

class Bullet
{
    private:
        sf::Sprite bullet;
        std::array<sf::IntRect, 2> bulletFrames;
        sf::Vector2f bulletDir;
        sf::FloatRect bulletBounds;
        float rotation;
    public:
        Bullet(sf::Texture& bulletTex)
        :bulletDir(0.f, 0.f)
        {
            bullet.setTexture(bulletTex);
            bulletFrames[0] = sf::IntRect(0, 0, 50, 31);
            bulletFrames[1] = sf::IntRect(50, 0, 50, 31);
            bullet.setTextureRect(bulletFrames[0]);
            bullet.setScale(0.5f, 0.5f);
            bullet.setOrigin(bulletTex.getSize().x/2, bulletTex.getSize().y/2);

            rotation = 0;
        }

        void setTextureRect(sf::IntRect bulletTexRect)
        {
            bullet.setTextureRect(bulletTexRect);
        }
        sf::FloatRect getBulletBounds()
        {
            bulletBounds = bullet.getGlobalBounds();
            return bulletBounds;
        }
        sf::Vector2f getPosition()
        {
            return bullet.getPosition();
        }
        void setPosition(sf::Vector2f p_bulletPos)
        {   
            bullet.setPosition(p_bulletPos);
        }
        void setRotation(float p_rotation)
        {
            rotation = p_rotation;
        }

        void update(sf::Time deltaTime)
        {
            bulletDir.x = radianToDegrees(cos(degreesToRadians(rotation))) * deltaTime.asSeconds() * 18.f;
            bulletDir.y = radianToDegrees(sin(degreesToRadians(rotation))) * deltaTime.asSeconds() * 18.f;
            bullet.move(bulletDir);
            bullet.setRotation(rotation);
        }

        void drawTo(sf::RenderWindow& window)
        {
            window.draw(bullet);
        }
    private:
        float radianToDegrees(float radian)
        {
            float degrees =  (radian * 180) / 3.141592;
            return degrees; 
        }

        float degreesToRadians(float degrees)
        {
            float radian = (degrees * 3.141592) / 180;
            return radian;
        }
};