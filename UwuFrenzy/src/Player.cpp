#include "Player.hpp"

Player::Player()
:playerRect(), playerRectPos(), windowSize(), playerRectMotion(0.f, 0.f), gunAngle(0.f), gun(), 
playerRectTex(), gunTex()
{   
    if(playerRectTex.loadFromFile("rsrc/Images/Player.png"))
    {
        playerRect.setTexture(playerRectTex);
        playerRect.setOrigin(playerRectTex.getSize().x/2, playerRectTex.getSize().y/2);
    }

    if(gunTex.loadFromFile("rsrc/Images/Gun Model.png"))
    {
        gun.setTexture(gunTex); // orignal Size was 10, 10
        gun.setOrigin(gunTex.getSize().x/2, gunTex.getSize().y/2); 
    }

    playerRectPos.x = 0; playerRectPos.y = 0;
    windowSize.x = 0; windowSize.y = 0;
    left = false; right = false;
    mouseDistance = 0; tIndex = 0;
    mousePos.x = 0; mousePos.y = 0;
    gunPos.x = 0; gunPos.y = 0; 
}

sf::Vector2f Player::returnGunPos()
{
    gunPos = gun.getPosition();
    return gunPos;
}

float Player::returnGunAngle()
{
    return gun.getRotation();
}


void Player::setPosition(sf::Vector2f p_playerRectPos)
{  
    playerRect.setPosition(p_playerRectPos);
    gun.setPosition(sf::Vector2f(p_playerRectPos.x + 45.f, p_playerRectPos.y - 45.f));
}

void Player::getMousePosition(sf::Vector2i p_mousePos)
{
    mousePos.x = p_mousePos.x; mousePos.y = p_mousePos.y;
}

void Player::getWindowSize(sf::Vector2f p_windowSize)
{
    windowSize = p_windowSize;
}
void Player::processEvent(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::A)
            left = true;
        if(event.key.code == sf::Keyboard::D)
            right = true;
    }

    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::A)
            left = false;
        if(event.key.code == sf::Keyboard::D)
            right = false;
    }

}

void Player::update(sf::Time deltaTime)
{
    moveGun();
    playerRectMotion.x = 0; playerRectMotion.y = 0;

    if(left == true)
        playerRectMotion.x = -4;
    if(right == true)
        playerRectMotion.x = 4;

    if(playerRectPos.x > windowSize.x + 10.f)
    {
        playerRect.setPosition(sf::Vector2f(0.f, playerRectPos.y));
        gun.setPosition(sf::Vector2f(0.f + 45.f, playerRectPos.y));
    }

    if(playerRectPos.x < 0.f)
    {
        playerRect.setPosition(sf::Vector2f(windowSize.x + 5.f,  playerRectPos.y));
        gun.setPosition(sf::Vector2f(windowSize.x + 5.f, playerRectPos.y));
    }
    

    playerRect.move(playerRectMotion);
    gun.move(playerRectMotion);
}

void Player::drawTo(sf::RenderWindow& window)
{
    window.draw(playerRect);
    window.draw(gun);
}

void Player::moveGun()
{
    sf::Vector2f rotationalGunPos;
    playerRectPos = playerRect.getPosition();
    mouseDistance = sqrt( pow(mousePos.x - playerRectPos.x, 2) + pow(mousePos.y - playerRectPos.y, 2) );
    tIndex = 45.f /mouseDistance;
    gunPos.x = playerRectPos.x*(1 - tIndex) + mousePos.x * tIndex;
    gunPos.y = playerRectPos.y*(1 - tIndex) + mousePos.y * tIndex;

    rotationalGunPos = gun.getPosition();
    gunAngle = ((atan2( (mousePos.y - rotationalGunPos.y), mousePos.x - rotationalGunPos.x) * 180) / 3.141592 );
    gun.setPosition(gunPos);
    gun.setRotation(gunAngle);

    // 270 - 90
    //90 - 0, 360 - 270

    if((gun.getRotation() < 270) && (gun.getRotation() > 90))
        gun.setScale(1.f, -1.f);
    if( ((gun.getRotation() < 90) && (gun.getRotation() > 0)) || (gun.getRotation() < 360) && (gun.getRotation() > 270))
        gun.setScale(1.f, 1.f);
}