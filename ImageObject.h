#pragma once
#include "SFML/Graphics.hpp"
#include "LoadingIcon.h"

class ImageObject {
public:
	ImageObject(int posX, int posY, int iconSizeX, int iconSizeY);
	void setTexture(std::string texturePath);
	void setPosition(int posX, int posY);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

private:
	int iconSizeX;
	int iconSizeY;

	sf::Sprite sprite;
	sf::RectangleShape border;
	bool textureLoaded;

	LoadingIcon* loadingIcon;
};