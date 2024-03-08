#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include "ImageObject.h"
#include "ImageManager.h"

ImageObject::ImageObject(std::string assetName, int posX, int posY, int iconSizeX, int iconSizeY) {
	this->textureLoaded = false;

	this->assetName = assetName;
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

void ImageObject::setTexture() {

	sf::Texture* texture = ImageManager::getInstance()->getImageTexture(this->assetName);
	if (!this->textureLoaded && texture) {
		this->sprite.setTexture(*texture);

		float scaleX = static_cast<float>(this->iconSizeX) / texture->getSize().x;
		float scaleY = static_cast<float>(this->iconSizeY) / texture->getSize().y;

		// resize image texture
		this->sprite.setScale(scaleX, scaleY);

		textureLoaded = true;
		std::cout << "[ImageObject] " << this->assetName + " loaded." << std::endl;
	}

	
}

void ImageObject::setPosition(int posX, int posY) {
	this->sprite.setPosition(posX, posY);
	this->border.setPosition(posX, posY);

	int centerX = (posX + this->iconSizeX / 2) ;
	int centerY = posY + this->iconSizeY / 2;
	this->loadingIcon->setPosition(centerX, centerY);


}

bool ImageObject::isTextureLoaded() const {
	return textureLoaded;
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

bool ImageObject::isMouseOver(const sf::Vector2f& mousePosition) {
	sf::FloatRect bounds = this->sprite.getGlobalBounds();
	return bounds.contains(mousePosition);
}

void ImageObject::handleDoubleClick() {
	// std::cout << "Double-click on image object detected! Index " << std::endl;
}

/*
// Implementation of getGlobalBounds function
sf::FloatRect ImageObject::getGlobalBounds() const {
	return sf::FloatRect(this->sprite.getPosition().x, this->sprite.getPosition().y, this->iconSizeX, this->iconSizeY);
}
*/