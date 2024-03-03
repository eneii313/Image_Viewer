#include "LoadingIcon.h"
#include <iostream>

LoadingIcon::LoadingIcon(int radius, int posX, int posY) {
	this->radius = radius;
	this->posX = posX;
	this->posY = posY;
	this->angle = 0;

	// set texture icon
	if (!this->icon.loadFromFile("Media/loading_icon.png"))
		this->circle.setFillColor(sf::Color::Red);
}

void LoadingIcon::initialize() {
	this->angle = 0;
	this->circle.setRadius(radius);
	this->circle.setFillColor(sf::Color::Red);
	this->circle.setOrigin(radius, radius);
	this->circle.setPosition(posX, posY);
	this->circle.setTexture(&icon);

}

void LoadingIcon::draw(sf::RenderWindow& window) {
	window.draw(this->circle);
}

void LoadingIcon::update(sf::Time deltaTime) {
	// update rotation angle
	this->angle += rot_speed * deltaTime.asSeconds();

	if (this->angle >= 360)
		this->angle -= 360;

	this->circle.setRotation(this->angle);
}