#include <iostream>
#include <SFML/Graphics.hpp>


#include "Player.hpp"
#include "BulletManager.hpp"
#include "ObstacleManager.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 500), "title");
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);

	Player player;
	player.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2 + window.getSize().y/4));
	player.getWindowSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	BulletManager bulletManager;
	bulletManager.getWindowSize(window.getSize().x, window.getSize().y);

	ObstacleManager obstacleManager(window.getSize().x, window.getSize().y);
	
	sf::Event event;
	sf::Time deltaTime;
	sf::Clock clock;
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			player.processEvent(event);
			bulletManager.processInput(event);
		}
		//update
		deltaTime = clock.restart();
		player.getMousePosition(sf::Mouse::getPosition(window));
		player.update(deltaTime);
		bulletManager.setGunPosition(player.returnGunPos());
		bulletManager.setGunRotation(player.returnGunAngle());
		obstacleManager.update(deltaTime, bulletManager.getBulletVector());
		bulletManager.update(deltaTime);
		
		//render
		window.clear();	
		player.drawTo(window);
		bulletManager.drawTo(window);
		obstacleManager.drawTo(window);
		window.display();
	}
}