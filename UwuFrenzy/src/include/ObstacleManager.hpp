#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "Bullet.hpp"


struct int_winSize
{
    int x;
    int y;
};

class Obstacle
{
    public:
        Obstacle(sf::Texture& tex)
        :obstacle(), obstacleBounds(), health(), rotation()
        {
            obstacle.setTexture(tex);
            obstacle.setOrigin(tex.getSize().x/2, tex.getSize().y);
        }
        sf::FloatRect getObstacleGlobalBounds()
        {
            obstacleBounds = obstacle.getGlobalBounds();
            return obstacleBounds;
        }
        sf::Vector2f getObstaclePosition()
        {
            return obstacle.getPosition();
        }

        void randRotationSpeed()
        {
            rotation = rand() % 15;
        }
        sf::Sprite obstacle;
        sf::FloatRect obstacleBounds;
        int health;
        int rotation;
};


class Explosion
{
    public:
        Explosion(sf::Texture& explosionTex)
        :explosionFrames(), explosionSprite(), animationCounter(0), animationFinish(false),
        textureHeightX(0), textureHeightY(0)
        {
            for(int i = 0; i < 13; i++)
                explosionFrames.push_back(sf::IntRect(i * 185, 0, 185, 185));
            explosionSprite.setTexture(explosionTex);
            explosionSprite.setTextureRect(explosionFrames[0]);
            //explosionSprite.setOrigin(explosionTex.getSize().x/2, explosionTex.getSize().y/2);
        }

        void setPosition(sf::Vector2f explosionPos)
        {
            explosionSprite.setPosition(explosionPos);
        }
        void animate()
        {
                
            for(int i = 0; i < explosionFrames.size(); i++)
            {
                if(animationCounter == (i + 1) * 3)
                    explosionSprite.setTextureRect(explosionFrames[i]);
            }
            if(animationCounter == explosionFrames.size() * 3)
                animationFinish = true;
            else
            {
                animationCounter += 1;
                animationFinish = false;
            } 
        }
    public:
        std::vector<sf::IntRect> explosionFrames;
        sf::Sprite explosionSprite;
        short animationCounter;
        bool animationFinish;
        int textureHeightX; int textureHeightY;
};


class ObstacleManager
{
    private:
        std::vector<Obstacle> obstacles;
        sf::Texture obstacleTex;
        std::vector<Explosion> explosions;
        sf::Texture explosionTex;
        sf::Time currentTime;
        int_winSize windowSize;
        bool colide;
        char animationCounter;
        bool animationFinish;
    public:
        ObstacleManager(int win_x, int win_y);
        void update(sf::Time deltaTime, std::vector<Bullet>& bullets);
        void drawTo(sf::RenderWindow& window);
};