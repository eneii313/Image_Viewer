#pragma once
#include <iostream>
#include "ImageObject.h"
#include <thread>

ImageObject::ImageObject(int posX, int posY, int iconSizeX, int iconSizeY) {
	this->textureLoaded = false;

	this->iconSizeX = iconSizeX;
	this->iconSizeY = iconSizeY;

	this->sprite.setPosition(posX, posY);

	// setup loading icon
	this->loadingIcon = new LoadingIcon(posX, posY, 0.5);

	// setup border for when there is no image loaded
	border.setSize(sf::Vector2f(iconSizeX, iconSizeY));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(3);
	border.setOutlineColor(sf::Color(70, 70, 77));
}

// TODO: move loading texture into gallery
void ImageObject::setTexture(std::string texturePath) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath))
		std::cerr << texturePath + " not found." << std::endl;

	this->sprite.setTexture(*texture);

	float scaleX = static_cast<float>(this->iconSizeX) / texture->getSize().x;
	float scaleY = static_cast<float>(this->iconSizeY) / texture->getSize().y;

	// resize image texture
	this->sprite.setScale(scaleX, scaleY);

	this->textureLoaded = true;
	//std::cout << texturePath + " loaded." << std::endl;
}

void ImageObject::setPosition(int posX, int posY) {
	this->sprite.setPosition(posX, posY);
	this->border.setPosition(posX, posY);

	int centerX = (posX + this->iconSizeX / 2) ;
	int centerY = posY + this->iconSizeY / 2;
	this->loadingIcon->setPosition(centerX, centerY);


}

void ImageObject::update(sf::Time deltaTime) {
	if (!this->textureLoaded) {
		this->loadingIcon->update(deltaTime);
	}
}

void ImageObject::draw(sf::RenderWindow& window) {
	if (this->textureLoaded) {
		window.draw(this->sprite);
	}
	else {
		this->loadingIcon->draw(window);
		window.draw(border);
	}
}