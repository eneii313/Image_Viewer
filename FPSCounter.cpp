#include "FPSCounter.h"
#include <iostream>
#include "BaseRunner.h"

FPSCounter::FPSCounter() {
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Roboto.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(BaseRunner::WINDOW_WIDTH - 155, BaseRunner::WINDOW_HEIGHT - 72);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);
}

void FPSCounter::processInput(sf::Event event)
{
}

void FPSCounter::update(sf::Time deltaTime)
{
	this->updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow& window) {
	window.draw(*this->statsText);
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	//this->statsText->setString("FPS: --\n");
	this->updateTime += elapsedTime;

	if (this->updateTime >= sf::seconds(0.5f)) {
		this->updateTime = sf::seconds(0.0f);
		this->statsText->setString("FPS: " + std::to_string(BaseRunner::getInstance()->getFPS()) + "\n");
	}
}

void FPSCounter::updateFPSPosition(int posY) {
	this->statsText->setPosition(BaseRunner::WINDOW_WIDTH - 155, posY - this->statsText->getGlobalBounds().height);
	// std::cout << "FPS Position: " << this->statsText->getPosition().x << " " << this->statsText->getPosition().y << std::endl;
}
