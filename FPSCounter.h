#pragma once
#include <SFML/Graphics.hpp>

class FPSCounter {
public:
	FPSCounter();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	void updateFPSPosition(int posY);

private:
	sf::Time updateTime;
	sf::Text* statsText;
	int framesPassed = 0;

	void updateFPS(sf::Time elapsedTime);

};

