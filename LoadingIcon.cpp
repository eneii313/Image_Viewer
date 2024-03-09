#include "LoadingIcon.h"
#include <iostream>

LoadingIcon::LoadingIcon(int posX, int posY, int spriteHeight, float scale) {

	// set texture icon
	if (!this->icon.loadFromFile("Media/loading_icon.png"))
		std::cerr<<"Failed to load loading icon" << std::endl;

	this->sprite.setTexture(this->icon);
	this->sprite.setColor(sf::Color(0,175,215));
	this->sprite.setOrigin(icon.getSize().x / 2.0f, icon.getSize().y / 2.0f);
	this->sprite.setPosition(posX, posY);

	float desiredHeight = spriteHeight * scale;
	float iconScale = desiredHeight / this->icon.getSize().y;
	this->sprite.setScale(iconScale, iconScale);
}

void LoadingIcon::setPosition(int posX, int posY) {
	this->sprite.setPosition(posX, posY);
	//std::cout << "Settingloading icon at " << posX << ", " << posY << std::endl;
}

void LoadingIcon::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}

void LoadingIcon::update(sf::Time deltaTime) {
	// update rotation angle
	float rotation = this->sprite.getRotation();
	rotation += rot_speed * deltaTime.asSeconds();
	this->sprite.setRotation(rotation);
}