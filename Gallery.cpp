#include <iostream>
#include "Gallery.h"
#include "BaseRunner.h"

Gallery::Gallery(int posX, int posY, int windowWidth, int windowHeight) { 
	this->posX = posX;
	this->posY = posY;
	this->iconSizeX = (windowWidth - iconPadding * (COLUMNS + 1)) / COLUMNS;
	this->iconSizeY = (windowHeight - iconPadding * (ROWS + 1)) / ROWS;
}

void Gallery::addImage(std::string texturePath) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath))
		std::cerr << texturePath + " not found." << std::endl;

	sf::Sprite sprite(*texture);

	float scaleX = this->iconSizeX / texture->getSize().x;
	float scaleY = this->iconSizeY / texture->getSize().y;

	// resize image texture
	sprite.setScale(scaleX, scaleY);
	
	this->images.push_back(sprite);
}

void Gallery::updateImagePositions() {
	int x = this->posX;
	int y = this->posY;

	for (int i = 0; i < this->images.size(); ++i) {
		this->images[i].setPosition(x, y);

		x += iconSizeX + iconPadding;

		if ((i + 1) % COLUMNS == 0) {
			x = posX;
			y += iconSizeY + iconPadding;
		}
	}
}

void Gallery::draw(sf::RenderWindow& window) {
	for (const auto& image : this->images)
		window.draw(image);
}