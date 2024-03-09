#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include "ImageObject.h"
#include "ImageManager.h"
#include "BaseRunner.h"

ImageObject::ImageObject(std::string assetName, int posX, int posY, int iconSizeX, int iconSizeY) {
	this->textureLoaded = false;

	this->assetName = assetName;
	this->iconSizeX = iconSizeX;
	this->iconSizeY = iconSizeY;

	this->sprite.setPosition(posX, posY);

	// setup loading icon
	this->loadingIcon = new LoadingIcon(posX, posY, iconSizeY, 0.5);

	// setup border for when there is no image loaded
	border.setSize(sf::Vector2f(iconSizeX, iconSizeY));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(3);
	border.setOutlineColor(sf::Color(70, 70, 77));
}


void ImageObject::setAssetName(std::string assetName) {
	this->assetName = assetName;
}

void ImageObject::setTexture() {

	sf::Texture* texture = ImageManager::getInstance()->getImageTexture(this->assetName);
	if (texture != nullptr) {
		this->sprite.setTexture(*texture);
		this->sprite.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));

		float scaleX = static_cast<float>(this->iconSizeX) / texture->getSize().x;
		float scaleY = static_cast<float>(this->iconSizeY) / texture->getSize().y;

		// resize image texture
		this->sprite.setScale(scaleX, scaleY);

		this->textureLoaded = true;
	}

	
}

void ImageObject::setPosition(int posX, int posY) {
	this->sprite.setPosition(posX, posY);
	this->border.setPosition(posX, posY);

	int centerX = (posX + this->iconSizeX / 2) ;
	int centerY = posY + this->iconSizeY / 2;
	this->loadingIcon->setPosition(centerX, centerY);


}

void ImageObject::setSizeByTexture() {
	float textureWidth = this->sprite.getTexture()->getSize().x;
	float textureHeight = this->sprite.getTexture()->getSize().y;
	
	if (textureWidth > this->iconSizeX || textureHeight > this->iconSizeY) {
		std::cout << "[ImageObject] textureSize: " << textureWidth << " " << textureHeight << std::endl;
		std::cout << "[ImageObject] iconSize: " << iconSizeX << " " << iconSizeY << std::endl;
		
		float scaleX = this->iconSizeX / textureWidth;
		float scaleY = this->iconSizeY / textureHeight;

		float scaleFactor = std::min(scaleX, scaleY);

		this->sprite.setScale(scaleFactor, scaleFactor);
		
		std::cout << "[ImageObject] " << this->assetName <<" scaleFactor: " << scaleFactor << std::endl;

		// center the sprite
		sf::FloatRect scaledBounds = this->sprite.getLocalBounds();
		float scaledWidth = scaledBounds.width * this->sprite.getScale().x;
		float scaledHeight = scaledBounds.height * this->sprite.getScale().y;

		float screenWidth = static_cast<float>(BaseRunner::WINDOW_WIDTH);

		this->sprite.setPosition((screenWidth - scaledWidth) / 2.0f, this->sprite.getPosition().y);

		std::cout << "[ImageObject] new textureSize: " << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << std::endl << std::endl;
	}
	
}

void ImageObject::setBorder() {
	this->border.setOutlineColor(sf::Color::White);
	this->showBorder = true;
}

void ImageObject::removeBorder() {
	this->showBorder = false;
}

bool ImageObject::isTextureLoaded() const {
	return this->textureLoaded;
}


std::string ImageObject::getAssetName() const {
	return this->assetName;
}

void ImageObject::update(sf::Time deltaTime) {
	if (!this->textureLoaded) {
		this->loadingIcon->update(deltaTime);
	}
}

void ImageObject::draw(sf::RenderWindow& window) {
	if (this->textureLoaded) {
		window.draw(this->sprite);
		if (this->showBorder)
			window.draw(border);
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

float ImageObject::getImageEndPos() {
	return this->sprite.getPosition().y;
}