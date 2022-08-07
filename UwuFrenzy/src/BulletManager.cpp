#include "BulletManager.hpp"

BulletManager::BulletManager()
:leftInput(false), bullets(), bulletTex()
{
    if(bulletTex.loadFromFile("rsrc/Images/Bullets.png"))
    {
        std::cout << "Loaded Bullets.png" << std::endl;
    }
    reloadTimer = 0;
    windowSize.x = 0; windowSize.y = 0;
    bulletSize = 0;
    rotation = 0;
}


void BulletManager::processInput(sf::Event& event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left) 
        {
            leftInput = true;
        }
    }

    if(event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Left) 
        {
            leftInput = false;
        }
    }

}

void BulletManager::getWindowSize(short win_x, short win_y)
{
    windowSize.x = win_x;
    windowSize.y = win_y;

}

void BulletManager::setGunRotation(float p_rotation)
{
    rotation = p_rotation;
}

void BulletManager::setGunPosition(sf::Vector2f p_gunPos)
{
    gunPos = p_gunPos;
}

void BulletManager::update(sf::Time deltaTime)
{
    bulletSize = bullets.size();
    if(leftInput == true && reloadTimer == 0)
    {
        reloadTimer = 5;
        bullets.push_back(Bullet(bulletTex));
        bullets.back().setPosition(gunPos);
        bullets.back().setRotation(rotation);
    }
    if(leftInput == false && reloadTimer > 0)
    {
        reloadTimer -= 1;
    }

    for(auto& bullet : bullets)
    {
        bullet.update(deltaTime);
    }

    for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();)
    {
        if ( (it->getPosition().x > windowSize.x || it->getPosition().x < 0.f) || (it->getPosition().y > windowSize.y || it->getPosition().y < 0.f) )
            it = bullets.erase(it);
        else
        {
            it++;
        }
    }
}

void BulletManager::drawTo(sf::RenderWindow& window)
{
    for(auto& bullet : bullets)
    {
        bullet.drawTo(window);
    }
}