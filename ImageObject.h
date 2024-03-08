#pragma once
#include "SFML/Graphics.hpp"
#include "LoadingIcon.h"

class ImageObject {
public:
	ImageObject(std::string assetName, int posX, int posY, int iconSizeX, int iconSizeY);
	//void setTexture(std::string texturePath);
	void setTexture();
	void setPosition(int posX, int posY);
	bool isMouseOver(const sf::Vector2f& mousePosition);
	void handleDoubleClick();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Sprite sprite;

	bool isTextureLoaded() const;

private:
	std::string assetName;
	int iconSizeX;
	int iconSizeY;

	sf::RectangleShape border;
	bool textureLoaded;

	LoadingIcon* loadingIcon;
};