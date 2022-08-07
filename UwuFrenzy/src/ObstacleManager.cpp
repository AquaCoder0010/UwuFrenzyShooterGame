#include "ObstacleManager.hpp"


ObstacleManager::ObstacleManager(int win_x, int win_y)
:currentTime(sf::Time::Zero), obstacles(), explosionTex()
{
    if(obstacleTex.loadFromFile("rsrc/Images/Asteroid.png"))
    {
        std::cout << "Loaded Asteroid.png Texture" << std::endl;
    }

    if(explosionTex.loadFromFile("rsrc/Images/Explosion_1.png"))
    {
        std::cout << "Loaded Explosion_1.png Texture" << std::endl;
    }
    explosions.reserve(10);
    windowSize.x = win_x; windowSize.y = win_y;
    colide = false;
}

void ObstacleManager::update(sf::Time deltaTime, std::vector<Bullet>& bullets)
{
    currentTime += deltaTime;
    if(currentTime.asSeconds() > 3.f)
    {
        currentTime = sf::Time::Zero;
        obstacles.push_back(Obstacle(obstacleTex));
        obstacles.back().health = 3;
        obstacles.back().obstacle.setPosition(sf::Vector2f( rand() % windowSize.x - 20.f, 20.f));
        obstacles.back().randRotationSpeed();
        if(obstacles.back().rotation > 10.f)
        {
            obstacles.back().obstacle.scale(0.5f, 0.5f);
            obstacles.back().obstacle.setOrigin(obstacleTex.getSize().x/2, obstacleTex.getSize().y/2);
        }
        if(obstacles.back().rotation < 10.f && obstacles.back().rotation > 5.f)
        {
            obstacles.back().obstacle.scale(0.75f, 0.75f);
            obstacles.back().obstacle.setOrigin(obstacleTex.getSize().x/2, obstacleTex.getSize().y/2);
        }

        else
        {
            obstacles.back().obstacle.scale(1.f, 1.f);
            obstacles.back().obstacle.setOrigin(obstacleTex.getSize().x/2, obstacleTex.getSize().y/2);
        }
    }

    for(int i = 0; i < bullets.size(); i++)
    {
        for(int x = 0; x < obstacles.size(); x++)
        {
            if(bullets[i].getBulletBounds().intersects(obstacles[x].getObstacleGlobalBounds()))
            {
                colide = true;
                obstacles[x].health -= 1;
                std::vector<Bullet>::iterator bulletIterator = bullets.begin() + i;
                bullets.erase(bulletIterator);
        }
        } 
    }  


     // check if obstacle Passes the Window Y position or its health is lower than zero;
    for (std::vector<Obstacle>::iterator it = obstacles.begin(); it !=obstacles.end();)
    {
        if ((it->getObstaclePosition().y > windowSize.y) == true)
        {
            explosions.push_back(Explosion(explosionTex));
            explosions.back().setPosition(sf::Vector2f(it->getObstaclePosition().x - 185/2, it->getObstaclePosition().y - 185/2));
            it = obstacles.erase(it);
        }
        else if(it->health == 0)
        {   
            explosions.push_back(Explosion(explosionTex));
            explosions.back().setPosition(sf::Vector2f(it->getObstaclePosition().x - 185/2, it->getObstaclePosition().y - 185/2));
            it = obstacles.erase(it);
        }
        else
        {
            it++;
        }
    }

    for(int i = 0; i < explosions.size(); i++)
    {
        explosions[i].animate();
        if(explosions[i].animationFinish == true)
        {
            std::vector<Explosion>::iterator explosionIter = explosions.begin() + i;
            explosions.erase(explosionIter);
        }

    }


    // update
    for(auto& obstacles : obstacles)
    {
        obstacles.obstacle.move(sf::Vector2f(0.f, 2.f));
        obstacles.obstacle.rotate(obstacles.rotation);
    }
}

void ObstacleManager::drawTo(sf::RenderWindow& window)
{
    // draw 
    for(auto& obstacles : obstacles)
    {
        window.draw(obstacles.obstacle); 
    }
    for(auto & explosions : explosions)
    {
        window.draw(explosions.explosionSprite);
    }
}
