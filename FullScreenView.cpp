#include <iostream>
#include <filesystem>
#include "FullScreenView.h"
#include "ImageManager.h"
#include "BaseRunner.h"
#include "StringUtils.h"


FullScreenView* FullScreenView::sharedInstance = NULL;

FullScreenView* FullScreenView::getInstance() {
	if (sharedInstance == NULL)
		sharedInstance = new FullScreenView(BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT);
	return sharedInstance;
}


FullScreenView::FullScreenView(int windowWidth, int windowHeight) {
	this->iconSizeX = (windowWidth - iconPadding * (ICON_COUNT + 1)) / ICON_COUNT;
	this->iconSizeY = windowHeight * 0.15;


	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Roboto.ttf");

	this->returnBtn.setString("< Return");
	this->returnBtn.setFont(*font);
	this->returnBtn.setCharacterSize(36);
	this->returnBtn.setFillColor(sf::Color::White);
	this->returnBtn.setPosition(25, 25);

	this->mainImage = new ImageObject("00.jpg", 0, 0, windowWidth - (iconPadding*2), (windowHeight * 0.8) - (iconPadding*2) - 75);
	this->mainImage->setPosition(iconPadding, iconPadding + 75);
	
	for (int i = 0; i < this->ICON_COUNT; ++i) {
		std::string assetName = ImageManager::getInstance()->getImageNameAt(i);
		ImageObject* imageObject = new ImageObject(assetName, 0, 0, this->iconSizeX, this->iconSizeY);
		this->images.push_back(imageObject);
	}
	updateImagePositions();
}

void FullScreenView::updateImagePositions() {

	int x = iconPadding;
	int y = BaseRunner::WINDOW_HEIGHT * 0.8;

	for (int i = 0; i < this->ICON_COUNT; ++i) {
		this->images[i]->setPosition(x, y);

		x += iconSizeX + iconPadding;

	}

}

void FullScreenView::update(sf::Time deltaTime) {
	this->mainImage->update(deltaTime);
	for (const auto& image : this->images)
		image->update(deltaTime);

}

void FullScreenView::draw(sf::RenderWindow& window) {
	window.draw(this->returnBtn);
	this->mainImage->draw(window);
	for (const auto& image : this->images)
		image->draw(window);
}